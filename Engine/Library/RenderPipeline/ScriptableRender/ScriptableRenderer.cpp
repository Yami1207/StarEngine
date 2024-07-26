#include "EngineLibrary.h"
#include "ScriptableRenderer.h"

#include "RenderCore/RenderInterface.h"
#include "RenderPipeline/RenderPipelineTypes.h"

#include "ScriptableRenderPass.h"
#include "ScriptableRenderContext.h"

#include "Runtime/Camera/Camera.h"

namespace StarEngine
{
	namespace Rendering
	{
		void ScriptableRenderer::Clear()
		{
			m_ActiveRenderPassQueue.clear();
		}

		void ScriptableRenderer::Execute(ScriptableRenderContext& context, RenderingData& renderingData)
		{
			CameraData* pCameraData = renderingData.pCameraData;
			Camera* pCamera = pCameraData->pCamera;

			// 设置灯光
			SetupLights(context, renderingData);

			// 设置相机属性
			context.SetupCameraProperties(*pCamera);

			// 清屏操作
			if (pCamera->GetClearFlags() != CameraClearFlags::Nothing)
			{
				ENQUEUE_UNIQUE_RENDER_COMMAND(Clear, pCamera,
					{
						Camera* pCamera = (Camera*)pObject;
						CameraClearFlags cameraClearFlags = pCamera->GetClearFlags();
						uint32 clearFlags = 0;
						if (cameraClearFlags == CameraClearFlags::Color)
							clearFlags = (uint32)Graphics::ClearFlags::All;
						else if (cameraClearFlags == CameraClearFlags::Skybox || cameraClearFlags == CameraClearFlags::Depth)
							clearFlags = (uint32)Graphics::ClearFlags::DepthStencil;
						RenderCommand::Clear(clearFlags, pCamera->GetBackgroundColor(), 1.0f, 0);
					}
				);
			}

			for (std::vector<ScriptableRenderPass*>::iterator iter = m_ActiveRenderPassQueue.begin(); iter != m_ActiveRenderPassQueue.end(); ++iter)
				(*iter)->Execute(context, renderingData);

			DrawGizmos(context, pCamera);
		}

		void ScriptableRenderer::EnqueuePass(ScriptableRenderPass* pPass)
		{
			m_ActiveRenderPassQueue.push_back(pPass);
		}

		void ScriptableRenderer::SetupLights(ScriptableRenderContext& context, RenderingData& renderingData)
		{
		}

		void ScriptableRenderer::DrawGizmos(ScriptableRenderContext& context, Camera* pCamera)
		{
#ifdef EDITOR_ENABLED
			context.DrawGizmos(*pCamera);
#endif
		}
	}
}
