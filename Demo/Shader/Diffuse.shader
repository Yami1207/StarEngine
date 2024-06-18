Shader "Legacy Shaders/Diffuse"
{
	Properties
	{
		_BaseColor("Color", Color) = (1, 1, 1, 1)
		_BaseMap("Base Map (RGB)", 2D) = "white" {}
	}
	SubShader
	{
		LOD 100

		Pass
		{
			Name "Forward"
			Tags{ "LightMode" = "Forward" }

			HLSLPROGRAM
			#pragma vertex vert
			#pragma fragment frag
			#pragma target 3.0

			#include "Diffuse.hlsl"
			ENDHLSL
		}
	}
}
