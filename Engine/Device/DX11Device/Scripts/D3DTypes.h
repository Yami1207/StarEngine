#ifndef __D3D_TYPES_H__
#define __D3D_TYPES_H__

#include "Graphics/GraphicsTypes.h"

namespace StarEngine
{
	struct BaseRenderSurface
	{
		BaseRenderSurface();
		virtual ~BaseRenderSurface();

		virtual void Release();

		uint32	width;
		uint32	height;
	};

	struct RenderColorSurface : public BaseRenderSurface
	{
		RenderColorSurface();

		virtual void Release() sealed;

		ID3D11Texture2D* pTexture;
		ID3D11RenderTargetView* pRenderTargetView;
	};

	struct RenderDepthSurface : public BaseRenderSurface
	{
		RenderDepthSurface();

		virtual void Release() sealed;

		ID3D11Texture2D* pTexture;
		ID3D11DepthStencilView* pDepthStencilView;
	};

	class D3DRasterizerState : public Graphics::IRasterizerState
	{
	public:
		D3DRasterizerState(const D3D11_RASTERIZER_DESC& desc);
		~D3DRasterizerState();

		/// <summary>
		/// 应用状态
		/// </summary>
		/// <returns></returns>
		virtual void Apply() sealed;
	private:
		ID3D11RasterizerState*	m_pState;
	};

	class D3DBlendState : public Graphics::IBlendState
	{
	public:
		D3DBlendState(const D3D11_BLEND_DESC& desc);
		~D3DBlendState();

		/// <summary>
		/// 应用状态
		/// </summary>
		/// <param name="factor">混合因子</param>
		/// <param name="mask">采样</param>
		virtual void Apply(const Vector4& factor = Vector4::zero, uint32 mask = 0xffffffff) sealed;
	private:
		ID3D11BlendState*	m_pState;
	};

	class D3DDepthStencilState : public Graphics::IDepthStencilState
	{
	public:
		D3DDepthStencilState(const D3D11_DEPTH_STENCIL_DESC& desc);
		~D3DDepthStencilState();

		/// <summary>
		/// 应用状态
		/// </summary>
		/// <param name="ref">模板参考值</param>
		virtual void Apply(uint32 ref = 0) sealed;
	private:
		ID3D11DepthStencilState*	m_pState;
	};

	class D3DInputLayout :public Graphics::IInputLayout
	{
	public:
		D3DInputLayout(ID3D11InputLayout* pLayout);
		~D3DInputLayout();
	public:
		ID3D11InputLayout*	m_pInputLayout;
	};

	class D3DVertexShader : public Graphics::IVertexShader
	{
	public:
		D3DVertexShader(ID3DBlob* pCode, ID3D11VertexShader* pShader);
		~D3DVertexShader();
	public:
		ID3DBlob*			m_pShaderCode;
		ID3D11VertexShader*	m_pShader;
	};

	class D3DPixelShader : public Graphics::IPixelShader
	{
	public:
		D3DPixelShader(ID3D11PixelShader* pShader);
		~D3DPixelShader();
	public:
		ID3D11PixelShader*	m_pShader;
	};

	class D3DVertexBuffer : public Graphics::IVertexBuffer
	{
	public:
		D3DVertexBuffer(uint32 byteWidth, sBoolean isDynamic, void* pData);
		~D3DVertexBuffer();

		/// <summary>
		/// 是否有效
		/// </summary>
		/// <returns></returns>
		virtual sBoolean IsValid() sealed;

		/// <summary>
		/// 返回数据大小
		/// </summary>
		/// <returns></returns>
		virtual uint32 DataBytes() sealed;
	public:
		ID3D11Buffer*	m_pBuffer;
	};

	class D3DVertexIndexBuffer : public Graphics::IVertexIndexBuffer
	{
	public:
		D3DVertexIndexBuffer(DXGI_FORMAT format, uint32 byteWidth, sBoolean isDynamic, void* pData);
		~D3DVertexIndexBuffer();

		/// <summary>
		/// 是否有效
		/// </summary>
		/// <returns></returns>
		virtual sBoolean IsValid() sealed;

