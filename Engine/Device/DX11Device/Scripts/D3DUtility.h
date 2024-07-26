#ifndef __D3D_UTILS_H__
#define __D3D_UTILS_H__

#include "Graphics/GraphicsTypes.h"

namespace StarEngine
{
	class DeviceWindow;

	/// <summary>
	/// 初始化图形设备
	/// </summary>
	/// <param name="error">错误信息</param>
	/// <returns></returns>
	sBoolean InitializeDevice(std::string& error);

	/// <summary>
	/// 注销图形设备
	/// </summary>
	void DestroyDevice();

	/// <summary>
	/// 返回ID3D11Device对象
	/// </summary>
	/// <returns></returns>
	ID3D11Device* GetD3DDevice();

	/// <summary>
	/// 返回ID3D11DeviceContext对象
	/// </summary>
	/// <returns></returns>
	ID3D11DeviceContext* GetImmediateContext();

	/// <summary>
	/// 返回IDXGIFactory对象
	/// </summary>
	/// <returns></returns>
	IDXGIFactory* GetDXGIFactory();

	void SetActiveWindow(DeviceWindow* pWindow);

	DeviceWindow* GetActiveWindow();

	/// <summary>
	/// 初始化数据类型描述表
	/// </summary>
	/// <param name="desc">描述表</param>
	/// <param name="decl">顶点信息</param>
	void InitVertexInputLayout(D3D11_INPUT_ELEMENT_DESC& desc, const Graphics::VertexDeclaration& decl);

	/// <summary>
	/// 根据深度模板格式,返回DXGI_FORMAT类型
	/// </summary>
	/// <param name="format">深度模板格式</param>
	/// <returns></returns>
	DXGI_FORMAT GetDepthBufferFormat(Graphics::DepthBufferFormat format);

//	void TextureDownSampling(uint32 nWidth, uint32 nHeight, uint8* pDestData, const uint8* pSrcData);

	D3D11_COMPARISON_FUNC ToCompareFunc(CompareFunc compare);

	DXGI_FORMAT GetDXGIFormat(Graphics::GraphicsFormat format);

	D3D11_FILL_MODE ToFileMode(Graphics::FillMode mode);
	
	D3D11_CULL_MODE ToCullMode(Graphics::CullMode mode);

	D3D11_BLEND_OP ToBlendOp(Graphics::BlendOp op);

	D3D11_BLEND ToBlendMode(Graphics::BlendMode mode);

	D3D11_STENCIL_OP ToStencilOp(Graphics::StencilOp op);

//	D3D11_FILTER GetTextureFilter(GfxTextureFilter filter);
//
//	D3D11_TEXTURE_ADDRESS_MODE GetTextureAddress(GfxTextureAddress address);

	D3D11_PRIMITIVE_TOPOLOGY ToPrimitiveTopology(Graphics::PrimitiveTopology type);
}

#endif
