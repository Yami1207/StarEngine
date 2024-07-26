#include "D3DPrivate.h"
#include "D3DDevice.h"

#include "D3DUtility.h"
#include "D3DDeviceWindow.h"

using namespace StarEngine::Graphics;

namespace StarEngine
{
	//////////////////////////////////////////////////////////////////////////
	D3DDevice::D3DDevicePtr D3DDevice::s_Instance;

	D3DDevice::D3DDevice()
	{
		
	}

	D3DDevice::~D3DDevice()
	{
		Destroy();
	}

	sBoolean D3DDevice::Create(std::string& error)
	{
		return InitializeDevice(error);
	}

	void D3DDevice::Destroy()
	{
		m_StateCache.Clear();

		DestroyDevice();
	}

	void D3DDevice::Clear(uint32 flags, const Color& color, F32 depth, uint8 stencil)
	{
		DeviceWindow* pWindow = GetActiveWindow();
		if (pWindow != sNull)
		{
			ID3D11DeviceContext* pImmediateContext = GetImmediateContext();

			// 清除颜色
			if ((flags & (uint32)ClearFlags::Color) != 0)
				pImmediateContext->ClearRenderTargetView(pWindow->ColorSurface().pRenderTargetView, (F32*)&color);

			// 清除深度模板缓冲区
			uint32 clearFlags = 0;
			if ((flags & (uint32)ClearFlags::Depth) != 0) clearFlags = D3D11_CLEAR_DEPTH;
			if ((flags & (uint32)ClearFlags::Stencil) != 0) clearFlags |= D3D11_CLEAR_STENCIL;
			if (clearFlags != 0) pImmediateContext->ClearDepthStencilView(pWindow->DepthSurface().pDepthStencilView, clearFlags, depth, stencil);
		}
	}

	sBoolean D3DDevice::UsesReverseZ()
	{
		return sTrue;
	}

	IDeviceWindow* D3DDevice::CreateDeviceWindow(PlatformWindowHandle window, int32 width, int32 height, DepthBufferFormat format, sBoolean sRGB)
	{
		return new DeviceWindow(window, width, height, format, sRGB);
	}

	RasterizerStatePtr D3DDevice::CreateRasterizerState(const RasterizerDesc& desc)
	{
		return m_StateCache.GetRasterizerState(desc);
	}

	BlendStatePtr D3DDevice::CreateBlendState(const BlendStateDesc& desc)
	{
		return m_StateCache.GetBlendState(desc);
	}

	DepthStencilStatePtr D3DDevice::CreateDepthStencilState(const Graphics::DepthStencilDesc& desc)
	{
		return m_StateCache.GetDepthStencilState(desc);
	}

	IInputLayout* D3DDevice::CreateInputLayout(IVertexShader* pShader, uint32 elements, const VertexDeclaration* pVertexDeclaration)
	{
		if (pShader == sNull || elements == 0 || elements > MAX_VERTEX_ELEMENTS || pVertexDeclaration == sNull)
			return sNull;

		//设置顶点布局信息
		D3D11_INPUT_ELEMENT_DESC desc[MAX_VERTEX_ELEMENTS];
		::memset(&desc, 0, MAX_VERTEX_ELEMENTS * sizeof(D3D11_INPUT_ELEMENT_DESC));
		for (uint32 i = 0; i < elements; ++i)
			InitVertexInputLayout(desc[i], pVertexDeclaration[i]);

		//创建顶点布局对象
		ID3D11InputLayout* pInputLayout = sNull;
		ID3DBlob* pShaderCode = static_cast<D3DVertexShader*>(pShader)->m_pShaderCode;
		if (FAILED(GetD3DDevice()->CreateInputLayout(desc, elements, pShaderCode->GetBufferPointer(), pShaderCode->GetBufferSize(), &pInputLayout)))
			return sNull;
		return new D3DInputLayout(pInputLayout);
	}

	IVertexShader* D3DDevice::CreateVertexShader(uint32 binarySize, uint8* pBinary)
	{
		// 编译着色器代码
		ID3DBlob* pShaderCode = sNull;
		if (FAILED(D3DStripShader(pBinary, binarySize, 0, &pShaderCode)))
			return sNull;

		// 创建顶点着色器
		ID3D11VertexShader* pShader = sNull;
		if (FAILED(GetD3DDevice()->CreateVertexShader(pShaderCode->GetBufferPointer(), pShaderCode->GetBufferSize(), sNull, &pShader)))
		{
			SAFE_RELEASE(pShaderCode);
			return sNull;
		}
			
		return new D3DVertexShader(pShaderCode, pShader);
	}

