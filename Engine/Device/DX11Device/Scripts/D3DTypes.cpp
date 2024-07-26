#include "D3DPrivate.h"
#include "D3DTypes.h"

#include "D3DUtility.h"

namespace StarEngine
{
	//////////////////////////////////////////////////////////////////////////
	BaseRenderSurface::BaseRenderSurface() : width(0), height(0)
	{
	}

	BaseRenderSurface::~BaseRenderSurface()
	{
		Release();
	}

	void BaseRenderSurface::Release()
	{
	}

	//////////////////////////////////////////////////////////////////////////
	RenderColorSurface::RenderColorSurface() : BaseRenderSurface(), pTexture(sNull), pRenderTargetView(sNull)
	{
	}

	void RenderColorSurface::Release()
	{
		SAFE_RELEASE(pTexture);
		SAFE_RELEASE(pRenderTargetView);
	}

	//////////////////////////////////////////////////////////////////////////
	RenderDepthSurface::RenderDepthSurface() : BaseRenderSurface(), pTexture(sNull), pDepthStencilView(sNull)
	{
	}

	void RenderDepthSurface::Release()
	{
		SAFE_RELEASE(pTexture);
		SAFE_RELEASE(pDepthStencilView);
	}

	//////////////////////////////////////////////////////////////////////////
	D3DRasterizerState::D3DRasterizerState(const D3D11_RASTERIZER_DESC& desc) : m_pState(sNull)
	{
		GetD3DDevice()->CreateRasterizerState(&desc, &m_pState);
	}

	D3DRasterizerState::~D3DRasterizerState()
	{
		SAFE_RELEASE(m_pState);
	}

	void D3DRasterizerState::Apply()
	{
		if (m_pState != sNull)
			GetImmediateContext()->RSSetState(m_pState);
	}

	//////////////////////////////////////////////////////////////////////////
	D3DBlendState::D3DBlendState(const D3D11_BLEND_DESC& desc) : m_pState(sNull)
	{
		GetD3DDevice()->CreateBlendState(&desc, &m_pState);
	}

	D3DBlendState::~D3DBlendState()
	{
		SAFE_RELEASE(m_pState);
	}

	void D3DBlendState::Apply(const Vector4& factor /*= Vector4::zero*/, uint32 mask /*= 0xffffffff*/)
	{
		if (m_pState != sNull)
			GetImmediateContext()->OMSetBlendState(m_pState, (F32*)&factor, mask);
	}

	//////////////////////////////////////////////////////////////////////////
	D3DDepthStencilState::D3DDepthStencilState(const D3D11_DEPTH_STENCIL_DESC& desc) : m_pState(sNull)
	{
		GetD3DDevice()->CreateDepthStencilState(&desc, &m_pState);
	}

	D3DDepthStencilState::~D3DDepthStencilState()
	{
		SAFE_RELEASE(m_pState);
	}

	void D3DDepthStencilState::Apply(uint32 ref /*= 0*/)
	{
		if (m_pState != sNull)
			GetImmediateContext()->OMSetDepthStencilState(m_pState, ref);
	}

	//////////////////////////////////////////////////////////////////////////
	D3DInputLayout::D3DInputLayout(ID3D11InputLayout* pLayout) : m_pInputLayout(pLayout)
	{
	}
	
	D3DInputLayout::~D3DInputLayout()
	{
		SAFE_RELEASE(m_pInputLayout);
	}

	//////////////////////////////////////////////////////////////////////////
	D3DVertexShader::D3DVertexShader(ID3DBlob* pCode, ID3D11VertexShader* pShader) : m_pShaderCode(pCode), m_pShader(pShader)
	{
	}

	D3DVertexShader::~D3DVertexShader()
	{
		SAFE_RELEASE(m_pShaderCode);
		SAFE_RELEASE(m_pShader);
	}

	//////////////////////////////////////////////////////////////////////////
	D3DPixelShader::D3DPixelShader(ID3D11PixelShader* pShader) : m_pShader(pShader)
	{
	}

	D3DPixelShader::~D3DPixelShader()
	{
		SAFE_RELEASE(m_pShader);
	}

