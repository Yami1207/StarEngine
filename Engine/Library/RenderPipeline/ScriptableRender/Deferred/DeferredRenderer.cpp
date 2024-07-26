#include "EngineLibrary.h"
#include "DeferredRenderer.h"

#include "DeferredLights.h"

#include "RenderPipeline/ScriptableRender/Passes/DrawSkyboxPass.h"

namespace StarEngine
{
	namespace Rendering
	{
		DeferredRenderer::DeferredRenderer()
		{
			m_pLights = new DeferredLights();
			m_pDrawSkyboxPass = new DrawSkyboxPass();
		}

		DeferredRenderer::~DeferredRenderer()
		{
			SAFE_DELETE(m_pLights);
			SAFE_DELETE(m_pDrawSkyboxPass);
		}

		void DeferredRenderer::Clear()
		{
			ScriptableRenderer::Clear();
		}

		void DeferredRenderer::Setup(ScriptableRenderContext& context, RenderingData& renderingData)
		{
			EnqueuePass(m_pDrawSkyboxPass);
		}

		void DeferredRenderer::SetupLights(ScriptableRenderContext& context, RenderingData& renderingData)
		{
			m_pLights->SetupLights(context, renderingData);
		}
	}
}
