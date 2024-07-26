#ifndef __DRAW_SKYBOX_PASS_H__
#define __DRAW_SKYBOX_PASS_H__

#include "RenderPipeline/ScriptableRender/ScriptableRenderPass.h"

namespace StarEngine
{
	namespace Rendering
	{
		class DrawSkyboxPass : public ScriptableRenderPass
		{
		public:
			DrawSkyboxPass();

			virtual void Execute(ScriptableRenderContext& context, RenderingData& renderingData) sealed;
		};
	}
}

#endif // !__DRAW_SKYBOX_PASS_H__
