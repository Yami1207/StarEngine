#ifndef __DEFERRED_LIGHTS_H__
#define __DEFERRED_LIGHTS_H__

namespace StarEngine
{
	namespace Rendering
	{
		struct RenderingData;
		class ScriptableRenderContext;

		class DeferredLights
		{
		public:
			DeferredLights();
			~DeferredLights();

			void SetupLights(ScriptableRenderContext& context, RenderingData& renderingData);
		};
	}
}

#endif // !__DEFERRED_LIGHTS_H__

