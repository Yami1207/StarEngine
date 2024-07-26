#ifndef __D3D_STATE_CACHE_H__
#define __D3D_STATE_CACHE_H__

#include <vector>
#include "Graphics/GraphicsTypes.h"

namespace StarEngine
{
	class D3DStateCache
	{
		using RasterizerStateKey = std::vector<D3D11_RASTERIZER_DESC>;
		using RasterizerStates = std::vector<Graphics::RasterizerStatePtr>;

		using BlendStateKey = std::vector<D3D11_BLEND_DESC>;
		using BlendStates = std::vector<Graphics::BlendStatePtr>;

		using DepthStencilStateKey = std::vector<D3D11_DEPTH_STENCIL_DESC>;
		using DepthStencilStates = std::vector<Graphics::DepthStencilStatePtr>;
	public:
		/// <summary>
		/// 释放内存
		/// </summary>
		void Clear();

		/// <summary>
		/// 获取光栅化状态
		/// </summary>
		/// <param name="desc">描述表</param>
		/// <returns></returns>
		Graphics::RasterizerStatePtr GetRasterizerState(const Graphics::RasterizerDesc& desc);

		/// <summary>
		/// 获取混合状态
		/// </summary>
		/// <param name="desc">混合状态描述表</param>
		/// <returns></returns>
		Graphics::BlendStatePtr GetBlendState(const Graphics::BlendStateDesc& desc);

		/// <summary>
		/// 获取模板缓冲区状态对象
		/// </summary>
		/// <param name="desc">描述表</param>
		/// <returns></returns>
		Graphics::DepthStencilStatePtr GetDepthStencilState(const Graphics::DepthStencilDesc& desc);
	private:
		RasterizerStateKey		m_RasterizerStateKey;
		RasterizerStates		m_RasterizerStates;

		BlendStateKey			m_BlendStateKey;
		BlendStates				m_BlendStates;

		DepthStencilStateKey	m_DepthStencilStateKey;
		DepthStencilStates		m_DepthStencilStates;
	};
}

#endif // !__D3D_STATE_CACHE_H__