	IPixelShader* D3DDevice::CreatePixelShader(uint32 binarySize, uint8* pBinary)
	{
		// 创建像素着色器
		ID3D11PixelShader* pShader = sNull;
		if (FAILED(GetD3DDevice()->CreatePixelShader(pBinary, binarySize, sNull, &pShader)))
			return sNull;
		return new D3DPixelShader(pShader);
	}

	IVertexBuffer* D3DDevice::CreateVertexBuffer(uint32 vertices, uint32 vertexBytes, sBoolean isDynamic, void* pData)
	{
		return new D3DVertexBuffer(vertices * vertexBytes, isDynamic, pData);
	}

	IVertexIndexBuffer* D3DDevice::CreateVertexIndexBuffer(uint32 indices, VertexIndexFormat format, sBoolean isDynamic, void* pData)
	{
		if (format == VertexIndexFormat::Uint16)
			return new D3DVertexIndexBuffer(DXGI_FORMAT_R16_UINT, indices * sizeof(uint16), isDynamic, pData);
		return new D3DVertexIndexBuffer(DXGI_FORMAT_R32_UINT, indices * sizeof(uint32), isDynamic, pData);
	}

	IConstantBuffer* D3DDevice::CreateConstantBuffer(uint32 byteWidth)
	{
		return new D3DConstantBuffer(byteWidth);
	}

	//IGfxTextureSampler* GfxDevice::CreateTextureSampler(const GfxTextureSamplerDesc& desc)
	//{
	//	D3D11_SAMPLER_DESC sampler_desc;
	//	MemorySet(&sampler_desc, 0, sizeof(D3D11_SAMPLER_DESC));
	//	sampler_desc.Filter = sampler_desc.MaxAnisotropy != 0 ? D3D11_FILTER_ANISOTROPIC : GetTextureFilter(desc.filter);
	//	sampler_desc.AddressU = sampler_desc.AddressV = sampler_desc.AddressW = GetTextureAddress(desc.address);
	//	sampler_desc.MipLODBias = desc.mipLODBias;
	//	sampler_desc.MaxAnisotropy = desc.maxAnisotropy;
	//	sampler_desc.ComparisonFunc = GetCompareFunc(desc.comparisonFunc);
	//	sampler_desc.BorderColor[0] = desc.borderColor.r;
	//	sampler_desc.BorderColor[1] = desc.borderColor.g;
	//	sampler_desc.BorderColor[2] = desc.borderColor.b;
	//	sampler_desc.BorderColor[3] = desc.borderColor.a;
	//	sampler_desc.MinLOD = desc.minLOD;
	//	sampler_desc.MaxLOD = desc.maxLOD;

	//	ID3D11SamplerState* pSamplerState = sNull;
	//	if (FAILED(g_pD3DDevice->CreateSamplerState(&sampler_desc, &pSamplerState)))
	//		return sNull;
	//	return new TextureSampler(pSamplerState);
	//}

	//IGfxTexture* GfxDevice::CreateTexture2D(uint32 width, uint32 height, GraphicsFormat format, sBoolean isMipmap, const void* pData)
	//{
	//	DXGI_FORMAT texture_format = GetFormat(format);
	//	if (texture_format == DXGI_FORMAT_UNKNOWN)
	//		return sNull;

	//	uint8* pLayers[16];
	//	uint32 layersW[16];
	//	uint32 layersH[16];
	//	uint32 mipmapLevels = 1, size = 0;

	//	//计算mipmap层数
	//	if (isMipmap)
	//	{
	//		uint32 mask = 0x01, maxSize = width > height ? height : width;
	//		for (uint32 i = 0; i < 16; ++i, ++mipmapLevels, mask <<= 1)
	//		{
	//			if (maxSize & mask)
	//				break;
	//		}
	//	}

	//	//设置0层纹理数据
	//	layersW[0] = width;
	//	layersH[0] = height;
	//	size = (layersW[0] * layersH[0]) << 2;
	//	pLayers[0] = new uint8[size];
	//	MemoryCopy(pLayers[0], pData, size);

	//	//计算其它层纹理数据
	//	for (uint32 i = 1; i < mipmapLevels; ++i)
	//	{
	//		layersW[i] = layersW[i - 1] >> 1;
	//		layersH[i] = layersH[i - 1] >> 1;
	//		size = (layersW[i] * layersH[i]) << 2;
	//		pLayers[i] = new uint8[size];
	//		TextureDownSampling(layersW[i], layersH[i], pLayers[i], pLayers[i - 1]);
	//	}

