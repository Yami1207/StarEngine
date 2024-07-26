#include "EngineLibrary.h"
#include "RenderPipelineTypes.h"

#include "Shader/ShaderRegistry.h"
#include "Shader/Internal/BuiltinShaderProperties.h"

namespace StarEngine
{
	namespace Rendering
	{
		uint32 ShaderPropertyID::viewMatrix = ShaderPropertyInvalidIndex;
		uint32 ShaderPropertyID::projectionMatrix = ShaderPropertyInvalidIndex;
		uint32 ShaderPropertyID::viewProjectionMatrix = ShaderPropertyInvalidIndex;

		uint32 ShaderPropertyID::inverseViewMatrix = ShaderPropertyInvalidIndex;
		uint32 ShaderPropertyID::inverseProjectionMatrix = ShaderPropertyInvalidIndex;
		uint32 ShaderPropertyID::inverseViewProjectionMatrix = ShaderPropertyInvalidIndex;

		uint32 ShaderPropertyID::objectToWorldMatrix = ShaderPropertyInvalidIndex;
		uint32 ShaderPropertyID::worldToObjectMatrix = ShaderPropertyInvalidIndex;

		uint32 ShaderPropertyID::mainLightPosition = ShaderPropertyInvalidIndex;
		uint32 ShaderPropertyID::mainLightColor = ShaderPropertyInvalidIndex;

		void ShaderPropertyID::Initialize()
		{
			viewMatrix = ShaderRegistry::PropertyToID(g_BuiltinMatrixPropertyNames[(int32)ShaderBuiltinMatrixProperty::View]);
			projectionMatrix = ShaderRegistry::PropertyToID(g_BuiltinMatrixPropertyNames[(int32)ShaderBuiltinMatrixProperty::Projection]);
			viewProjectionMatrix = ShaderRegistry::PropertyToID(g_BuiltinMatrixPropertyNames[(int32)ShaderBuiltinMatrixProperty::ViewProjection]);

			inverseViewMatrix = ShaderRegistry::PropertyToID(g_BuiltinMatrixPropertyNames[(int32)ShaderBuiltinMatrixProperty::InvView]);
			inverseProjectionMatrix = ShaderRegistry::PropertyToID(g_BuiltinMatrixPropertyNames[(int32)ShaderBuiltinMatrixProperty::InvProjection]);
			inverseViewProjectionMatrix = ShaderRegistry::PropertyToID(g_BuiltinMatrixPropertyNames[(int32)ShaderBuiltinMatrixProperty::InvViewProjection]);

			objectToWorldMatrix = ShaderRegistry::PropertyToID(g_BuiltinMatrixPropertyNames[(int32)ShaderBuiltinMatrixProperty::ObjectToWorld]);
			worldToObjectMatrix = ShaderRegistry::PropertyToID(g_BuiltinMatrixPropertyNames[(int32)ShaderBuiltinMatrixProperty::WorldToObject]);

			mainLightPosition = ShaderRegistry::PropertyToID(g_BuiltinVectorPropertyNames[(uint32)ShaderBuiltinVectorProperty::MainLightPosition]);
			mainLightColor = ShaderRegistry::PropertyToID(g_BuiltinVectorPropertyNames[(uint32)ShaderBuiltinVectorProperty::MainLightColor]);
		}
	}
}