	//////////////////////////////////////////////////////////////////////////
	D3DVertexBuffer::D3DVertexBuffer(uint32 byteWidth, sBoolean isDynamic, void* pData) : m_pBuffer(sNull)
	{
		D3D11_BUFFER_DESC desc;
		::memset(&desc, 0, sizeof(desc));
		desc.Usage = isDynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE;
		desc.ByteWidth = byteWidth;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = isDynamic ? D3D11_CPU_ACCESS_WRITE : 0;

		if (pData != sNull)
		{
			D3D11_SUBRESOURCE_DATA subresource;
			::memset(&subresource, 0, sizeof(subresource));
			subresource.pSysMem = pData;
			GetD3DDevice()->CreateBuffer(&desc, &subresource, &m_pBuffer);
		}
		else
		{
			GetD3DDevice()->CreateBuffer(&desc, sNull, &m_pBuffer);
		}
	}

	D3DVertexBuffer::~D3DVertexBuffer()
	{
		SAFE_RELEASE(m_pBuffer);
	}

	sBoolean D3DVertexBuffer::IsValid()
	{
		return m_pBuffer != sNull;
	}

	uint32 D3DVertexBuffer::DataBytes()
	{
		D3D11_BUFFER_DESC desc;
		m_pBuffer->GetDesc(&desc);
		return desc.ByteWidth;
	}

	//////////////////////////////////////////////////////////////////////////
	D3DVertexIndexBuffer::D3DVertexIndexBuffer(DXGI_FORMAT format, uint32 byteWidth, sBoolean isDynamic, void* pData) : m_Format(format)
	{
		D3D11_BUFFER_DESC desc;
		::memset(&desc, 0, sizeof(desc));
		desc.Usage = isDynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE;
		desc.ByteWidth = byteWidth;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = isDynamic ? D3D11_CPU_ACCESS_WRITE : 0;

		if (pData != sNull)
		{
			D3D11_SUBRESOURCE_DATA subresource;
			::memset(&subresource, 0, sizeof(subresource));
			subresource.pSysMem = pData;
			GetD3DDevice()->CreateBuffer(&desc, &subresource, &m_pBuffer);
		}
		else
		{
			GetD3DDevice()->CreateBuffer(&desc, sNull, &m_pBuffer);
		}
	}

	D3DVertexIndexBuffer::~D3DVertexIndexBuffer()
	{
		SAFE_RELEASE(m_pBuffer);
	}

	sBoolean D3DVertexIndexBuffer::IsValid()
	{
		return m_pBuffer != sNull;
	}

	uint32 D3DVertexIndexBuffer::DataBytes()
	{
		D3D11_BUFFER_DESC desc;
		m_pBuffer->GetDesc(&desc);
		return desc.ByteWidth;
	}

	//////////////////////////////////////////////////////////////////////////
	D3DConstantBuffer::D3DConstantBuffer(uint32 byteWidth) : m_BufferSize(byteWidth), m_pBuffer(sNull)
	{
		D3D11_BUFFER_DESC desc;
		::memset(&desc, 0, sizeof(desc));
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = byteWidth;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetD3DDevice()->CreateBuffer(&desc, sNull, &m_pBuffer);
	}

	D3DConstantBuffer::~D3DConstantBuffer()
	{
		SAFE_RELEASE(m_pBuffer);
	}

	void D3DConstantBuffer::SetData(const void* pData, uint32 size)
	{
		if (!IsValid())
			return;

		D3D11_MAPPED_SUBRESOURCE resource;
		::memset(&resource, 0, sizeof(D3D11_MAPPED_SUBRESOURCE));
		ID3D11DeviceContext* pImmediateContext = GetImmediateContext();
		HRESULT hResult = pImmediateContext->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		if(SUCCEEDED(hResult))
		{
			::memcpy(resource.pData, pData, MathLib::Min(size, m_BufferSize));
			pImmediateContext->Unmap(m_pBuffer, 0);
		}
	}

	void D3DConstantBuffer::Bind(uint32 slot)
	{
		if (IsValid())
		{
			ID3D11DeviceContext* pImmediateContext = GetImmediateContext();
			pImmediateContext->VSSetConstantBuffers(slot, 1, &m_pBuffer);
			pImmediateContext->PSSetConstantBuffers(slot, 1, &m_pBuffer);
			pImmediateContext->GSSetConstantBuffers(slot, 1, &m_pBuffer);
		}
	}

	sBoolean D3DConstantBuffer::IsValid()
	{
		return m_pBuffer != sNull ? sTrue : sFalse;
	}

	uint32 D3DConstantBuffer::DataBytes()
	{
		return m_BufferSize;
	}
}

