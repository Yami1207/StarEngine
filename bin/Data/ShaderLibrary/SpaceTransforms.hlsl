#ifndef __ENGINE_SPACE_TRANSFORMS_HLSL__
#define __ENGINE_SPACE_TRANSFORMS_HLSL__

float4x4 GetObjectToWorldMatrix()
{
	return TRANSFORM_MATRIX_M;
}

float4x4 GetWorldToViewMatrix()
{
	return TRANSFORM_MATRIX_V;
}

float4x4 GetViewToHClipMatrix()
{
	return TRANSFORM_MATRIX_P;
}

float4x4 GetWorldToHClipMatrix()
{
	return TRANSFORM_MATRIX_VP;
}

// 返回世界空间坐标（物体坐标到世界空间）
float4 TransformObjectToWorld(float4 positionOS)
{
    return mul(positionOS, GetObjectToWorldMatrix());
}

// 返回视锥空间坐标（世界空间到视锥空间）
float4 TransformWorldToView(float4 positionWS)
{
	return mul(positionWS, GetWorldToViewMatrix());
}

// 返回剪辑空间坐标（物体坐标到剪辑空间）
float4 TransformObjectToHClip(float4 positionOS)
{
	float4 positionWS = TransformObjectToWorld(positionOS);
	return mul(positionWS, GetWorldToHClipMatrix());
}

#endif
