#include "D3DPrivate.h"
#include "D3DDeviceWindow.h"

#include "D3DUtility.h"

using namespace StarEngine::Graphics;

namespace StarEngine
{
	//////////////////////////////////////////////////////////////////////////
	DeviceWindow::DeviceWindow(PlatformWindowHandle window, uint32 width, uint32 height, DepthBufferFormat format, sBoolean sRGB) : m_Window(window),
		m_InvalidState(sTrue), m_pSwapChain(sNull)
	{
		Reshape(width, height, format, sRGB);
	}

	DeviceWindow::~DeviceWindow()
	{
		if (GetActiveWindow() == this)
			SetActiveWindow(sNull);

		m_BackBuffer.Release();
		m_DepthStencil.Release();
		SAFE_RELEASE(m_pSwapChain);
	}

	sBoolean DeviceWindow::Reshape(uint32 width, uint32 height, DepthBufferFormat depthFormat, sBoolean sRGB)
	{
		m_BackBuffer.Release();
		m_DepthStencil.Release();

		ID3D11Device* pD3DDevice = GetD3DDevice();
		IDXGIFactory* pFactory = GetDXGIFactory();

		const uint32 kBufferCount = 2;
		DXGI_FORMAT swapFormat = sRGB ? DXGI_FORMAT_R8G8B8A8_UNORM_SRGB : DXGI_FORMAT_R8G8B8A8_UNORM;

		if (m_pSwapChain == sNull)
		{
			// 设置DXGI交换链描述信息
			DXGI_SWAP_CHAIN_DESC swapChainDesc;
			memset(&swapChainDesc, 0, sizeof(DXGI_SWAP_CHAIN_DESC));
			swapChainDesc.BufferCount = kBufferCount;
			swapChainDesc.BufferDesc.Width = width;
			swapChainDesc.BufferDesc.Height = height;
			swapChainDesc.BufferDesc.Format = swapFormat;
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
			swapChainDesc.OutputWindow = m_Window;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.Windowed = TRUE;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

			if (FAILED(pFactory->CreateSwapChain(pD3DDevice, &swapChainDesc, &m_pSwapChain)))
			{
				m_InvalidState = sTrue;
				return sFalse;
			}
		}
		else
		{
			if (FAILED(m_pSwapChain->ResizeBuffers(kBufferCount, width, height, swapFormat, 0)))
			{
				m_InvalidState = sTrue;
				return sFalse;
			}
		}

		// 创建渲染缓冲区
		{
			// 获取数据交换链的主辅渲染缓冲区
			if (FAILED(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_BackBuffer.pTexture)))
			{
				m_InvalidState = sTrue;
				return sFalse;
			}

			// 创建渲染主视口对象
			if (FAILED(pD3DDevice->CreateRenderTargetView(m_BackBuffer.pTexture, sNull, &m_BackBuffer.pRenderTargetView)))
			{
				m_InvalidState = sTrue;
				return sFalse;
			}

			m_BackBuffer.width = width;
			m_BackBuffer.height = height;
		}

		// 创建深度缓冲区
		if (depthFormat != DepthBufferFormat::None)
		{
			D3D11_TEXTURE2D_DESC depthDesc;
			memset(&depthDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));
			depthDesc.Width = width;
			depthDesc.Height = height;
			depthDesc.MipLevels = 1;
			depthDesc.ArraySize = 1;
			depthDesc.Format = GetDepthBufferFormat(depthFormat);
			depthDesc.SampleDesc.Count = 1;
			depthDesc.SampleDesc.Quality = 0;
			depthDesc.Usage = D3D11_USAGE_DEFAULT;
			depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthDesc.CPUAccessFlags = 0;
			depthDesc.MiscFlags = 0;

			if (FAILED(pD3DDevice->CreateTexture2D(&depthDesc, sNull, &(m_DepthStencil.pTexture))))
			{
				m_InvalidState = sTrue;
				return sFalse;
			}

			if (FAILED(pD3DDevice->CreateDepthStencilView(m_DepthStencil.pTexture, 0, &m_DepthStencil.pDepthStencilView)))
			{
				m_InvalidState = sTrue;
				return sFalse;
			}

			m_DepthStencil.width = width;
			m_DepthStencil.height = height;
		}

		m_InvalidState = sFalse;
		return sTrue;
	}

	sBoolean DeviceWindow::BeginRendering()
	{
		if (m_InvalidState)
			return sFalse;

		SetActiveWindow(this);
		return sTrue;
	}

	sBoolean DeviceWindow::EndRendering()
	{
		if (m_InvalidState || GetActiveWindow() != this)
			return sFalse;

		//	交换前后缓冲区
		if (FAILED(m_pSwapChain->Present(1, 0)))
			return sFalse;
		return sTrue;
	}

	RenderColorSurface& DeviceWindow::ColorSurface()
	{
		return m_BackBuffer;
	}

	RenderDepthSurface& DeviceWindow::DepthSurface()
	{
		return m_DepthStencil;
	}

	sBoolean DeviceWindow::IsValid() const
	{
		return m_BackBuffer.pRenderTargetView != sNull && m_DepthStencil.pDepthStencilView != sNull;
	}

	sBoolean DeviceWindow::GetWindowSize(uint32& width, uint32& height)
	{
		if (m_InvalidState)
			return sFalse;

		width = m_BackBuffer.width;
		height = m_BackBuffer.height;
		return sTrue;
	}
}
