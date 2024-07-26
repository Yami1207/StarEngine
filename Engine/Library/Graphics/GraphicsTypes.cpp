#include "Core/BaseTypes.h"
#include "Core/BaseEnums.h"
#include "Core/Macros.h"

#include "Core/Math/Vector3.h"
#include "Core/Math/Vector4.h"

#include "GraphicsTypes.h"

namespace StarEngine
{
	namespace Graphics
	{
		//////////////////////////////////////////////////////////////////////////
		RasterizerDesc::RasterizerDesc() : fillMode(FillMode::Solid), cullMode(CullMode::Back), frontCounterClockwise(sTrue), depthBias(0), depthBiasClamp(0.0f),
			slopeScaledDepthBias(0.0f), enableDepthClip(sTrue), enableScissor(sFalse), enableMultisample(sFalse), enableAntialiasedLine(sFalse)
		{
		}

		//////////////////////////////////////////////////////////////////////////
		RenderTargetBlendStateDesc::RenderTargetBlendStateDesc() : blendOp(BlendOp::Add), srcBlend(BlendMode::One), dstBlend(BlendMode::Zero),
			blendOpAlpha(BlendOp::Add), srcBlendAlpha(BlendMode::One), dstBlendAlpha(BlendMode::Zero), writeMask(ColorWriteMask::ColorWriteAll)
		{
		}

		//////////////////////////////////////////////////////////////////////////
		BlendStateDesc::BlendStateDesc() : enableIndependentBlend(sFalse)
		{
		}

		//////////////////////////////////////////////////////////////////////////
		DepthStencilOpDesc::DepthStencilOpDesc() : stencilFailOp(StencilOp::Keep), stencilDepthFailOp(StencilOp::Keep), stencilPassOp(StencilOp::Keep), stencilFunc(CompareFunc::Always)
		{
		}

		//////////////////////////////////////////////////////////////////////////
		DepthStencilDesc::DepthStencilDesc() : enableDepth(sTrue), enableDepthWrite(sTrue), depthFunc(CompareFunc::LessEqual), enableStencil(sFalse), stencilReadMask(0xff), stencilWriteMask(0xff)
		{
		}

		//////////////////////////////////////////////////////////////////////////
		uint32 ToPrimitives(PrimitiveTopology type, uint32 count)
		{
			switch (type)
			{
			case PrimitiveTopology::Points:			return count;
			case PrimitiveTopology::Lines:			return count >> 1;
			case PrimitiveTopology::LineStrip:		return count - 1;
			case PrimitiveTopology::Triangles:		return count / 3;
			case PrimitiveTopology::TriangleStrip:	return count - 2;
			case PrimitiveTopology::Quads:			return count >> 2;
			}
			return 0;
		}

		uint32 ToDrawCount(PrimitiveTopology type, uint32 primitives)
		{
			switch (type)
			{
			case PrimitiveTopology::Points:			return primitives;
			case PrimitiveTopology::Lines:			return primitives << 1;
			case PrimitiveTopology::LineStrip:		return primitives + 1;
			case PrimitiveTopology::Triangles:		return primitives * 3;
			case PrimitiveTopology::TriangleStrip:	return primitives + 2;
			case PrimitiveTopology::Quads:			return primitives * 4;
			}
			return 0;
		}
	}
}
