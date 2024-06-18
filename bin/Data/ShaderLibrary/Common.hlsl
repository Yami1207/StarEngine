#ifndef __ENGINE_COMMON_HLSL__
#define __ENGINE_COMMON_HLSL__

//#define HAS_HALF    1

#if defined(HAS_HALF)
#define half    min16float
#define half2   min16float2
#define half3   min16float3
#define half4   min16float4
#define half2x2 min16float2x2
#define half2x3 min16float2x3
#define half3x2 min16float3x2
#define half3x3 min16float3x3
#define half3x4 min16float3x4
#define half4x3 min16float4x3
#define half4x4 min16float4x4
#else
#define half    float
#define half2   float2
#define half3   float3
#define half4   float4
#define half2x2 float2x2
#define half2x3 float2x3
#define half3x2 float3x2
#define half3x3 float3x3
#define half3x4 float3x4
#define half4x3 float4x3
#define half4x4 float4x4
#endif

#if defined(SHADER_API_D3D11)
#include "ShaderLibrary/API/D3D11.hlsl"
#else
#error unsupported shader api
#endif

#include "ShaderLibrary/Macros.hlsl"
#include "ShaderLibrary/ShaderVariables.hlsl"
#include "ShaderLibrary/SpaceTransforms.hlsl"

#endif
