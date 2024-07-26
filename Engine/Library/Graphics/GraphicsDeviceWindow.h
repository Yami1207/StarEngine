#ifndef __GRAPHICS_DEVICE_WINDOW_H__
#define __GRAPHICS_DEVICE_WINDOW_H__

#include "GraphicsTypes.h"

namespace StarEngine
{
	namespace Graphics
	{
		class EXPORT_MODULE IDeviceWindow
		{
		public:
			virtual ~IDeviceWindow() { }
		public:
			/// <summary>
			/// 重置窗口
			/// </summary>
			/// <param name="width">宽度</param>
			/// <param name="height">高度</param>
			/// <param name="depthFormat">深度缓冲区格式</param>
			/// <param name="sRGB">是否线性空间</param>
			/// <returns></returns>
			virtual sBoolean Reshape(uint32 width, uint32 height, DepthBufferFormat depthFormat, sBoolean sRGB) = 0;

			/// <summary>
			/// 开始绘制屏幕
			/// </summary>
			/// <returns></returns>
			virtual sBoolean BeginRendering() = 0;

			/// <summary>
			/// 结束绘制屏幕
			/// </summary>
			/// <returns></returns>
			virtual sBoolean EndRendering() = 0;

			/// <summary>
			/// 是否有效
			/// </summary>
			/// <returns></returns>
			virtual sBoolean IsValid() const = 0;

			/// <summary>
			/// 返回窗口大小
			/// </summary>
			/// <param name="width">窗口宽度</param>
			/// <param name="height">窗口高度</param>
			/// <returns></returns>
			virtual sBoolean GetWindowSize(uint32& width, uint32& height) = 0;
		};
	}
}

#endif // !__GRAPHICS_DEVICE_WINDOW_H__

