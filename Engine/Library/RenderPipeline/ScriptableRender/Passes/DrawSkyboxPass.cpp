#include "EngineLibrary.h"
#include "DrawSkyboxPass.h"

#include "Runtime/Camera/Camera.h"

#include "RenderPipeline/RenderPipelineTypes.h"
#include "RenderPipeline/ScriptableRender/ScriptableRenderContext.h"

namespace StarEngine
{
	namespace Rendering
	{
		DrawSkyboxPass::DrawSkyboxPass() : ScriptableRenderPass()
		{
		}

		void DrawSkyboxPass::Execute(ScriptableRenderContext& context, RenderingData& renderingData)
		{
			Camera& camera = *(renderingData.pCameraData->pCamera);
			context.DrawSkybox(camera);
		}
	}
}
