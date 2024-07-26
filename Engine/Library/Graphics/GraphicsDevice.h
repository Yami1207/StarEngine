#ifndef __GRAPHICS_DEVICE_H__
#define __GRAPHICS_DEVICE_H__

#include "GraphicsDeviceWindow.h"

namespace StarEngine
{
	namespace Graphics
	{
		class EXPORT_MODULE IDevice
		{
		public:
			virtual ~IDevice() { }
		public:
			/// <summary>
			/// 创建图形设备
			/// </summary>
			/// <param name="error">错误信息</param>
			/// <returns></returns>
			virtual sBoolean Create(std::string& error) = 0;

			/// <summary>
			/// 注销图形设备
			/// </summary>
			virtual void Destroy() = 0;

			/// <summary>
			/// 填充渲染缓冲区
			/// </summary>
			/// <param name="flags">填充指令</param>
			/// <param name="color">背景颜色</param>
			/// <param name="depth">背景深度</param>
			/// <param name="stencil">背景模板值</param>
			virtual void Clear(uint32 flags, const Color& color, F32 depth, uint8 stencil) = 0;
		public:
			/// <summary>
			/// 是否反向Z
			/// </summary>
			/// <returns></returns>
			virtual sBoolean UsesReverseZ() = 0;
		public:
			/// <summary>
			/// 创建图形窗口
			/// </summary>
			/// <param name="window">窗口句柄</param>
			/// <param name="width">窗口宽度</param>
			/// <param name="height">窗口高度</param>
			/// <param name="format">深度缓冲区格式</param>
			/// <param name="sRGB">是否线性空间</param>
			/// <returns></returns>
			virtual IDeviceWindow* CreateDeviceWindow(PlatformWindowHandle window, int32 width, int32 height, DepthBufferFormat format, sBoolean sRGB) = 0;

			/// <summary>
			/// 创建光栅化状态
			/// </summary>
			/// <param name="desc">描述表</param>
			/// <returns></returns>
			virtual RasterizerStatePtr CreateRasterizerState(const RasterizerDesc& desc) = 0;

			/// <summary>
			/// 创建混合状态
			/// </summary>
			/// <param name="desc">描述表</param>
			/// <returns></returns>
			virtual BlendStatePtr CreateBlendState(const BlendStateDesc& desc) = 0;

			/// <summary>
			/// 创建模板缓冲区状态对象
			/// </summary>
			/// <param name="desc">描述表</param>
			/// <returns></returns>
			virtual DepthStencilStatePtr CreateDepthStencilState(const DepthStencilDesc& desc) = 0;

			/// <summary>
			/// 创建输入布局对象
			/// </summary>
			/// <param name="pShader">顶点着色器对象</param>
			/// <param name="elements">数据类型数</param>
			/// <param name="pDecls">数据类型数组</param>
			/// <returns></returns>
			virtual IInputLayout* CreateInputLayout(IVertexShader* pShader, uint32 elements, const VertexDeclaration* pVertexDeclaration) = 0;

			/// <summary>
			/// 创建顶点着色器
			/// </summary>
			/// <param name="binarySize">代码字节数</param>
			/// <param name="pBinary">着色器代码</param>
			/// <returns></returns>
			virtual IVertexShader* CreateVertexShader(uint32 binarySize, uint8* pBinary) = 0;

			/// <summary>
			/// 创建像素着色器
			/// </summary>
			/// <param name="binarySize">代码字节数</param>
			/// <param name="pBinary">着色器代码</param>
			/// <returns></returns>
			virtual IPixelShader* CreatePixelShader(uint32 binarySize, uint8* pBinary) = 0;

			/// <summary>
			/// 创建顶点缓冲区对象
			/// </summary>
			/// <param name="vertices">顶点数</param>
			/// <param name="vertexBytes">顶点字节数</param>
			/// <param name="isDynamic">缓冲区是否动态</param>
			/// <param name="pData">顶点数据</param>
			/// <returns></returns>
			virtual IVertexBuffer* CreateVertexBuffer(uint32 vertices, uint32 vertexBytes, sBoolean isDynamic, void* pData) = 0;

