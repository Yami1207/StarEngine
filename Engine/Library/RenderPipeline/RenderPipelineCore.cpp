#include "EngineLibrary.h"
#include "RenderPipelineCore.h"

#include <vector>

#include "Runtime/Light/Light.h"
#include "Runtime/Transform/Transform.h"

namespace StarEngine
{
	namespace Rendering
	{
		namespace
		{
			static const Vector4 g_kDefaultLightPosition(0.0f, 0.0f, 1.0f, 0.0f);
			static const Color g_kDefaultLightColor = Color::black;
		}

		void RenderPipelineCore::InitializeLightConstants(Vector4& mainLightPosition, Color& mainLightColor)
		{
			Light* pMainLight = sNull;

			std::vector<Light*> lights;
			Light::GetLights(lights);
			uint32 count = (uint32)lights.size();
			if (count > 0)
			{
				for (uint32 i = 0; i < count; ++i)
				{
					Light* pLight = lights[i];
					if (pLight->GetLightType() != LightType::Directional)
						continue;
					if (pMainLight == sNull || pMainLight->GetIntensity() < pLight->GetIntensity())
						pMainLight = pLight;
				}
			}

			if (pMainLight)
			{
				Transform* pTransform = pMainLight->GetComponent<Transform>();
				Vector3 forward = pTransform->GetRotation().Forward();
				mainLightPosition = Vector4(-forward.x, -forward.y, -forward.z, 0.0f);

				Color lightColor = pMainLight->GetColor() * pMainLight->GetIntensity();
				lightColor.a = pMainLight->GetIntensity();
				mainLightColor = lightColor;
			}
			else
			{
				mainLightPosition = g_kDefaultLightPosition;
				mainLightColor = g_kDefaultLightColor;
			}
		}
	}
}
