#ifndef __SCRIPTABLE_RENDER_PASS_H__
#define __SCRIPTABLE_RENDER_PASS_H__

namespace StarEngine
{
	namespace Rendering
	{
		struct RenderingData;
		class ScriptableRenderContext;

		class ScriptableRenderPass
		{
		public:
			ScriptableRenderPass();
			virtual ~ScriptableRenderPass();
		public:
			virtual void Execute(ScriptableRenderContext& context, RenderingData& renderingData) = 0;
		};
	}
}

#endif // !__SCRIPTABLE_RENDER_PASS_H__
