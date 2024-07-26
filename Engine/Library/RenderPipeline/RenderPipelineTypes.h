#ifndef __RENDER_PIPELINE_TYPES_H__
#define __RENDER_PIPELINE_TYPES_H__

namespace StarEngine
{
	class Camera;
	class ScriptableRenderer;

	namespace Rendering
	{
		struct CameraData
		{
			sBoolean	clearDepth;
			
			Camera*		pCamera;

			ScriptableRenderer*	pRenderer;
		};

		struct RenderingData
		{
			CameraData*	pCameraData;

			sBoolean	enablePostProcess;
		};

		struct ShaderPropertyID
		{
			static void Initialize();

			static uint32 viewMatrix;
			static uint32 projectionMatrix;
			static uint32 viewProjectionMatrix;

			static uint32 inverseViewMatrix;
			static uint32 inverseProjectionMatrix;
			static uint32 inverseViewProjectionMatrix;

			static uint32 objectToWorldMatrix;
			static uint32 worldToObjectMatrix;

			static uint32 mainLightPosition;
			static uint32 mainLightColor;
		};
	}
}

#endif // !__RENDER_PIPELINE_TYPES_H__
