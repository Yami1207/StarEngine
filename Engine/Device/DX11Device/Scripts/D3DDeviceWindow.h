#ifndef __D3D_DEVICE_WINDOW_H__
#define __D3D_DEVICE_WINDOW_H__

#include "D3DTypes.h"
#include "Graphics/GraphicsDeviceWindow.h"

namespace StarEngine
{
	class DeviceWindow : public Graphics::IDeviceWindow
	{
	public:
		DeviceWindow(PlatformWindowHandle window, uint32 width, uint32 height, Graphics::DepthBufferFormat format, sBoolean sRGB);
		virtual ~DeviceWindow();
	public:
		/// <summary>
		/// 重置窗口
		/// </summary>
		/// <param name="width">宽度</param>
		/// <param name="height">高度</param>
		/// <param name="depthFormat">深度缓冲区格式</param>
		/// <param name="sRGB">是否线性空间</param>
		/// <returns></returns>
		virtual sBoolean Reshape(uint32 width, uint32 height, Graphics::DepthBufferFormat depthFormat, sBoolean sRGB) sealed;

		/// <summary>
		/// 开始绘制屏幕
		/// </summary>
		/// <returns></returns>
		virtual sBoolean BeginRendering() sealed;

		/// <summary>
		/// 结束绘制屏幕
		/// </summary>
		/// <returns></returns>
		virtual sBoolean EndRendering() sealed;

		/// <summary>
		/// 是否有效
		/// </summary>
		/// <returns></returns>
		virtual sBoolean IsValid() const;

		/// <summary>
		/// 返回窗口大小
		/// </summary>
		/// <param name="width">窗口宽度</param>
		/// <param name="height">窗口高度</param>
		/// <returns></returns>
		virtual sBoolean GetWindowSize(uint32& width, uint32& height) sealed;

		RenderColorSurface& ColorSurface();

		RenderDepthSurface& DepthSurface();
	private:
		sBoolean	m_InvalidState;

		PlatformWindowHandle	m_Window;

		RenderColorSurface		m_BackBuffer;
		RenderDepthSurface		m_DepthStencil;

		IDXGISwapChain*			m_pSwapChain;
	};
}

#endif
