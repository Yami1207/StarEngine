#ifndef __SHADER_VARIABLES_HLSL__
#define __SHADER_VARIABLES_HLSL__

CBUFFER_START(CameraCB, 0)
	float4x4 g_TransMatrix_View;
	float4x4 g_TransMatrix_Projection;
	float4x4 g_TransMatrix_VP;
	float4x4 g_TransMatrix_InvV;
	float4x4 g_TransMatrix_InvP;
	float4x4 g_TransMatrix_InvVP;
CBUFFER_END

CBUFFER_START(ObjectCB, 1)
	float4x4 g_TransMatrix_ObjectToWorld;
	float4x4 g_TransMatrix_WorldToObject;
CBUFFER_END

CBUFFER_START(LightsCB, 2)
	float4 g_MainLightPosition;
	half4 g_MainLightColor;
CBUFFER_END

// 物体空间到世界空间变换矩阵
#define TRANSFORM_MATRIX_M		g_TransMatrix_ObjectToWorld

// 世界空间到视锥空间变换矩阵
#define TRANSFORM_MATRIX_V		g_TransMatrix_View

// 世界空间到视锥空间变换逆矩阵
#define TRANSFORM_MATRIX_INV_V 	g_TransMatrix_InvV

// 视锥空间到裁剪空间变换矩阵
#define TRANSFORM_MATRIX_P		g_TransMatrix_Projection

// 视锥空间到裁剪空间变换逆矩阵
#define TRANSFORM_MATRIX_INV_P 	g_TransMatrix_InvP

// 世界空间到裁剪空间变换矩阵
#define TRANSFORM_MATRIX_VP		g_TransMatrix_VP

// 世界空间到裁剪空间变换逆矩阵
#define TRANSFORM_MATRIX_INV_VP	g_TransMatrix_InvVP

#endif
