#ifndef __GRAPHICS_ENUMS_H__
#define __GRAPHICS_ENUMS_H__

#include "GraphicsFormat.h"

namespace StarEngine
{
	namespace Graphics
	{
		enum class DeviceType
		{
			Direct3D11 = 0,
			Unknown
		};

		/// <summary>
		/// 清屏指令
		/// </summary>
		enum class ClearFlags
		{
			None = 0,
			Color = 1,
			Depth = (1 << 1),
			Stencil = (1 << 2),
			DepthStencil = Depth | Stencil,
			All = Color | DepthStencil,
		};

		/// <summary>
		/// 填充模式
		/// </summary>
		enum class FillMode
		{
			WireFrame = 0,
			Solid,
		};

		// 剔除模式
		enum class CullMode
		{
			// 不进行任何剔除
			Off = 0,

			// 前面剔除
			Front,

			// 背面剔除
			Back,
		};

		/// <summary>
		/// 混合模式操作
		/// </summary>
		enum class BlendOp
		{
			Add = 0,
			Sub,
			RevSub,
			Min,
			Max
		};

		/// <summary>
		/// 混合模式
		/// </summary>
		enum class BlendMode
		{
			Zero = 0,
			One,

			SrcColor,
			OneMinusSrcColor,
			SrcAlpha,
			OneMinusSrcAlpha,

			DstColor,
			OneMinusDstColor,
			DstAlpha,
			OneMinusDstAlpha,

			SrcAlphaSaturate,

			Factor,
			OneMinusFactor,
		};

		enum class StencilOp
		{
			Keep = 0,
			Zero,
			Replace,
			IncSat,
			DecSat,
			Invert,
			IncWrap,
			DecWrap,
		};

		enum ColorWriteMask
		{
			ColorWriteRed = 1,
			ColorWriteGreen = 2,
			ColorWriteBlue = 4,
			ColorWriteAlpha = 8,
			ColorWriteAll = ColorWriteRed | ColorWriteGreen | ColorWriteBlue | ColorWriteAlpha,
		};

		/// <summary>
		/// 纹理类型
		/// </summary>
		enum class TextureDimension
		{
			Unknown = 0,
			None,
			Any,
			Tex2D,
			Tex3D,
			Cube,
			Tex2DArray,
			CubeArray,
		};

		enum class PrimitiveTopology
		{
			// 点列表
			Points = 0,

			// 线列表(每两个点画成一条线段)
			Lines,

			// 线列表(从一点开始,把所有的点首尾相接)
			LineStrip,

			// 三角形列表(每三个是一个三角形的定点)
			Triangles,

			// 三角带状图形
			TriangleStrip,

			// 四边形
			Quads,
		};

		/// <summary>
		/// 深度缓冲区格式
		/// </summary>
		enum class DepthBufferFormat
		{
			None,
			Depth16Bits,
			Depth24BitsAndStencil8Bits,
		};

		/// <summary>
		/// 顶点索引格式
		/// </summary>
		enum class VertexIndexFormat
		{
			Uint16,
			Uint32,
		};
	}
}

#endif // !__GRAPHICS_ENUMS_H__
