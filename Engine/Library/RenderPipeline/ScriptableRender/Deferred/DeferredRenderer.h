#ifndef __DEFERRED_RENDERER_H__
#define __DEFERRED_RENDERER_H__

#include "RenderPipeline/ScriptableRender/ScriptableRenderer.h"

namespace StarEngine
{
	namespace Rendering
	{
		class DeferredLights;
		class DrawSkyboxPass;

		class DeferredRenderer : public ScriptableRenderer
		{
		public:
			DeferredRenderer();
			~DeferredRenderer();
		public:
			/// <summary>
			/// 清理
			/// </summary>
			virtual void Clear() sealed;

			virtual void Setup(ScriptableRenderContext& context, RenderingData& renderingData) sealed;
		protected:
			/// <summary>
			/// 设置灯光
			/// </summary>
			/// <param name="context"></param>
			/// <param name="renderingData"></param>
			virtual void SetupLights(ScriptableRenderContext& context, RenderingData& renderingData) sealed;
		private:
			DeferredLights*	m_pLights;

			DrawSkyboxPass*	m_pDrawSkyboxPass;
		};
	}
}

#endif // !__DEFERRED_RENDERER_H__