//namespace StarEngine
//{
//	extern ID3D11Device* g_pD3DDevice;
//	extern ID3D11DeviceContext*	g_pImmediateContext;
//
//	//////////////////////////////////////////////////////////////////////////
//	RasterState::RasterState(ID3D11RasterizerState* pState) : m_pState(pState)
//	{
//	}
//
//	RasterState::~RasterState()
//	{
//		SAFE_RELEASE(m_pState);
//	}
//
//	//////////////////////////////////////////////////////////////////////////
//	BlendState::BlendState(ID3D11BlendState* pState) : m_pState(pState)
//	{
//	}
//
//	BlendState::~BlendState()
//	{
//		SAFE_RELEASE(m_pState);
//	}
//
//	//////////////////////////////////////////////////////////////////////////
//	DepthStencilState::DepthStencilState(ID3D11DepthStencilState* pState) : m_pState(pState)
//	{
//	}
//
//	DepthStencilState::~DepthStencilState()
//	{
//		SAFE_RELEASE(m_pState);
//	}
//
//	//////////////////////////////////////////////////////////////////////////
//	TextureSampler::TextureSampler(ID3D11SamplerState* pState) : m_pState(pState)
//	{
//	}
//
//	TextureSampler::~TextureSampler()
//	{
//		SAFE_RELEASE(m_pState);
//	}
//
//	//////////////////////////////////////////////////////////////////////////
//	Texture2D::Texture2D(uint32 levels, ID3D11Texture2D* pTexture, ID3D11ShaderResourceView* pResourceView) : m_pTexture(pTexture), m_pResourceView(pResourceView)
//	{
//	}
//
//	Texture2D::~Texture2D()
//	{
//		SAFE_RELEASE(m_pResourceView);
//		SAFE_RELEASE(m_pTexture);
//	}
//
//	sBoolean Texture2D::Read(uint32 level, uint32 bytes, uint8* pBuffer)
//	{
//		D3D11_TEXTURE2D_DESC textureDesc;
//		MemorySet(&textureDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));
//		m_pTexture->GetDesc(&textureDesc);
//		textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
//		textureDesc.Usage = D3D11_USAGE_STAGING;
//		textureDesc.BindFlags = 0;
//		textureDesc.MiscFlags = 0;
//
//		ID3D11Texture2D* pTextureBuffer = sNull;
//		if (FAILED(g_pD3DDevice->CreateTexture2D(&textureDesc, sNull, &pTextureBuffer)))
//			return sFalse;
//
//		//复制资源
//		g_pImmediateContext->CopyResource(pTextureBuffer, m_pTexture);
//
//		//
//		D3D11_MAPPED_SUBRESOURCE mapped_resource;
//		MemorySet(&mapped_resource, 0, sizeof(D3D11_MAPPED_SUBRESOURCE));
//		if (SUCCEEDED(g_pImmediateContext->Map(pTextureBuffer, level, D3D11_MAP_READ, 0, &mapped_resource)))
//		{
//			MemoryCopy(pBuffer, mapped_resource.pData, bytes);
//			g_pImmediateContext->Unmap(pTextureBuffer, level);
//		}
//
//		SAFE_RELEASE(pTextureBuffer);
//		return sTrue;
//	}
//
//	ID3D11ShaderResourceView* Texture2D::ResourceView()
//	{
//		return m_pResourceView;
//	}
//
//	//////////////////////////////////////////////////////////////////////////
//	Texture3D::Texture3D(ID3D11Texture3D* pTexture, ID3D11ShaderResourceView* pResourceView) : m_pTexture(pTexture), m_pResourceView(pResourceView)
//	{
//	}
//
//	Texture3D::~Texture3D()
//	{
//		SAFE_RELEASE(m_pResourceView);
//		SAFE_RELEASE(m_pTexture);
//	}
//
//	sBoolean Texture3D::Read(uint32 level, uint32 bytes, uint8* pBuffer)
//	{
//		D3D11_TEXTURE3D_DESC desc;
//		MemorySet(&desc, 0, sizeof(D3D11_TEXTURE3D_DESC));
//		m_pTexture->GetDesc(&desc);
//		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
//		desc.Usage = D3D11_USAGE_STAGING;
//		desc.BindFlags = 0;
//		desc.MiscFlags = 0;
//
//		ID3D11Texture3D* pTextureBuffer = sNull;
//		if (FAILED(g_pD3DDevice->CreateTexture3D(&desc, sNull, &pTextureBuffer)))
//			return sFalse;
//
//		//复制资源
//		g_pImmediateContext->CopyResource(pTextureBuffer, m_pTexture);
//
//		//
//		D3D11_MAPPED_SUBRESOURCE mappedResource;
//		MemorySet(&mappedResource, 0, sizeof(D3D11_MAPPED_SUBRESOURCE));
//		if (SUCCEEDED(g_pImmediateContext->Map(pTextureBuffer, level, D3D11_MAP_READ, 0, &mappedResource)))
//		{
//			MemoryCopy(pBuffer, mappedResource.pData, bytes);
//			g_pImmediateContext->Unmap(pTextureBuffer, level);
//		}
//
//		SAFE_RELEASE(pTextureBuffer);
//		return sTrue;
//	}
//
//	ID3D11ShaderResourceView* Texture3D::ResourceView()
//	{
//		return m_pResourceView;
//	}
//
//	//////////////////////////////////////////////////////////////////////////
//	RenderTexture::RenderTexture(ID3D11Texture2D* pTexture, ID3D11RenderTargetView* pRenderTargetView, ID3D11ShaderResourceView* pRenderTargetResource,
//		ID3D11Texture2D* pDepthStencil, ID3D11DepthStencilView* pDepthStencilView, ID3D11ShaderResourceView* pDepthStencilResource) : m_pTexture(pTexture),
//		m_pRenderTargetView(pRenderTargetView), m_pRenderTargetResource(pRenderTargetResource),
//		m_pDepthStencil(pDepthStencil), m_pDepthStencilView(pDepthStencilView), m_pDepthStencilResource(pDepthStencilResource)
//	{
//	}
//
//	RenderTexture::~RenderTexture()
//	{
//		SAFE_RELEASE(m_pRenderTargetResource);
//		SAFE_RELEASE(m_pRenderTargetView);
//		SAFE_RELEASE(m_pTexture);
//
//		SAFE_RELEASE(m_pDepthStencilResource);
//		SAFE_RELEASE(m_pDepthStencilView);
//		SAFE_RELEASE(m_pDepthStencil);
//	}
//
//	//void RenderTexture::Clear(uint32 flags, const Color& color, F32 depth, uint8 stencil)
//	//{
//	//	//清除颜色
//	//	if (m_pRenderTargetView && (flags & Device::CLEAR_FLAG_COLOR) != 0)
//	//		g_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, (F32*)&color);
//
//	//	//清除深度模板缓冲区
//	//	if (m_pDepthStencilView)
//	//	{
//	//		uint32 clearFlags = 0;
//	//		if ((flags & Device::CLEAR_FLAG_DEPTH) != 0) clearFlags = D3D11_CLEAR_DEPTH;
//	//		if ((flags & Device::CLEAR_FLAG_STENCIL) != 0) clearFlags |= D3D11_CLEAR_STENCIL;
//	//		if (clearFlags != 0) g_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, clearFlags, depth, stencil);
//	//	}
//	//}
//
//	sBoolean RenderTexture::Read(uint32 level, uint32 bytes, uint8* pBuffer)
//	{
//		D3D11_TEXTURE2D_DESC textureDesc;
//		MemorySet(&textureDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));
//		m_pTexture->GetDesc(&textureDesc);
//		textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
//		textureDesc.Usage = D3D11_USAGE_STAGING;
//		textureDesc.BindFlags = 0;
//		textureDesc.MiscFlags = 0;
//
//		ID3D11Texture2D* pTextureBuffer = sNull;
//		if (FAILED(g_pD3DDevice->CreateTexture2D(&textureDesc, sNull, &pTextureBuffer)))
//			return sFalse;
//
//		//复制资源
//		g_pImmediateContext->CopyResource(pTextureBuffer, m_pTexture);
//
//		//
//		D3D11_MAPPED_SUBRESOURCE mappedResource;
//		MemorySet(&mappedResource, 0, sizeof(D3D11_MAPPED_SUBRESOURCE));
//		if (SUCCEEDED(g_pImmediateContext->Map(pTextureBuffer, level, D3D11_MAP_READ, 0, &mappedResource)))
//		{
//			MemoryCopy(pBuffer, mappedResource.pData, bytes);
//			g_pImmediateContext->Unmap(pTextureBuffer, level);
//		}
//
//		SAFE_RELEASE(pTextureBuffer);
//		return sTrue;
//	}
//
//	ID3D11ShaderResourceView* RenderTexture::ResourceView()
//	{
//		return m_pRenderTargetResource;
//	}
//
//	ID3D11RenderTargetView* RenderTexture::RenderTargetView()
//	{
//		return m_pRenderTargetView;
//	}
//
//	ID3D11DepthStencilView* RenderTexture::DepthStencilView()
//	{
//		return m_pDepthStencilView;
//	}
//
//	//////////////////////////////////////////////////////////////////////////
//	VertexLayer::VertexLayer(ID3D11InputLayout* pInputLayout) : m_pInputLayout(pInputLayout)
//	{
//	}
//
//	VertexLayer::~VertexLayer()
//	{
//		SAFE_RELEASE(m_pInputLayout);
//	}
//
//	//////////////////////////////////////////////////////////////////////////
//	VertexBuffer::VertexBuffer(ID3D11Buffer* pBuffer) : m_pBuffer(pBuffer)
//	{
//	}
//
//	VertexBuffer::~VertexBuffer()
//	{
//		SAFE_RELEASE(m_pBuffer);
//	}
//
//	sBoolean VertexBuffer::Map(void** ppData, sBoolean isDiscard)
//	{
//		D3D11_MAPPED_SUBRESOURCE mappedResource;
//		MemorySet(&mappedResource, 0, sizeof(D3D11_MAPPED_SUBRESOURCE));
//		if (FAILED(g_pImmediateContext->Map(m_pBuffer, 0, isDiscard ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedResource)))
//			return sFalse;
//
//		*ppData = mappedResource.pData;
//		return sTrue;
//	}
//
//	void VertexBuffer::Unmap()
//	{
//		g_pImmediateContext->Unmap(m_pBuffer, 0);
//	}
//
//	//////////////////////////////////////////////////////////////////////////
//	VertexIndexBuffer::VertexIndexBuffer(ID3D11Buffer* pBuffer) : m_pBuffer(pBuffer)
//	{
//	}
//
//	VertexIndexBuffer::~VertexIndexBuffer()
//	{
//		SAFE_RELEASE(m_pBuffer);
//	}
//
//	sBoolean VertexIndexBuffer::Map(void** ppData, sBoolean isDiscard)
//	{
//		D3D11_MAPPED_SUBRESOURCE mappedResource;
//		MemorySet(&mappedResource, 0, sizeof(D3D11_MAPPED_SUBRESOURCE));
//		if (FAILED(g_pImmediateContext->Map(m_pBuffer, 0, isDiscard ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedResource)))
//			return sFalse;
//
//		*ppData = mappedResource.pData;
//		return sTrue;
//	}
//
//	void VertexIndexBuffer::Unmap()
//	{
//		g_pImmediateContext->Unmap(m_pBuffer, 0);
//	}
//
//	//////////////////////////////////////////////////////////////////////////
//	ConstantBuffer::ConstantBuffer(ID3D11Buffer* pBuffer) : m_pBuffer(pBuffer)
//	{
//	}
//
//	ConstantBuffer::~ConstantBuffer()
//	{
//		SAFE_RELEASE(m_pBuffer);
//	}
//
//	sBoolean ConstantBuffer::Map(void** ppData, sBoolean isDiscard)
//	{
//		D3D11_MAPPED_SUBRESOURCE mappedResource;
//		MemorySet(&mappedResource, 0, sizeof(D3D11_MAPPED_SUBRESOURCE));
//		if (FAILED(g_pImmediateContext->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
//			return sFalse;
//
//		*ppData = mappedResource.pData;
//		return sTrue;
//	}
//
//	void ConstantBuffer::Unmap()
//	{
//		g_pImmediateContext->Unmap(m_pBuffer, 0);
//	}
//
//	//////////////////////////////////////////////////////////////////////////
//	VertexShader::VertexShader(ID3DBlob* pShaderCode, ID3D11VertexShader* pShader) : m_pShaderCode(pShaderCode), m_pShader(pShader)
//	{
//	}
//
//	VertexShader::~VertexShader()
//	{
//		SAFE_RELEASE(m_pShader);
//		SAFE_RELEASE(m_pShaderCode);
//	}
//
//	GfxShaderType VertexShader::Type() const
//	{
//		return GfxShaderType::Vertex;
//	}
//
//	//////////////////////////////////////////////////////////////////////////
//	PixelShader::PixelShader(ID3D11PixelShader* pShader) : m_pShader(pShader)
//	{
//	}
//
//	PixelShader::~PixelShader()
//	{
//		SAFE_RELEASE(m_pShader);
//	}
//
//	GfxShaderType PixelShader::Type() const
//	{
//		return GfxShaderType::Fragment;
//	}
//
//	//////////////////////////////////////////////////////////////////////////
//	GeometryShader::GeometryShader(ID3D11GeometryShader* pShader) : m_pShader(pShader)
//	{
//	}
//
//	GeometryShader::~GeometryShader()
//	{
//		SAFE_RELEASE(m_pShader);
//	}
//
//	GfxShaderType GeometryShader::Type() const
//	{
//		return GfxShaderType::Geometry;
//	}
//}
