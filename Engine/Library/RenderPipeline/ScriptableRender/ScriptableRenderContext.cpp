#include "EngineLibrary.h"
#include "ScriptableRenderContext.h"

#include "Runtime/Camera/Camera.h"
#include "Runtime/Transform/Transform.h"

#include "RenderCore/RenderContext.h"
#include "RenderCore/RenderInterface.h"

#include "RenderPipeline/RenderPipelineTypes.h"
#include "RenderPipeline/Command/CommandBuffer.h"
#include "RenderPipeline/Command/CommandBufferPool.h"

#include "Shader/ShaderPropertySheet.h"

namespace StarEngine
{
	namespace Rendering
	{
		ScriptableRenderContext::ScriptableRenderContext()
		{
		}

		ScriptableRenderContext::~ScriptableRenderContext()
		{
		}

		void ScriptableRenderContext::SetupCameraProperties(Camera& camera)
		{
			SetCameraShaderVariables(camera);
		}

		void ScriptableRenderContext::ExecuteCommandBuffer(CommandBuffer* pCommandBuffer)
		{
			CommandBuffer* pCmd = CommandBufferPool::Instance()->Get();
			pCmd->Copy(*pCommandBuffer);
			ENQUEUE_UNIQUE_RENDER_COMMAND(ExecuteCommandBuffer, pCmd,
				{
					CommandBuffer* pCmd = (CommandBuffer*)pObject;
					pCmd->Execute();
					CommandBufferPool::Instance()->Release(pCmd);
				});
		}

		void ScriptableRenderContext::DrawSkybox(Camera& camera)
		{
			if (camera.GetClearFlags() == CameraClearFlags::Skybox)
			{
				ENQUEUE_UNIQUE_RENDER_COMMAND(RenderSkybox, &camera, { static_cast<Camera*>(pObject)->RenderSkybox(); });
			}
		}

		void ScriptableRenderContext::DrawGizmos(Camera& camera)
		{
			if (camera.GetCameraType() == CameraType::SceneView)
				;
		}

		void ScriptableRenderContext::Submit()
		{
			RenderInterface::FlushRenderingCommands();
		}

		void ScriptableRenderContext::SetCameraShaderVariables(Camera& camera)
		{
			CommandBuffer* pCommandBuffer = CommandBufferPool::Instance()->Get();

			// ����ռ䵽��׶�ռ�任����
			Matrix44 viewMatrix = camera.GetViewMatrix();
			pCommandBuffer->SetGlobalMatrix(ShaderPropertyID::viewMatrix, viewMatrix);

			// ����ռ䵽��׶�ռ�任�����
			Matrix44 inverseViewMatrix = Matrix44::Invert(viewMatrix);
			pCommandBuffer->SetGlobalMatrix(ShaderPropertyID::inverseViewMatrix, inverseViewMatrix);

			// ��׶�ռ䵽�ü��ռ�任����
			Matrix44 projectionMatrix = camera.GetProjectionMatrix();
			pCommandBuffer->SetGlobalMatrix(ShaderPropertyID::projectionMatrix, projectionMatrix);

			// ��׶�ռ䵽�ü��ռ�任�����
			Matrix44 inverseProjectionMatrix = Matrix44::Invert(projectionMatrix);
			pCommandBuffer->SetGlobalMatrix(ShaderPropertyID::inverseProjectionMatrix, inverseProjectionMatrix);

			// ����ռ䵽�ü��ռ�任����
			Matrix44 viewProjectionMatrix = viewMatrix * projectionMatrix;
			pCommandBuffer->SetGlobalMatrix(ShaderPropertyID::viewProjectionMatrix, viewProjectionMatrix);

			// ����ռ䵽�ü��ռ�任�����
			Matrix44 inverseViewProjection = inverseViewMatrix * inverseProjectionMatrix;
			pCommandBuffer->SetGlobalMatrix(ShaderPropertyID::inverseViewProjectionMatrix, inverseViewProjection);

			ExecuteCommandBuffer(pCommandBuffer);
			CommandBufferPool::Instance()->Release(pCommandBuffer);

			// ����������������
			ShaderPropertySheet* pSheet = RenderContext::Instance()->GetShaderPropertySheet(RenderContext::CameraConstantSheet);
			ENQUEUE_UNIQUE_RENDER_COMMAND(UploadCameraCB, pSheet,
				{
					ShaderPropertySheet* pSheet = static_cast<ShaderPropertySheet*>(pObject);
					pSheet->UploadConstantBufferData();
					pSheet->Apply();
				});
		}
	}
}
