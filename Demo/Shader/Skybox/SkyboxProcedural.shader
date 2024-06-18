Shader "Skybox/Procedural"
{
	Properties
	{
		_SunSize("Sun Size", Range(0, 1)) = 0.04
		_SunStrength("Sun Strength", Range(0, 1)) = 1.0
		_AtmosphereThickness("Atmosphere Thickness", Range(0, 5)) = 1.0
		_SkyTint("Sky Tint", Color) = (.5, .5, .5, 1)
		_GroundColor("Ground", Color) = (.369, .349, .341, 1)

		_Exposure("Exposure", Range(0, 8)) = 1.3
	}

	SubShader
	{
		Pass
		{
			zwrite off

			HLSLPROGRAM
			#pragma vertex vert
			#pragma fragment frag
			#pragma target 3.0

			#include "SkyboxProcedural.hlsl"
			ENDHLSL
		}
	}
}