	//	D3D11_TEXTURE2D_DESC textureDesc;
	//	MemorySet(&textureDesc, 0, sizeof(textureDesc));
	//	textureDesc.Width = width;
	//	textureDesc.Height = height;
	//	textureDesc.MipLevels = mipmapLevels;
	//	textureDesc.ArraySize = 1;
	//	textureDesc.SampleDesc.Count = 1;
	//	textureDesc.Format = texture_format;
	//	textureDesc.Usage = D3D11_USAGE_IMMUTABLE;
	//	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	//	//保存各个图层数据
	//	D3D11_SUBRESOURCE_DATA layersData[16];
	//	for (uint32 i = 0; i < mipmapLevels; ++i)
	//	{
	//		layersData[i].pSysMem = pLayers[i];
	//		layersData[i].SysMemPitch = layersW[i] << 2;
	//		layersData[i].SysMemSlicePitch = 0;
	//	}

	//	ID3D11Texture2D* pTexture = sNull;
	//	if (FAILED(g_pD3DDevice->CreateTexture2D(&textureDesc, layersData, &pTexture)))
	//		return sNull;
	//	for (uint32 i = 0; i < mipmapLevels; ++i)
	//		SAFE_DELETE_ARRAY(pLayers[i]);

	//	D3D11_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
	//	MemorySet(&resourceViewDesc, 0, sizeof(resourceViewDesc));
	//	resourceViewDesc.Format = textureDesc.Format;
	//	resourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	//	resourceViewDesc.Texture2D.MostDetailedMip = 0;
	//	resourceViewDesc.Texture2D.MipLevels = mipmapLevels;

	//	ID3D11ShaderResourceView* pResourceView = sNull;
	//	if (FAILED(g_pD3DDevice->CreateShaderResourceView(pTexture, &resourceViewDesc, &pResourceView)))
	//	{
	//		SAFE_RELEASE(pTexture);
	//		return sNull;
	//	}

	//	return new Texture2D(mipmapLevels, pTexture, pResourceView);
	//}

	//IGfxTexture* GfxDevice::CreateTexture3D(uint32 width, uint32 height, uint32 depth, GraphicsFormat format, uint8 bitPerPixel, const void* pData)
	//{
	//	DXGI_FORMAT texture_format = GetFormat(format);
	//	if (texture_format == DXGI_FORMAT_UNKNOWN)
	//		return sNull;

	//	D3D11_TEXTURE3D_DESC desc;
	//	MemorySet(&desc, 0, sizeof(D3D11_TEXTURE3D_DESC));
	//	desc.Width = width;
	//	desc.Height = height;
	//	desc.Depth = depth;
	//	desc.MipLevels = 1;
	//	desc.Format = texture_format;
	//	desc.Usage = D3D11_USAGE_IMMUTABLE;
	//	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	//	D3D11_SUBRESOURCE_DATA layersData;
	//	MemorySet(&layersData, 0, sizeof(D3D11_SUBRESOURCE_DATA));
	//	layersData.pSysMem = pData;
	//	layersData.SysMemPitch = width * (bitPerPixel >> 3);
	//	layersData.SysMemSlicePitch = layersData.SysMemPitch * height;

	//	ID3D11Texture3D* pTexture = sNull;
	//	if (FAILED(g_pD3DDevice->CreateTexture3D(&desc, &layersData, &pTexture)))
	//		return sNull;

	//	D3D11_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
	//	MemorySet(&resourceViewDesc, 0, sizeof(resourceViewDesc));
	//	resourceViewDesc.Format = desc.Format;
	//	resourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
	//	resourceViewDesc.Texture3D.MostDetailedMip = 0;
	//	resourceViewDesc.Texture3D.MipLevels = 1;

	//	ID3D11ShaderResourceView* pResourceView = sNull;
	//	if (FAILED(g_pD3DDevice->CreateShaderResourceView(pTexture, &resourceViewDesc, &pResourceView)))
	//	{
	//		SAFE_RELEASE(pTexture);
	//		return sNull;
	//	}

	//	return new Texture3D(pTexture, pResourceView);
	//}

	//IGfxTexture* GfxDevice::CreateRenderTexture(uint32 width, uint32 height, GraphicsFormat format, GraphicsFormat depthStencilFormat)
	//{
	//	DXGI_FORMAT texture_format = GetFormat(format);
	//	if (texture_format == DXGI_FORMAT_UNKNOWN) return sNull;

