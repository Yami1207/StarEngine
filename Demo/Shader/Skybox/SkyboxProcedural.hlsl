#ifndef __SKYBOX_PROCEDURAL_HLSL__
#define __SKYBOX_PROCEDURAL_HLSL__

#include "Shader/Lib/Core.hlsl"

CBUFFER_MATERIAL_START
    float _SunSize;
    float _SunStrength;
    float _AtmosphereThickness;
    float3 _SkyTint;
    float3 _GroundColor;
    float _Exposure;
CBUFFER_END

#define MAX_SCATTER 50.0
#define SUN_BRIGHTNESS 20.0
#define MIE_CONSTANT 0.0010
#define RAYLEIGH_CONSTANT (lerp(0.0, 0.0025, pow(abs(_AtmosphereThickness) , 2.5)))

#define SKY_GROUND_THRESHOLD 0.02

#define MIE_G (-0.990)
#define MIE_G2 0.9801

// RGB wavelengths
// .35 (.62=158), .43 (.68=174), .525 (.75=190)
static const float3 kDefaultScatteringWavelength = float3(0.65, 0.57, 0.475);
static const float3 kVariableRangeForScatteringWavelength = float3(0.15, 0.15, 0.15);

// 地球半径
static const float kInnerRadius = 1.0;
static const float kInnerRadius2 = 1.0; // kInnerRadius * kInnerRadius;

// 大气层顶部到地球球心的距离,由于大气层的高度为0.025,因此定义为1.025
#define OUTER_RADIUS 1.025
static const float kOuterRadius = OUTER_RADIUS;
static const float kOuterRadius2 = kOuterRadius * kOuterRadius;

static const float kCameraHeight = 0.0001;

static const float kSimpleSundiskIntensityFactor = 27.0;
static const float kSunScale = 400.0 * SUN_BRIGHTNESS;
static const float kKmESun = MIE_CONSTANT * SUN_BRIGHTNESS;
static const float kKm4PI = MIE_CONSTANT * 4.0 * 3.14159265;
static const float kScale = 1.0 / (OUTER_RADIUS - 1.0);
static const float kScaleDepth = 0.25;
static const float kScaleOverScaleDepth = (1.0 / (OUTER_RADIUS - 1.0)) / kScaleDepth;
static const float kSamples = 2.0;

// 光学深度值
inline float Scale(float inCos)
{
    float x = 1.0 - inCos;
    return 0.25 * exp(-0.00287 + x * (0.459 + x * (3.83 + x * (-6.80 + x * 5.25))));
}

// 相位函数
inline float GetRayleighPhase(float eyeCos2)
{
    return 0.75 + 0.75 * eyeCos2;
}

// 相位函数
inline float GetRayleighPhase(float3 light, float3 ray)
{
    float eyeCos = dot(light, ray);
    return GetRayleighPhase(eyeCos * eyeCos);
}

// 计算太阳
inline float CalcSunAttenuation(float3 lightPos, float3 ray)
{
    half3 delta = lightPos - ray;
    half dist = length(delta);
    half spot = 1.0 - smoothstep(0.0, _SunSize, dist);
    return spot * spot;
}

// 顶点输入数据
struct Attributes
{
    float4 positionOS : POSITION;
};

// 片元输入数据
struct Varyings
{
    float4 positionCS   : SV_POSITION;
    float3 rayDirection : TEXCOORD0;
    float3 groundColor  : TEXCOORD1;
    float3 skyColor     : TEXCOORD2;
    float3 sunColor     : TEXCOORD3;
};

