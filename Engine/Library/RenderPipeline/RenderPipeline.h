#ifndef __RENDER_PIPELINE_H__
#define __RENDER_PIPELINE_H__

#include <vector>

#include "RenderPipelineTypes.h"

namespace StarEngine
{
	class Camera;

	namespace Rendering
	{
		class ScriptableRenderer;
		class ScriptableRenderContext;

		class RenderPipeline
		{
		public:
			RenderPipeline();
			virtual ~RenderPipeline();
		public:
			/// <summary>
			/// 执行渲染
			/// </summary>
			/// <param name="context"></param>
			/// <param name="cameraType">渲染相机的类型</param>
			/// <param name="cameras">相机列表</param>
						void Render(ScriptableRenderContext& context, std::vector<class Camera*>& cameras);

			/// <summary>
			/// 执行渲染（编辑器）
			/// </summary>
			/// <param name="context"></param>
			/// <param name="cameraType">渲染相机的类型</param>
			/// <param name="cameras">相机列表</param>
			void Render(ScriptableRenderContext& context, uint32 cameraType, std::vector<class Camera*>& cameras);
		private:
			/// <summary>
			/// 排序相机
			/// </summary>
			/// <param name="cameras">相机列表</param>
			void SortCameras(std::vector<class Camera*>& cameras);

			/// <summary>
			/// 渲染相机
			/// </summary>
			/// <param name="context"></param>
			/// <param name="cameraData">相机数据</param>
			void RenderSingleCamera(ScriptableRenderContext& context, CameraData& cameraData);
		private:
			ScriptableRenderer*	m_pRenderer;
		};
	}
}

#endif // !__RENDER_PIPELINE_H__