	//	ID3D11Texture2D *pRenderTexture = sNull, *pDepthStencil = sNull;
	//	ID3D11RenderTargetView* pRenderTargetView = sNull;
	//	ID3D11DepthStencilView* pDepthStencilView = sNull;
	//	ID3D11ShaderResourceView *pRenderTargetResource = sNull, *pDepthStencilResource = sNull;

	//	// 创建渲染目标对象
	//	D3D11_TEXTURE2D_DESC desc;
	//	MemorySet(&desc, 0, sizeof(D3D11_TEXTURE2D_DESC));
	//	desc.Width = width;
	//	desc.Height = height;
	//	desc.MipLevels = 1;
	//	desc.Format = texture_format;
	//	desc.SampleDesc.Count = 1;
	//	desc.SampleDesc.Quality = 0;
	//	desc.Usage = D3D11_USAGE_DEFAULT;
	//	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	//	desc.CPUAccessFlags = 0;
	//	desc.MiscFlags = 0;
	//	desc.ArraySize = 1;
	//	if (FAILED(g_pD3DDevice->CreateTexture2D(&desc, sNull, &pRenderTexture)))
	//		return sNull;

	//	// 创建渲染目标视口对象
	//	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	//	renderTargetViewDesc.Format = desc.Format;
	//	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	//	renderTargetViewDesc.Texture2D.MipSlice = 0;
	//	if (FAILED(g_pD3DDevice->CreateRenderTargetView(pRenderTexture, &renderTargetViewDesc, &pRenderTargetView)))
	//	{
	//		SAFE_RELEASE(pRenderTexture);
	//		return sFalse;
	//	}

	//	D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_desc;
	//	shader_resource_view_desc.Format = desc.Format;
	//	shader_resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	//	shader_resource_view_desc.Texture2D.MostDetailedMip = 0;
	//	shader_resource_view_desc.Texture2D.MipLevels = 1;
	//	if (FAILED(g_pD3DDevice->CreateShaderResourceView(pRenderTexture, &shader_resource_view_desc, &pRenderTargetResource)))
	//	{
	//		SAFE_RELEASE(pRenderTargetView);
	//		SAFE_RELEASE(pRenderTexture);
	//		return sFalse;
	//	}

	//	// 创建深度模板纹理
	//	MemorySet(&desc, 0, sizeof(D3D11_TEXTURE2D_DESC));
	//	desc.Width = width;
	//	desc.Height = height;
	//	desc.MipLevels = 1;
	//	desc.ArraySize = 1;
	//	desc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	//	desc.SampleDesc.Count = 1;
	//	desc.Usage = D3D11_USAGE_DEFAULT;
	//	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	//	if (FAILED(g_pD3DDevice->CreateTexture2D(&desc, sNull, &pDepthStencil)))
	//	{
	//		SAFE_RELEASE(pRenderTargetResource);
	//		SAFE_RELEASE(pRenderTargetView);
	//		SAFE_RELEASE(pRenderTexture);
	//		return sFalse;
	//	}

	//	MemorySet(&shader_resource_view_desc, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	//	shader_resource_view_desc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	//	shader_resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	//	shader_resource_view_desc.Texture2D.MipLevels = 1;
	//	if (FAILED(g_pD3DDevice->CreateShaderResourceView(pDepthStencil, &shader_resource_view_desc, &pDepthStencilResource)))
	//	{
	//		SAFE_RELEASE(pRenderTargetResource);
	//		SAFE_RELEASE(pRenderTargetView);
	//		SAFE_RELEASE(pRenderTexture);
	//		SAFE_RELEASE(pDepthStencil);
	//		return sFalse;
	//	}

	//	//创建深度模板视口对象
	//	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
	//	MemorySet(&depth_stencil_view_desc, 0, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	//	depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//	depth_stencil_view_desc.Texture2D.MipSlice = 0;
	//	if (FAILED(g_pD3DDevice->CreateDepthStencilView(pDepthStencil, &depth_stencil_view_desc, &pDepthStencilView)))
	//	{
	//		SAFE_RELEASE(pRenderTargetResource);
	//		SAFE_RELEASE(pRenderTargetView);
	//		SAFE_RELEASE(pRenderTexture);
	//		SAFE_RELEASE(pDepthStencil);
	//		SAFE_RELEASE(pDepthStencilResource);
	//		return sFalse;
	//	}

