#ifndef __SCRIPTABLE_RENDERER_H__
#define __SCRIPTABLE_RENDERER_H__

#include <vector>

namespace StarEngine
{
	class Camera;

	namespace Rendering
	{
		struct RenderingData;
		class ScriptableRenderPass;
		class ScriptableRenderContext;

		class ScriptableRenderer
		{
		public:
			virtual ~ScriptableRenderer() {}
		public:
			/// <summary>
			/// 清理
			/// </summary>
			virtual void Clear();

			virtual void Setup(ScriptableRenderContext& context, RenderingData& renderingData) = 0;

			virtual void Execute(ScriptableRenderContext& context, RenderingData& renderingData);
		protected:
			/// <summary>
			/// 添加渲染操作
			/// </summary>
			/// <param name="pPass"></param>
			void EnqueuePass(ScriptableRenderPass* pPass);

			/// <summary>
			/// 设置灯光
			/// </summary>
			/// <param name="context"></param>
			/// <param name="renderingData"></param>
			virtual void SetupLights(ScriptableRenderContext& context, RenderingData& renderingData);

			/// <summary>
			/// 绘制工具
			/// </summary>
			/// <param name="context"></param>
			/// <param name="renderingData"></param>
			void DrawGizmos(ScriptableRenderContext& context, Camera* pCamera);
		private:
			std::vector<ScriptableRenderPass*>	m_ActiveRenderPassQueue;
		};
	}
}

#endif // !__SCRIPTABLE_RENDER_H__
