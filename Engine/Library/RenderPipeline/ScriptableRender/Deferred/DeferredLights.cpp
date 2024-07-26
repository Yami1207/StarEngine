#include "EngineLibrary.h"
#include "DeferredLights.h"

#include "RenderCore/RenderContext.h"
#include "RenderCore/RenderInterface.h"

#include "Shader/ShaderPropertySheet.h"

#include "RenderPipeline/RenderPipelineCore.h"
#include "RenderPipeline/RenderPipelineTypes.h"

#include "RenderPipeline/Command/CommandBuffer.h"
#include "RenderPipeline/Command/CommandBufferPool.h"

#include "RenderPipeline/ScriptableRender/ScriptableRenderContext.h"

namespace StarEngine
{
	namespace Rendering
	{
		DeferredLights::DeferredLights()
		{
		}

		DeferredLights::~DeferredLights()
		{
		}

		void DeferredLights::SetupLights(ScriptableRenderContext& context, RenderingData& renderingData)
		{
			CommandBuffer* pCommandBuffer = CommandBufferPool::Instance()->Get();
			{
				Vector4 mainLightPosition;
				Color mainLightColor;
				RenderPipelineCore::InitializeLightConstants(mainLightPosition, mainLightColor);

				pCommandBuffer->SetGlobalVector(ShaderPropertyID::mainLightPosition, mainLightPosition);
				pCommandBuffer->SetGlobalColor(ShaderPropertyID::mainLightColor, mainLightColor);

				context.ExecuteCommandBuffer(pCommandBuffer);
			}
			CommandBufferPool::Instance()->Release(pCommandBuffer);

			// 添加相机常量缓存区
			ShaderPropertySheet* pSheet = RenderContext::Instance()->GetShaderPropertySheet(RenderContext::LightsConstantSheet);
			if (pSheet != sNull)
			{
				ENQUEUE_UNIQUE_RENDER_COMMAND(UploadLights, pSheet,
					{
						ShaderPropertySheet* pSheet = static_cast<ShaderPropertySheet*>(pObject);
						pSheet->UploadConstantBufferData();
						pSheet->Apply();
					});
			}
		}
	}
}