	//	return new RenderTexture(pRenderTexture, pRenderTargetView, pRenderTargetResource, pDepthStencil, pDepthStencilView, pDepthStencilResource);
	//}

//	IGfxVertexBuffer* GfxDevice::CreateVertexBuffer(uint32 numVertices, uint32 stride, sBoolean isDynamic, void* pData)
//	{
//		D3D11_BUFFER_DESC desc;
//		MemorySet(&desc, 0, sizeof(desc));
//		desc.Usage = isDynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE;
//		desc.ByteWidth = numVertices * stride;
//		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//		desc.CPUAccessFlags = isDynamic ? D3D11_CPU_ACCESS_WRITE : 0;
//
//		ID3D11Buffer* pBuffer = sNull;
//		if (pData != sNull)
//		{
//			D3D11_SUBRESOURCE_DATA subresource;
//			MemorySet(&subresource, 0, sizeof(subresource));
//			subresource.pSysMem = pData;
//			if (FAILED(g_pD3DDevice->CreateBuffer(&desc, &subresource, &pBuffer)))
//				return sNull;
//		}
//		else
//		{
//			if (FAILED(g_pD3DDevice->CreateBuffer(&desc, sNull, &pBuffer)))
//				return sNull;
//		}
//
//		return new VertexBuffer(pBuffer);
//	}
//


//	IGfxShader* GfxDevice::CreateVertexShaderFromFile(const wchar_t* pFilename, const char* pEntry, const char* pProfile, char** ppError)
//	{
//		ID3DBlob* pShaderCode = sNull;
//		ID3DBlob* pErrorMessage = sNull;
//		ID3D11VertexShader* pShader = sNull;
//#ifdef _DEBUG
//		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY | D3D10_SHADER_DEBUG;
//#else
//		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY;
//#endif
//		VertexShader* pVertexShader = sNull;
//
//		//编译顶点着色器代码
//		if (FAILED(D3DCompileFromFile(pFilename, sNull, sNull, pEntry, pProfile, dwShaderFlags, 0, &pShaderCode, &pErrorMessage)))
//		{
//			//创建顶点着色器
//			if (SUCCEEDED(g_pD3DDevice->CreateVertexShader(pShaderCode->GetBufferPointer(), pShaderCode->GetBufferSize(), sNull, &pShader)))
//				pVertexShader = new VertexShader(pShaderCode, pShader);
//		}
//		else
//		{
//			if (pErrorMessage && ppError && *ppError)
//				StringCopy(*ppError, (char*)(pErrorMessage->GetBufferPointer()));
//		}
//
//		SAFE_RELEASE(pErrorMessage);
//		return new VertexShader(pShaderCode, pShader);
//	}
//
//	IGfxShader* GfxDevice::CreateVertexShaderFromStream(uint32 streamSize, const void* pStreamData, const char* pEntry, const char* pProfile, char** ppError)
//	{
//		ID3DBlob* pShaderCode = sNull;
//		ID3DBlob* pErrorMessage = sNull;
//		ID3D11VertexShader* pShader = sNull;
//#ifdef _DEBUG
//		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY | D3D10_SHADER_DEBUG;
//#else
//		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY;
//#endif
//		VertexShader* pVertexShader = sNull;
//
//		//编译顶点着色器代码
//		if (SUCCEEDED(D3DCompile(pStreamData, streamSize, sNull, sNull, sNull, pEntry, pProfile, dwShaderFlags, 0, &pShaderCode, &pErrorMessage)))
//		{
//			//创建顶点着色器
//			if (SUCCEEDED(g_pD3DDevice->CreateVertexShader(pShaderCode->GetBufferPointer(), pShaderCode->GetBufferSize(), sNull, &pShader)))
//				pVertexShader = new VertexShader(pShaderCode, pShader);
//		}
//		else
//		{
//			if (pErrorMessage && ppError && *ppError)
//				StringCopy(*ppError, (char*)(pErrorMessage->GetBufferPointer()));
//		}
//
//		SAFE_RELEASE(pErrorMessage);
//		return new VertexShader(pShaderCode, pShader);
//	}

//	IGfxShader* GfxDevice::CreateFragmentShaderFromFile(const wchar_t* pFilename, const char* pEntry, const char* pProfile, char** ppError)
//	{
//		ID3DBlob* pShaderCode = sNull;
//		ID3DBlob* pErrorMessage = sNull;
//		ID3D11PixelShader* pShader = sNull;
//#ifdef _DEBUG
//		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY | D3D10_SHADER_DEBUG;
//#else
//		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY;
//#endif
//		PixelShader* pPixelShader = sNull;
//
//		//编译像素着色器代码
//		if (SUCCEEDED(D3DCompileFromFile(pFilename, sNull, sNull, pEntry, pProfile, dwShaderFlags, 0, &pShaderCode, &pErrorMessage)))
//		{
//			//创建像素着色器
//			if (SUCCEEDED(g_pD3DDevice->CreatePixelShader(pShaderCode->GetBufferPointer(), pShaderCode->GetBufferSize(), sNull, &pShader)))
//				pPixelShader = new PixelShader(pShader);
//		}
//		else
//		{
//			if (pErrorMessage && ppError && *ppError)
//				StringCopy(*ppError, (char*)(pErrorMessage->GetBufferPointer()));
//		}
//
//		SAFE_RELEASE(pErrorMessage);
//		SAFE_RELEASE(pShaderCode);
//		return new PixelShader(pShader);
//	}
//
//	IGfxShader* GfxDevice::CreateFragmentShaderFromStream(uint32 streamSize, const void* pStreamData, const char* pEntry, const char* pProfile, char** ppError)
//	{
//		ID3DBlob* pShaderCode = sNull;
//		ID3DBlob* pErrorMessage = sNull;
//		ID3D11PixelShader* pShader = sNull;
//#ifdef _DEBUG
//		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY | D3D10_SHADER_DEBUG;
//#else
//		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY;
//#endif
//		PixelShader* pPixelShader = sNull;
//
//		//编译几何体着色器代码
//		if (SUCCEEDED(D3DCompile(pStreamData, streamSize, sNull, sNull, sNull, pEntry, pProfile, dwShaderFlags, 0, &pShaderCode, &pErrorMessage)))
//		{
//			//创建几何体着色器
//			if (SUCCEEDED(g_pD3DDevice->CreatePixelShader(pShaderCode->GetBufferPointer(), pShaderCode->GetBufferSize(), sNull, &pShader)))
//				pPixelShader = new PixelShader(pShader);
//		}
//		else
//		{
//			if (pErrorMessage && ppError && *ppError)
//				StringCopy(*ppError, (char*)(pErrorMessage->GetBufferPointer()));
//		}
//
//		SAFE_RELEASE(pErrorMessage);
//		SAFE_RELEASE(pShaderCode);
//		return new PixelShader(pShader);
//	}
//
//	IGfxShader* GfxDevice::CreateGeometryShaderFromFile(const wchar_t* pFilename, const char* pEntry, const char* pProfile, char** ppError)
//	{
//		ID3DBlob* pShaderCode = sNull;
//		ID3DBlob* pErrorMessage = sNull;
//		ID3D11GeometryShader* pShader = sNull;
//#ifdef _DEBUG
//		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY | D3D10_SHADER_DEBUG;
//#else
//		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY;
//#endif
//		GeometryShader* pGeometryShader = sNull;
//
//		//编译几何体着色器代码
//		if (SUCCEEDED(D3DCompileFromFile(pFilename, sNull, sNull, pEntry, pProfile, dwShaderFlags, 0, &pShaderCode, &pErrorMessage)))
//		{
//			//创建几何体着色器
//			if (SUCCEEDED(g_pD3DDevice->CreateGeometryShader(pShaderCode->GetBufferPointer(), pShaderCode->GetBufferSize(), sNull, &pShader)))
//				pGeometryShader = new GeometryShader(pShader);
//		}
//		else
//		{
//			if (pErrorMessage && ppError && *ppError)
//				StringCopy(*ppError, (char*)(pErrorMessage->GetBufferPointer()));
//		}
//
//		SAFE_RELEASE(pErrorMessage);
//		SAFE_RELEASE(pShaderCode);
//		return new GeometryShader(pShader);
//	}
//
//	IGfxShader* GfxDevice::CreateGeometryShaderFromStream(uint32 streamSize, const void* pStreamData, const char* pEntry, const char* pProfile, char** ppError)
//	{
//		ID3DBlob* pShaderCode = sNull;
//		ID3DBlob* pErrorMessage = sNull;
//		ID3D11GeometryShader* pShader = sNull;
//#ifdef _DEBUG
//		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY | D3D10_SHADER_DEBUG;
//#else
//		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY;
//#endif
//		GeometryShader* pGeometryShader = sNull;
//
//		//编译几何体着色器代码
//		if (SUCCEEDED(D3DCompile(pStreamData, streamSize, sNull, sNull, sNull, pEntry, pProfile, dwShaderFlags, 0, &pShaderCode, &pErrorMessage)))
//		{
//			//创建几何体着色器
//			if (SUCCEEDED(g_pD3DDevice->CreateGeometryShader(pShaderCode->GetBufferPointer(), pShaderCode->GetBufferSize(), sNull, &pShader)))
//				pGeometryShader = new GeometryShader(pShader);
//		}
//		else
//		{
//			if (pErrorMessage && ppError && *ppError)
//				StringCopy(*ppError, (char*)(pErrorMessage->GetBufferPointer()));
//		}
//
//		SAFE_RELEASE(pErrorMessage);
//		SAFE_RELEASE(pShaderCode);
//		return new GeometryShader(pShader);
//	}
//
//	void GfxDevice::DrawPrimitive(GfxPrimitiveType type, uint32 startVertex, uint32 vertices, uint32 primitives)
//	{
//		g_pImmediateContext->IASetPrimitiveTopology(GetPrimitiveType(type));
//		g_pImmediateContext->Draw(vertices, startVertex);
//	}