			/// <summary>
			/// 创建顶点索引缓冲区对象
			/// </summary>
			/// <param name="indices">索引数</param>
			/// <param name="format">索引格式</param>
			/// <param name="isDynamic">缓冲区是否动态</param>
			/// <param name="pData">顶点索引数据</param>
			/// <returns></returns>
			virtual IVertexIndexBuffer* CreateVertexIndexBuffer(uint32 indices, VertexIndexFormat format, sBoolean isDynamic, void* pData) = 0;

			/// <summary>
			/// 创建常量缓冲区对象
			/// </summary>
			/// <param name="byteWidth">缓冲区数据大小</param>
			/// <returns></returns>
			virtual IConstantBuffer* CreateConstantBuffer(uint32 byteWidth) = 0;
		public:
			/// <summary>
			/// 绘制图元
			/// </summary>
			/// <param name="type">图元类型</param>
			/// <param name="offset">顶点偏移值</param>
			/// <param name="primitives">绘制图元数</param>
			virtual void DrawPrimitive(PrimitiveTopology type, uint32 offset, uint32 primitives) = 0;

			/// <summary>
			/// 绘制图元
			/// </summary>
			/// <param name="type">图元类型</param>
			/// <param name="startVertex">顶点偏移值</param>
			/// <param name="startIndex">顶点索引偏移值</param>
			/// <param name="primitives">绘制图元数</param>
			virtual void DrawIndexedPrimitive(PrimitiveTopology type, uint32 startVertex, uint32 startIndex, uint32 primitives) = 0;
		public:
			/// <summary>
			/// 设置视口
			/// </summary>
			/// <param name="x">视口x轴坐标</param>
			/// <param name="y">视口y轴坐标</param>
			/// <param name="width">视口宽度</param>
			/// <param name="height">视口高度</param>
			/// <param name="minDepth">视口做小深度(值为0到1)</param>
			/// <param name="maxDepth">视口做大深度(值为0到1)</param>
			virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height, F32 minDepth, F32 maxDepth) = 0;

			/// <summary>
			/// 设置当前顶点布局
			/// </summary>
			/// <param name="pInputLayout">顶点布局对象</param>
			virtual void SetInputLayout(IInputLayout* pInputLayout) = 0;

			/// <summary>
			/// 设置顶点着色器
			/// </summary>
			/// <param name="pShader">顶点着色器对象</param>
			virtual void SetVertexShader(IVertexShader* pShader) = 0;

			/// <summary>
			/// 设置片元着色器
			/// </summary>
			/// <param name="pShader">像素着色器</param>
			virtual void SetPixelShader(IPixelShader* pShader) = 0;

			/// <summary>
			/// 设置顶点缓冲区对象
			/// </summary>
			/// <param name="stream">渲染数据流索引</param>
			/// <param name="stride">渲染数据流中顶点间内存的大小</param>
			/// <param name="offset">渲染数据流的起始位置</param>
			/// <param name="pBuffer">顶点缓冲区对象</param>
			virtual void SetVertexBuffer(uint32 stream, uint32 stride, uint32 offset, IVertexBuffer* pBuffer) = 0;

			/// <summary>
			/// 设置顶点索引缓冲区对象
			/// </summary>
			/// <param name="offset">索引偏移量</param>
			/// <param name="pBuffer">顶点索引缓冲区对象</param>
			virtual void SetVertexIndexBuffer(uint32 offset, IVertexIndexBuffer* pBuffer) = 0;
		};
	}

	extern "C" EXPORT_MODULE Graphics::IDevice * GetGraphicsDevice();
	typedef Graphics::IDevice* (*GetGraphicsDeviceFunc)();
}

#endif // !__GRAPHICS_DEVICE_H__

