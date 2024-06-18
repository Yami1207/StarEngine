#ifndef __D3D11_HLSL__
#define __D3D11_HLSL__

#define CBUFFER_START(name, slot)   cbuffer name : register(b##slot) {
#define CBUFFER_MATERIAL_START      cbuffer MaterialCB : register(b3) {
#define CBUFFER_END                 };

// 初始化结构体或数组
#define ZERO_INITIALIZE(type, name) name = (type)0;
#define ZERO_INITIALIZE_ARRAY(type, name, arraySize) { for (int arrayIndex = 0; arrayIndex < arraySize; arrayIndex++) { name[arrayIndex] = (type)0; } }

// Texture
#define TEXTURE2D(textureName)          Texture2D textureName
#define TEXTURE2D_ARRAY(textureName)    Texture2DArray textureName
#define TEXTURECUBE(textureName)        TextureCube textureName
#define TEXTURECUBE_ARRAY(textureName)  TextureCubeArray textureName
#define TEXTURE3D(textureName)          Texture3D textureName

// 纹理采样器
#define SAMPLER(samplerName)            SamplerState samplerName

#define TEXTURE2D_PARAM(textureName, samplerName)	TEXTURE2D(textureName), SAMPLER(samplerName)

#define TEXTURE2D_ARGS(textureName, samplerName)	textureName, samplerName

// 纹理采样
#define SAMPLE_TEXTURE2D(textureName, samplerName, uv)	textureName.Sample(samplerName, uv)

#endif