	void D3DDevice::DrawPrimitive(PrimitiveTopology type, uint32 offset, uint32 primitives)
	{
		ID3D11DeviceContext* pImmediateContext = GetImmediateContext();
		pImmediateContext->IASetPrimitiveTopology(ToPrimitiveTopology(type));
		pImmediateContext->Draw(ToDrawCount(type, primitives), offset);
	}

	void D3DDevice::DrawIndexedPrimitive(PrimitiveTopology type, uint32 startVertex, uint32 startIndex, uint32 primitives)
	{
		ID3D11DeviceContext* pImmediateContext = GetImmediateContext();
		pImmediateContext->IASetPrimitiveTopology(ToPrimitiveTopology(type));
		pImmediateContext->DrawIndexed(ToDrawCount(type, primitives), startIndex, startVertex);
	}

	void D3DDevice::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height, F32 minDepth, F32 maxDepth)
	{
		D3D11_VIEWPORT viewport;
		viewport.Width = static_cast<F32>(width);
		viewport.Height = static_cast<F32>(height);
		viewport.MinDepth = minDepth;
		viewport.MaxDepth = maxDepth;
		viewport.TopLeftX = static_cast<F32>(x);
		viewport.TopLeftY = static_cast<F32>(y);
		GetImmediateContext()->RSSetViewports(1, &viewport);
	}

	void D3DDevice::SetInputLayout(IInputLayout* pInputLayout)
	{
		if (pInputLayout != sNull)
			GetImmediateContext()->IASetInputLayout(static_cast<D3DInputLayout*>(pInputLayout)->m_pInputLayout);
		else
			GetImmediateContext()->IASetInputLayout(sNull);
	}

	void D3DDevice::SetVertexShader(IVertexShader* pShader)
	{
		if (pShader != sNull)
			GetImmediateContext()->VSSetShader(static_cast<D3DVertexShader*>(pShader)->m_pShader, sNull, 0);
		else
			GetImmediateContext()->VSSetShader(sNull, sNull, 0);
	}

	void D3DDevice::SetPixelShader(IPixelShader* pShader)
	{
		if (pShader != sNull)
			GetImmediateContext()->PSSetShader(static_cast<D3DPixelShader*>(pShader)->m_pShader, sNull, 0);
		else
			GetImmediateContext()->PSSetShader(sNull, sNull, 0);
	}

	void D3DDevice::SetVertexBuffer(uint32 stream, uint32 stride, uint32 offset, IVertexBuffer* pBuffer)
	{
		if (pBuffer != sNull)
			GetImmediateContext()->IASetVertexBuffers(stream, 1, &(static_cast<D3DVertexBuffer*>(pBuffer)->m_pBuffer), &stride, &offset);
		else
			GetImmediateContext()->IASetVertexBuffers(stream, 0, sNull, sNull, sNull);
	}

	void D3DDevice::SetVertexIndexBuffer(uint32 offset, IVertexIndexBuffer* pBuffer)
	{
		if (pBuffer != sNull)
		{
			D3DVertexIndexBuffer* pVIB = static_cast<D3DVertexIndexBuffer*>(pBuffer);
			GetImmediateContext()->IASetIndexBuffer(pVIB->m_pBuffer, pVIB->m_Format, offset);
		}
		else
		{
			GetImmediateContext()->IASetIndexBuffer(sNull, DXGI_FORMAT_R16_UINT, offset);
		}
	}

	//void GfxDevice::SetTextureSampler(IGfxTextureSampler* pSampler, uint32 slot)
	//{
	//	TextureSampler* pTextureSampler = static_cast<TextureSampler*>(pSampler);
	//	ID3D11SamplerState* pState = pTextureSampler->State();
	//	g_pImmediateContext->PSSetSamplers(slot, 1, &pState);
	//}

	//void GfxDevice::SetTexture(uint32 stage, IGfxTexture* pTexture)
	//{
	//	if (pTexture == sNull)
	//	{
	//		ID3D11ShaderResourceView *const pResourceView[1] = { sNull };
	//		g_pImmediateContext->PSSetShaderResources(stage, 1, pResourceView);
	//	}
	//	else
	//	{
	//		IBaseTexture* pBaseTexture = static_cast<IBaseTexture*>(pTexture);
	//		ID3D11ShaderResourceView *const pResourceView[1] = { pBaseTexture->ResourceView() };
	//		g_pImmediateContext->PSSetShaderResources(stage, 1, pResourceView);
	//	}
	//}

	//void GfxDevice::SetRenderTarget(IGfxTexture* pTexture)
	//{
	//	if (pTexture != sNull)
	//	{
	//		RenderTexture* pRenderTexture = static_cast<RenderTexture*>(pTexture);
	//		ID3D11RenderTargetView* pRenderTargetView = pRenderTexture->RenderTargetView();
	//		g_pImmediateContext->OMSetRenderTargets(1, &pRenderTargetView, pRenderTexture->DepthStencilView());
	//	}
	//	else
	//	{
	//		//this->SetViewport(0, 0, m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height, 0.0f, 1.0f);
	//		g_pImmediateContext->OMSetRenderTargets(1, &m_pBackRenderTargetView, m_pBackDepthStencilView);
	//	}
	//}

	//void GfxDevice::SetVertexIndexBuffer(uint32 offset, IGfxVertexIndexBuffer* pBuffer)
	//{
	//	if (pBuffer != sNull)
	//	{
	//		VertexIndexBuffer* pVertexIndexBuffer = static_cast<VertexIndexBuffer*>(pBuffer);
	//		ID3D11Buffer* pDXBuffer = pVertexIndexBuffer->Buffer();
	//		g_pImmediateContext->IASetIndexBuffer(pDXBuffer, DXGI_FORMAT_R16_UINT, offset);
	//	}
	//	else
	//	{
	//		g_pImmediateContext->IASetIndexBuffer(sNull, DXGI_FORMAT_R16_UINT, offset);
	//	}
	//}

	//void GfxDevice::SetConstantBuffer(uint32 slot, GfxConstantUser user, IGfxConstantBuffer* pBuffer)
	//{
	//	if (pBuffer != sNull)
	//	{
	//		ConstantBuffer* pConstantBuffer = static_cast<ConstantBuffer*>(pBuffer);
	//		ID3D11Buffer* pDXBuffer = pConstantBuffer->Buffer();

	//		if ((user & GfxConstantUser::GfxConstantVertex) != 0)
	//			g_pImmediateContext->VSSetConstantBuffers(slot, 1, &pDXBuffer);

	//		if ((user & GfxConstantUser::GfxConstantGeometry) != 0)
	//			g_pImmediateContext->PSSetConstantBuffers(slot, 1, &pDXBuffer);

	//		if ((user & GfxConstantUser::GfxConstantFragment) != 0)
	//			g_pImmediateContext->GSSetConstantBuffers(slot, 1, &pDXBuffer);
	//	}
	//	else
	//	{
	//		if ((user & GfxConstantUser::GfxConstantVertex) != 0)
	//			g_pImmediateContext->VSSetConstantBuffers(slot, 0, sNull);

	//		if ((user & GfxConstantUser::GfxConstantGeometry) != 0)
	//			g_pImmediateContext->GSSetConstantBuffers(slot, 0, sNull);

	//		if ((user & GfxConstantUser::GfxConstantFragment) != 0)
	//			g_pImmediateContext->PSSetConstantBuffers(slot, 0, sNull);
	//	}
	//}

	//void GfxDevice::SetGeometryShader(IGfxShader* pShader)
	//{
	//	if (pShader && (pShader->Type() == GfxShaderType::Geometry))
	//	{
	//		GeometryShader* pGeometryShader = static_cast<GeometryShader*>(pShader);
	//		ID3D11GeometryShader* pDXShader = pGeometryShader->Shader();
	//		g_pImmediateContext->GSSetShader(pDXShader, sNull, 0);
	//	}
	//	else
	//	{
	//		g_pImmediateContext->GSSetShader(sNull, sNull, 0);
	//	}
	//}

	uint32 D3DDevice::MaxSamplerCount()
	{
		return D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT;
	}

	D3DDevice* D3DDevice::Instance()
	{
		if (s_Instance.get() == sNull)
			s_Instance.reset(new D3DDevice);
		return s_Instance.get();
	}

	//////////////////////////////////////////////////////////////////////////
	EXPORT_MODULE Graphics::IDevice* GetGraphicsDevice()
	{
		return D3DDevice::Instance();
	}
}
