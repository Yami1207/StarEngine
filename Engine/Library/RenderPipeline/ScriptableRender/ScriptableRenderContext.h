#ifndef __SCRIPTABLE_RENDER_CONTEXT_H__
#define __SCRIPTABLE_RENDER_CONTEXT_H__

namespace StarEngine
{
	class Camera;

	namespace Rendering
	{
		class CommandBuffer;

		class ScriptableRenderContext
		{
		public:
			ScriptableRenderContext();
			~ScriptableRenderContext();
		public:
			/// <summary>
			/// 设置相机属性
			/// </summary>
			/// <param name="camera">相机对象</param>
			void SetupCameraProperties(Camera& camera);

			/// <summary>
			/// 执行命令
			/// </summary>
			/// <param name="pCommandBuffer">命令</param>
			void ExecuteCommandBuffer(CommandBuffer* pCommandBuffer);

			/// <summary>
			/// 渲染天空
			/// </summary>
			/// <param name="camera">相机对象</param>
			void DrawSkybox(Camera& camera);

			void DrawGizmos(Camera& camera);

			void Submit();
		private:
			/// <summary>
			/// 设置Shader中的相机变量
			/// </summary>
			/// <param name="camera">相机对象</param>
			void SetCameraShaderVariables(Camera& camera);
		};
	}
}

#endif // !__SCRIPTABLE_RENDER_CONTEXT_H__

