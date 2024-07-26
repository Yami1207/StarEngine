#ifndef __RENDER_PIPELINE_CORE_H__
#define __RENDER_PIPELINE_CORE_H__

namespace StarEngine
{
	namespace Rendering
	{
		class RenderPipelineCore
		{
		public:
			static void InitializeLightConstants(Vector4& mainLightPosition, Color& mainLightColor);
		};
	}
}

#endif // !__RENDER_PIPELINE_CORE_H__
