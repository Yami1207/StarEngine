#include "D3DPrivate.h"
#include "D3DStateCache.h"

#include "D3DTypes.h"
#include "D3DUtility.h"

namespace StarEngine
{
	void D3DStateCache::Clear()
	{
		for (RasterizerStates::iterator iter = m_RasterizerStates.begin(); iter != m_RasterizerStates.end(); ++iter)
			*iter = sNull;
		m_RasterizerStateKey.clear();
		m_RasterizerStates.clear();

		for (BlendStates::iterator iter = m_BlendStates.begin(); iter != m_BlendStates.end(); ++iter)
			*iter = sNull;
		m_BlendStateKey.clear();
		m_BlendStates.clear();

		for (DepthStencilStates::iterator iter = m_DepthStencilStates.begin(); iter != m_DepthStencilStates.end(); ++iter)
			*iter = sNull;
		m_DepthStencilStateKey.clear();
		m_DepthStencilStates.clear();
	}

	Graphics::RasterizerStatePtr D3DStateCache::GetRasterizerState(const Graphics::RasterizerDesc& desc)
	{
		D3D11_RASTERIZER_DESC stateDesc;
		::memset(&stateDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
		stateDesc.FillMode = ToFileMode(desc.fillMode);
		stateDesc.CullMode = ToCullMode(desc.cullMode);
		stateDesc.FrontCounterClockwise = desc.frontCounterClockwise ? TRUE : FALSE;
		stateDesc.DepthBias = desc.depthBias;
		stateDesc.DepthBiasClamp = desc.depthBiasClamp;
		stateDesc.SlopeScaledDepthBias = desc.slopeScaledDepthBias;
		stateDesc.DepthClipEnable = desc.enableDepthClip ? TRUE : FALSE;
		stateDesc.ScissorEnable = desc.enableScissor ? TRUE : FALSE;
		stateDesc.MultisampleEnable = desc.enableMultisample ? TRUE : FALSE;
		stateDesc.AntialiasedLineEnable = desc.enableAntialiasedLine ? TRUE : FALSE;

		for (size_t i = 0; i < m_RasterizerStateKey.size(); ++i)
		{
			if (::memcmp(&m_RasterizerStateKey[i], &stateDesc, sizeof(D3D11_RASTERIZER_DESC)) == 0)
				return m_RasterizerStates[i];
		}

		Graphics::RasterizerStatePtr state = new D3DRasterizerState(stateDesc);
		m_RasterizerStateKey.push_back(stateDesc);
		m_RasterizerStates.push_back(state);
		return state;
	}

	Graphics::BlendStatePtr D3DStateCache::GetBlendState(const Graphics::BlendStateDesc& desc)
	{
		D3D11_BLEND_DESC stateDesc;
		::memset(&stateDesc, 0, sizeof(D3D11_BLEND_DESC));
		stateDesc.AlphaToCoverageEnable = FALSE;
		stateDesc.IndependentBlendEnable = desc.enableIndependentBlend ? TRUE : FALSE;

		//BOOL enable = desc.enable ? TRUE : FALSE;
		uint32 count = MAX_SUPPORTED_RENDER_TARGETS < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT ? MAX_SUPPORTED_RENDER_TARGETS : D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
		for (uint32 i = 0; i < count; ++i)
		{
			const Graphics::RenderTargetBlendStateDesc& rt = desc.rt[i];
			stateDesc.RenderTarget[i].BlendEnable = TRUE;
			stateDesc.RenderTarget[i].BlendOp = ToBlendOp(rt.blendOp);
			stateDesc.RenderTarget[i].SrcBlend = ToBlendMode(rt.srcBlend);
			stateDesc.RenderTarget[i].DestBlend = ToBlendMode(rt.dstBlend);
			stateDesc.RenderTarget[i].BlendOpAlpha = ToBlendOp(rt.blendOpAlpha);
			stateDesc.RenderTarget[i].SrcBlendAlpha = ToBlendMode(rt.srcBlendAlpha);
			stateDesc.RenderTarget[i].DestBlendAlpha = ToBlendMode(rt.dstBlendAlpha);
			stateDesc.RenderTarget[i].RenderTargetWriteMask = rt.writeMask;
		}

		for (size_t i = 0; i < m_BlendStateKey.size(); ++i)
		{
			if (::memcmp(&m_BlendStateKey[i], &stateDesc, sizeof(D3D11_BLEND_DESC)) == 0)
				return m_BlendStates[i];
		}

		Graphics::BlendStatePtr state = new D3DBlendState(stateDesc);
		m_BlendStateKey.push_back(stateDesc);
		m_BlendStates.push_back(state);
		return state;
	}

	Graphics::DepthStencilStatePtr D3DStateCache::GetDepthStencilState(const Graphics::DepthStencilDesc& desc)
	{
		D3D11_DEPTH_STENCIL_DESC stateDesc;
		::memset(&stateDesc, 0, sizeof(D3D11_DEPTH_STENCIL_DESC));

		stateDesc.DepthEnable = desc.enableDepth ? TRUE : FALSE;
		stateDesc.DepthWriteMask = desc.enableDepthWrite ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
		stateDesc.DepthFunc = ToCompareFunc(desc.depthFunc);

		stateDesc.StencilEnable = desc.enableStencil ? TRUE : FALSE;
		stateDesc.StencilReadMask = desc.stencilReadMask;
		stateDesc.StencilWriteMask = desc.stencilWriteMask;

		stateDesc.FrontFace.StencilFailOp = ToStencilOp(desc.frontFace.stencilFailOp);
		stateDesc.FrontFace.StencilDepthFailOp = ToStencilOp(desc.frontFace.stencilDepthFailOp);
		stateDesc.FrontFace.StencilPassOp = ToStencilOp(desc.frontFace.stencilPassOp);
		stateDesc.FrontFace.StencilFunc = ToCompareFunc(desc.frontFace.stencilFunc);

		stateDesc.BackFace.StencilFailOp = ToStencilOp(desc.backFace.stencilFailOp);
		stateDesc.BackFace.StencilDepthFailOp = ToStencilOp(desc.backFace.stencilDepthFailOp);
		stateDesc.BackFace.StencilPassOp = ToStencilOp(desc.backFace.stencilPassOp);
		stateDesc.BackFace.StencilFunc = ToCompareFunc(desc.backFace.stencilFunc);

		for (size_t i = 0; i < m_DepthStencilStateKey.size(); ++i)
		{
			if (::memcmp(&m_DepthStencilStateKey[i], &stateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC)) == 0)
				return m_DepthStencilStates[i];
		}

		Graphics::DepthStencilStatePtr state = new D3DDepthStencilState(stateDesc);
		m_DepthStencilStateKey.push_back(stateDesc);
		m_DepthStencilStates.push_back(state);
		return state;
	}
}