		/// <summary>
		/// 返回数据大小
		/// </summary>
		/// <returns></returns>
		virtual uint32 DataBytes() sealed;
	public:
		DXGI_FORMAT		m_Format;
		ID3D11Buffer*	m_pBuffer;
	};

	class D3DConstantBuffer : public Graphics::IConstantBuffer
	{
	public:
		D3DConstantBuffer(uint32 byteWidth);
		~D3DConstantBuffer();

		/// <summary>
		/// 设置数据
		/// </summary>
		/// <param name="pData"></param>
		/// <param name="size"></param>
		virtual void SetData(const void* pData, uint32 size) sealed;

		/// <summary>
		/// 绑定常量缓冲区
		/// </summary>
		/// <param name="slot">寄存器索引</param>
		virtual void Bind(uint32 slot) sealed;

		/// <summary>
		/// 是否有效
		/// </summary>
		/// <returns></returns>
		virtual sBoolean IsValid() sealed;

		/// <summary>
		/// 返回数据大小
		/// </summary>
		/// <returns></returns>
		virtual uint32 DataBytes() sealed;
	private:
		uint32			m_BufferSize;
		ID3D11Buffer*	m_pBuffer;
	};
}

//namespace StarEngine
//{
//	class RasterState : public IGfxRasterState
//	{
//	public:
//		RasterState(ID3D11RasterizerState* pState);
//		virtual ~RasterState();
//
//		INLINE ID3D11RasterizerState* State() { return m_pState; }
//	private:
//		ID3D11RasterizerState*	m_pState;
//	};
//
//	class BlendState : public IGfxBlendState
//	{
//	public:
//		BlendState(ID3D11BlendState* pState);
//		virtual ~BlendState();
//
//		INLINE ID3D11BlendState* State() { return m_pState; }
//	protected:
//		ID3D11BlendState*	m_pState;
//	};
//
//	class DepthStencilState : public IGfxDepthStencilState
//	{
//	public:
//		DepthStencilState(ID3D11DepthStencilState* pState);
//		virtual ~DepthStencilState();
//
//		INLINE ID3D11DepthStencilState* State() { return m_pState; }
//	protected:
//		ID3D11DepthStencilState * m_pState;
//	};
//
//	class TextureSampler : public IGfxTextureSampler
//	{
//	public:
//		TextureSampler(ID3D11SamplerState* pState);
//		virtual ~TextureSampler();
//
//		INLINE ID3D11SamplerState* State() { return m_pState; }
//	protected:
//		ID3D11SamplerState*	m_pState;
//	};
//
//	class IBaseTexture : public IGfxTexture
//	{
//	public:
//		/**
//		*	返回视图指针对象
//		*/
//		virtual ID3D11ShaderResourceView* ResourceView() = 0;
//	};
//
//	class Texture2D : public IBaseTexture
//	{
//	public:
//		Texture2D(uint32 levels, ID3D11Texture2D* pTexture, ID3D11ShaderResourceView* pResourceView);
//		virtual ~Texture2D();
//
//		virtual sBoolean Read(uint32 level, uint32 bytes, uint8* pBuffer) sealed;
//
//		virtual ID3D11ShaderResourceView* ResourceView() sealed;
//	private:
//		ID3D11Texture2D*			m_pTexture;
//		ID3D11ShaderResourceView*	m_pResourceView;
//	};
//
//	class Texture3D : public IBaseTexture
//	{
//	public:
//		Texture3D(ID3D11Texture3D* pTexture, ID3D11ShaderResourceView* pResourceView);
//		virtual ~Texture3D();
//
//		virtual sBoolean Read(uint32 level, uint32 bytes, uint8* pBuffer) sealed;
//
//		virtual ID3D11ShaderResourceView* ResourceView() sealed;
//	private:
//		ID3D11Texture3D*			m_pTexture;
//		ID3D11ShaderResourceView*	m_pResourceView;
//	};
//
//	class RenderTexture : public IBaseTexture
//	{
//	public:
//		RenderTexture(ID3D11Texture2D*, ID3D11RenderTargetView*, ID3D11ShaderResourceView*, ID3D11Texture2D*, ID3D11DepthStencilView*, ID3D11ShaderResourceView*);
//		virtual ~RenderTexture();
//
//		virtual sBoolean Read(uint32 level, uint32 bytes, uint8* pBuffer) sealed;
//
//		virtual ID3D11ShaderResourceView* ResourceView() sealed;
//
//		ID3D11RenderTargetView* RenderTargetView();
//
//		ID3D11DepthStencilView* DepthStencilView();
//	private:
//		ID3D11Texture2D*			m_pTexture;
//		ID3D11RenderTargetView*		m_pRenderTargetView;
//		ID3D11ShaderResourceView*	m_pRenderTargetResource;
//
//		ID3D11Texture2D*			m_pDepthStencil;
//		ID3D11DepthStencilView*		m_pDepthStencilView;
//		ID3D11ShaderResourceView*	m_pDepthStencilResource;
//	};
//
//	class VertexLayer : public IGfxVertexLayer
//	{
//	public:
//		VertexLayer(ID3D11InputLayout* pInputLayout);
//		virtual ~VertexLayer();
//
//		INLINE ID3D11InputLayout* InputLayout() const { return m_pInputLayout; }
//	private:
//		ID3D11InputLayout*	m_pInputLayout;
//	};
//
//	class VertexBuffer : public IGfxVertexBuffer
//	{
//		friend class GraphicsDevice;
//	public:
//		VertexBuffer(ID3D11Buffer* pBuffer);
//		virtual ~VertexBuffer();
//
//		virtual sBoolean Map(void** ppData, sBoolean isDiscard) sealed;
//
//		virtual void Unmap() sealed;
//
//		INLINE ID3D11Buffer* Buffer() const { return m_pBuffer; }
//	private:
//		ID3D11Buffer*	m_pBuffer;
//	};
//
//	class VertexIndexBuffer : public IGfxVertexIndexBuffer
//	{
//	public:
//		VertexIndexBuffer(ID3D11Buffer* pBuffer);
//		virtual ~VertexIndexBuffer();
//
//		virtual sBoolean Map(void** ppData, sBoolean isDiscard) sealed;
//
//		virtual void Unmap() sealed;
//
//		INLINE ID3D11Buffer* Buffer() const { return m_pBuffer; }
//	private:
//		ID3D11Buffer*	m_pBuffer;
//	};
//
//	class ConstantBuffer : public IGfxConstantBuffer
//	{
//	public:
//		ConstantBuffer(ID3D11Buffer* pBuffer);
//		virtual ~ConstantBuffer();
//
//		virtual sBoolean Map(void** ppData, sBoolean isDiscard) sealed;
//
//		virtual void Unmap() sealed;
//
//		INLINE ID3D11Buffer* Buffer() const { return m_pBuffer; }
//	private:
//		ID3D11Buffer*	m_pBuffer;
//	};
//
//	class VertexShader : public IGfxShader
//	{
//	public:
//		VertexShader(ID3DBlob* pShaderCode, ID3D11VertexShader* pShader);
//		virtual ~VertexShader();
//	public:
//		virtual GfxShaderType Type() const sealed;
//
//		INLINE ID3DBlob* ShaderCode() { return m_pShaderCode; }
//
//		INLINE ID3D11VertexShader* Shader() { return m_pShader; }
//	private:
//		ID3DBlob*			m_pShaderCode;
//		ID3D11VertexShader*	m_pShader;
//	};
//
//	class PixelShader : public IGfxShader
//	{
//	public:
//		PixelShader(ID3D11PixelShader* pShader);
//		virtual ~PixelShader();
//
//		virtual GfxShaderType Type() const sealed;
//
//		INLINE ID3D11PixelShader* Shader() { return m_pShader; }
//	private:
//		ID3D11PixelShader*	m_pShader;
//	};
//
//	class GeometryShader : public IGfxShader
//	{
//	public:
//		GeometryShader(ID3D11GeometryShader* pShader);
//		virtual ~GeometryShader();
//
//		virtual GfxShaderType Type() const sealed;
//
//		INLINE ID3D11GeometryShader* Shader() { return m_pShader; }
//	private:
//		ID3D11GeometryShader*	m_pShader;
//	};
//}

#endif
