#include "EngineLibrary.h"
#include "RenderPipeline.h"

#include <algorithm>

#include "Runtime/Camera/Camera.h"

#include "RenderPipeline/ScriptableRender/Deferred/DeferredRenderer.h"

namespace StarEngine
{
	namespace Rendering
	{
		namespace
		{
			static bool SortCamera(const Camera* pLeft, const Camera* pRight)
			{
				return pLeft->GetPriority() < pRight->GetPriority();
			}

			static void InitializeCameraData(Camera& camera, CameraData& cameraData)
			{
				cameraData.pCamera = &camera;

				cameraData.clearDepth = camera.GetClearFlags() != CameraClearFlags::Nothing;
			}

			static void InitializeRenderingData(CameraData& cameraData, RenderingData& renderingData)
			{
				renderingData.pCameraData = &cameraData;

				renderingData.enablePostProcess = sTrue;
			}
		}

		RenderPipeline::RenderPipeline()
		{
			m_pRenderer = new DeferredRenderer();
		}

		RenderPipeline::~RenderPipeline()
		{
			SAFE_DELETE(m_pRenderer);
		}

		void RenderPipeline::Render(ScriptableRenderContext& context, std::vector<class Camera*>& cameras)
		{
			SortCameras(cameras);

			CameraData cameraData;
			for (std::vector<class Camera*>::iterator iter = cameras.begin(); iter != cameras.end(); ++iter)
			{
				InitializeCameraData(*(*iter), cameraData);
				RenderSingleCamera(context, cameraData);
			}
		}

		void RenderPipeline::Render(ScriptableRenderContext& context, uint32 cameraType, std::vector<class Camera*>& cameras)
		{
			SortCameras(cameras);

			CameraData cameraData;
			for (std::vector<class Camera*>::iterator iter = cameras.begin(); iter != cameras.end(); ++iter)
			{
				Camera& camera = *(*iter);
				if (camera.GetCameraType() == (CameraType)cameraType)
				{
					InitializeCameraData(camera, cameraData);
					RenderSingleCamera(context, cameraData);
				}
			}
		}

		void RenderPipeline::SortCameras(std::vector<class Camera*>& cameras)
		{
			if (cameras.size() > 1)
				std::sort(cameras.begin(), cameras.end(), SortCamera);
		}

		void RenderPipeline::RenderSingleCamera(ScriptableRenderContext& context, CameraData& cameraData)
		{
			ASSERT_DEBUG(m_pRenderer);

			m_pRenderer->Clear();

			RenderingData renderingData;
			InitializeRenderingData(cameraData, renderingData);
			m_pRenderer->Setup(context, renderingData);
			m_pRenderer->Execute(context, renderingData);
		}
	}
}