// 顶点函数
Varyings vert(Attributes input)
{
    float3 skyTintInGammaSpace = _SkyTint;
    float3 scatteringWavelength = lerp(kDefaultScatteringWavelength - kVariableRangeForScatteringWavelength,
		kDefaultScatteringWavelength + kVariableRangeForScatteringWavelength, 1.0 - skyTintInGammaSpace);
    float3 invWavelength = 1.0 / pow(scatteringWavelength, 4);

    float kKrESun = RAYLEIGH_CONSTANT * SUN_BRIGHTNESS;
    float kKr4PI = RAYLEIGH_CONSTANT * 4.0 * 3.14159265;
    
    // 相机位置
    float3 cameraPos = float3(0, kInnerRadius + kCameraHeight, 0);
    
    Light light = GetMainLight();
    float3 lightDirection = light.direction;
    half3 lightColor = light.color;
    
    Varyings output = (Varyings)0;
    output.positionCS = TransformObjectToHClip(input.positionOS);
    
    // 地心到穿过大气层的光点向量
    float3 positionWS = TransformObjectToWorld(input.positionOS).xyz;
    float3 eyeRay = normalize(positionWS);

	// 光线方向
    output.rayDirection = -eyeRay;

    float far = 0;
    float3 inScatter, outScatter;
    float3 frontColor = float3(0.0, 0.0, 0.0);
    
    if (eyeRay.y >= 0)	// Sky
    {
        far = sqrt(kOuterRadius2 + kInnerRadius2 * eyeRay.y * eyeRay.y - kInnerRadius2) - kInnerRadius * eyeRay.y;
        float3 pos = cameraPos + far * eyeRay;

		// 从相机位置沿着eyeRay方向到大气层顶部的光学深度
        float height = kInnerRadius + kCameraHeight;
        float depth = exp(kScaleOverScaleDepth * (-kCameraHeight));
        float startAngle = dot(eyeRay, cameraPos) / height;
        float startOffset = depth * Scale(startAngle);

        float sampleLength = far / kSamples;
        float scaledLength = sampleLength * kScale;
        float3 sampleRay = eyeRay * sampleLength;
        float3 samplePoint = cameraPos + sampleRay * 0.5;

        for (int i = 0; i < int(kSamples); ++i)
        {
            float height = length(samplePoint);
            float depth = exp(kScaleOverScaleDepth * (kInnerRadius - height));
            float lightAngle = dot(lightDirection, samplePoint) / height;
            float cameraAngle = dot(eyeRay, samplePoint) / height;
            float scatter = (startOffset + depth * (Scale(lightAngle) - Scale(cameraAngle)));
            float3 attenuate = exp(-clamp(scatter, 0.0, MAX_SCATTER) * (invWavelength * kKr4PI + kKm4PI));

            frontColor += attenuate * (depth * scaledLength);
            samplePoint += sampleRay;
        }
        
        inScatter = frontColor * (invWavelength * kKrESun);
        outScatter = frontColor * kKmESun;
    }
    else
    {
        far = (-kCameraHeight) / (min(-0.00001, eyeRay.y));
        float3 pos = cameraPos + far * eyeRay;

        float depth = exp((-kCameraHeight) * (1.0 / kScaleDepth));
        float cameraAngle = dot(-eyeRay, pos);
        float lightAngle = dot(lightDirection, pos);
        float cameraScale = Scale(cameraAngle);
        float lightScale = Scale(lightAngle);
        float cameraOffset = depth * cameraScale;
        float temp = (lightScale + cameraScale);

        float sampleLength = far / kSamples;
        float scaledLength = sampleLength * kScale;
        float3 sampleRay = eyeRay * sampleLength;
        float3 samplePoint = cameraPos + sampleRay * 0.5;

        float3 attenuate;
        for (int i = 0; i < int(kSamples); ++i)
        {
            float height = length(samplePoint);
            float depth = exp(kScaleOverScaleDepth * (kInnerRadius - height));
            float scatter = depth * temp - cameraOffset;
            attenuate = exp(-clamp(scatter, 0.0, MAX_SCATTER) * (invWavelength * kKr4PI + kKm4PI));
            frontColor += attenuate * (depth * scaledLength);
            samplePoint += sampleRay;
        }

        inScatter = frontColor * (invWavelength * kKrESun + kKmESun);
        outScatter = clamp(attenuate, 0.0, 1.0);
    }
    
    output.skyColor = _Exposure * (inScatter * GetRayleighPhase(lightDirection, -eyeRay));
    output.groundColor = _Exposure * (inScatter + _GroundColor * _GroundColor * outScatter);
    
    // 太阳光
    half lightColorIntensity = clamp(length(lightColor), 0.25, 1);
    output.sunColor = _SunStrength * kSimpleSundiskIntensityFactor * saturate(outScatter * kSunScale) * lightColor / lightColorIntensity;
    
    return output;
}

// 片元函数
float4 frag(Varyings input) : SV_TARGET
{
    float3 ray = input.rayDirection;
    float y = ray.y / SKY_GROUND_THRESHOLD;
    float3 color = lerp(input.skyColor, input.groundColor, saturate(y));
    
    if (y < 0)
    {
        Light light = GetMainLight();
        color += input.sunColor * CalcSunAttenuation(light.direction, -ray);
    }
    
    return float4(clamp(color, 0, 25), 1.0);
}

#endif
