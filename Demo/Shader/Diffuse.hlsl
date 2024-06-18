#ifndef __DIFFUSE_HLSL__
#define __DIFFUSE_HLSL__

#include "ShaderLibrary/Common.hlsl"

CBUFFER_MATERIAL_START
	float4 _BaseMap_ST;
	float4 _BaseColor;
CBUFFER_END

TEXTURE2D(_BaseMap);
SAMPLER(sampler_BaseMap);

// 顶点输入数据
struct Attributes
{
	float4 positionOS	: POSITION;
	float2 texcoord		: TEXCOORD0;
};

// 片元输入数据
struct Varyings
{
	float4 positionCS	: SV_POSITION;
	float2 texcoord		: TEXCOORD0;
};

// 顶点函数
Varyings vert(Attributes input)
{
	Varyings output = (Varyings)0;
	output.positionCS = TransformObjectToHClip(input.positionOS);
	output.texcoord = TRANSFORM_TEX(input.texcoord, _BaseMap);
	return output;
}

// 片元函数
float4 frag(Varyings input) : SV_TARGET
{
	float4 baseColor = SAMPLE_TEXTURE2D(_BaseMap, sampler_BaseMap, input.texcoord);
	float3 finalColor = baseColor.rgb * _BaseColor.rgb;
	float alpha = baseColor.a * _BaseColor.a;
	return float4(finalColor, alpha);
}

#endif
