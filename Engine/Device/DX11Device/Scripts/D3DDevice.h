#ifndef __D3D_DEVICE_H__
#define __D3D_DEVICE_H__

#include <memory>
#include "D3DStateCache.h"
#include "Graphics/GraphicsDevice.h"

namespace StarEngine
{
	class D3DDevice : public Graphics::IDevice
	{
		using D3DDevicePtr = std::shared_ptr<D3DDevice>;
	protected:
		D3DDevice();
		D3DDevice(const D3DDevice&) = delete;
		D3DDevice& operator =(const D3DDevice&) = delete;
	public:
		virtual ~D3DDevice();
	public:
		/// <summary>
		/// 创建图形设备
		/// </summary>
		/// <param name="error">错误信息</param>
		/// <returns></returns>
		virtual sBoolean Create(std::string& error) sealed;

		/// <summary>
		/// 注销图形设备
		/// </summary>
		virtual void Destroy() sealed;

		/// <summary>
		/// 填充渲染缓冲区
		/// </summary>
		/// <param name="flags">填充指令</param>
		/// <param name="color">背景颜色</param>
		/// <param name="depth">背景深度</param>
		/// <param name="stencil">背景模板值</param>
		virtual void Clear(uint32 flags, const Color& color, F32 depth, uint8 stencil) sealed;
	public:
		/// <summary>
		/// 是否反向Z
		/// </summary>
		/// <returns></returns>
		virtual sBoolean UsesReverseZ() sealed;
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
		virtual Graphics::IDeviceWindow* CreateDeviceWindow(PlatformWindowHandle window, int32 width, int32 height, Graphics::DepthBufferFormat format, sBoolean sRGB) sealed;

		/// <summary>
		/// 创建光栅化状态
		/// </summary>
		/// <param name="desc">描述表</param>
		/// <returns></returns>
		virtual Graphics::RasterizerStatePtr CreateRasterizerState(const Graphics::RasterizerDesc& desc) sealed;

		/// <summary>
		/// 创建混合状态
		/// </summary>
		/// <param name="desc">混合状态描述表</param>
		/// <returns></returns>
		virtual Graphics::BlendStatePtr CreateBlendState(const Graphics::BlendStateDesc& desc) sealed;

		/// <summary>
		/// 创建模板缓冲区状态对象
		/// </summary>
		/// <param name="desc">描述表</param>
		/// <returns></returns>
		virtual Graphics::DepthStencilStatePtr CreateDepthStencilState(const Graphics::DepthStencilDesc& desc) sealed;

		/// <summary>
		/// 创建输入布局对象
		/// </summary>
		/// <param name="pShader">顶点着色器对象</param>
		/// <param name="elements">数据类型数</param>
		/// <param name="pDecls">数据类型数组</param>
		/// <returns></returns>
		virtual Graphics::IInputLayout* CreateInputLayout(Graphics::IVertexShader* pShader, uint32 elements, const Graphics::VertexDeclaration* pVertexDeclaration) sealed;

		/// <summary>
		/// 创建顶点着色器
		/// </summary>
		/// <param name="binarySize">代码字节数</param>
		/// <param name="pBinary">着色器代码</param>
		/// <returns></returns>
		virtual Graphics::IVertexShader* CreateVertexShader(uint32 binarySize, uint8* pBinary) sealed;

		/// <summary>
		/// 创建像素着色器
		/// </summary>
		/// <param name="binarySize">代码字节数</param>
		/// <param name="pBinary">着色器代码</param>
		/// <returns></returns>
		virtual Graphics::IPixelShader* CreatePixelShader(uint32 binarySize, uint8* pBinary) sealed;

		/// <summary>
		/// 创建顶点缓冲区对象
		/// </summary>
		/// <param name="vertices">顶点数</param>
		/// <param name="vertexBytes">顶点字节数</param>
		/// <param name="isDynamic">缓冲区是否动态</param>
		/// <param name="pData">顶点数据</param>
		/// <returns></returns>
		virtual Graphics::IVertexBuffer* CreateVertexBuffer(uint32 vertices, uint32 vertexBytes, sBoolean isDynamic, void* pData) sealed;

		/// <summary>
		/// 创建顶点索引缓冲区对象
		/// </summary>
		/// <param name="indices">索引数</param>
		/// <param name="format">索引格式</param>
		/// <param name="isDynamic">缓冲区是否动态</param>
		/// <param name="pData">顶点索引数据</param>
		/// <returns></returns>
		virtual Graphics::IVertexIndexBuffer* CreateVertexIndexBuffer(uint32 indices, Graphics::VertexIndexFormat format, sBoolean isDynamic, void* pData) sealed;

		/// <summary>
		/// 创建常量缓冲区对象
		/// </summary>
		/// <param name="byteWidth">缓冲区数据大小</param>
		/// <returns></returns>
		virtual Graphics::IConstantBuffer* CreateConstantBuffer(uint32 byteWidth) sealed;

		//public:
		//	/**
		//	*	创建纹理采样对象
		//	*	@param desc	描述表
		//	*/
		//	virtual IGfxTextureSampler* CreateTextureSampler(const GfxTextureSamplerDesc& desc) sealed;
		//public:
		//	/**
		//	*	创建2D纹理对象
		//	*	@param width	纹理宽度
		//	*	@param height	纹理高度
		//	*	@param format	纹理格式
		//	*	@param isMipmap	是否使用mipmap
		//	*	@param pData	纹理数据
		//	*/
		//	virtual IGfxTexture* CreateTexture2D(uint32 width, uint32 height, GraphicsFormat format, sBoolean isMipmap, const void* pData) sealed;

		//	/**
		//	*	创建3D纹理对象
		//	*	@param width		纹理宽度
		//	*	@param height		纹理高度
		//	*	@param depth		纹理深度
		//	*	@param format		纹理格式
		//	*	@param bitPerPixel	像素位数
		//	*	@param pData		纹理数据
		//	*/
		//	virtual IGfxTexture* CreateTexture3D(uint32 width, uint32 height, uint32 depth, GraphicsFormat format, uint8 bitPerPixel, const void* pData) sealed;

		//	/**
		//	*	创建动态纹理对象
		//	*	@param width				纹理宽度
		//	*	@param height				纹理高度
		//	*	@param format				纹理格式
		//	*	@param depthStencilFormat	深度模板格式
		//	*/
		//	virtual IGfxTexture* CreateRenderTexture(uint32 width, uint32 height, GraphicsFormat format, GraphicsFormat depthStencilFormat) sealed;
		//public:
		//	/**
		//	*	创建顶点布局对象
		//	*	@param pShader			顶点着色器对象
		//	*	@param elements			输入顶点元素数目
		//	*	@param pVertexElements	输入顶点元素
		//	*/
		//	virtual IGfxVertexLayer* CreateVertexLayer(IGfxShader* pShader, uint32 elements, const GfxVertexElement* pVertexElements) sealed;

		//	/**
		//	*	创建几何着色器对象
		//	*	@param pFilename	文件名
		//	*	@param pEntry		着色器入口函数
		//	*	@param pProfile		着色器模型版本
		//	*	@param ppError		错误信息
		//	*/
		//	virtual IGfxShader* CreateGeometryShaderFromFile(const wchar_t* pFilename, const char* pEntry, const char* pProfile, char** ppError) sealed;

		//	/**
		//	*	创建几何着色器对象
		//	*	@param streamSize	流数据长度
		//	*	@param pStreamData	流数据
		//	*	@param pEntry		着色器入口函数
		//	*	@param pProfile		着色器模型版本
		//	*	@param ppError		错误信息
		//	*/
		//	virtual IGfxShader* CreateGeometryShaderFromStream(uint32 streamSize, const void* pStreamData, const char* pEntry, const char* pProfile, char** ppError) sealed;
	public:
		/// <summary>
		/// 绘制图元
		/// </summary>
		/// <param name="type">图元类型</param>
		/// <param name="offset">顶点偏移值</param>
		/// <param name="primitives">绘制图元数</param>
		virtual void DrawPrimitive(Graphics::PrimitiveTopology type, uint32 offset, uint32 primitives) sealed;

		/// <summary>
		/// 绘制图元
		/// </summary>
		/// <param name="type">图元类型</param>
		/// <param name="startVertex">顶点偏移值</param>
		/// <param name="startIndex">顶点索引偏移值</param>
		/// <param name="primitives">绘制图元数</param>
		virtual void DrawIndexedPrimitive(Graphics::PrimitiveTopology type, uint32 startVertex, uint32 startIndex, uint32 primitives) sealed;
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
		virtual void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height, F32 minDepth, F32 maxDepth) sealed;

		/// <summary>
		/// 设置当前顶点布局
		/// </summary>
		/// <param name="pInputLayout">顶点布局对象</param>
		virtual void SetInputLayout(Graphics::IInputLayout* pInputLayout) sealed;

		/// <summary>
		/// 设置顶点着色器
		/// </summary>
		/// <param name="pShader">顶点着色器对象</param>
		virtual void SetVertexShader(Graphics::IVertexShader* pShader) sealed;

		/// <summary>
		/// 设置片元着色器
		/// </summary>
		/// <param name="pShader">像素着色器</param>
		virtual void SetPixelShader(Graphics::IPixelShader* pShader) sealed;

		/// <summary>
		/// 设置顶点缓冲区对象
		/// </summary>
		/// <param name="stream">渲染数据流索引</param>
		/// <param name="stride">渲染数据流中顶点间内存的大小</param>
		/// <param name="offset">渲染数据流的起始位置</param>
		/// <param name="pBuffer">顶点缓冲区对象</param>
		virtual void SetVertexBuffer(uint32 stream, uint32 stride, uint32 offset, Graphics::IVertexBuffer* pBuffer) sealed;

		/// <summary>
		/// 设置顶点索引缓冲区对象
		/// </summary>
		/// <param name="offset">索引偏移量</param>
		/// <param name="pBuffer">顶点索引缓冲区对象</param>
		virtual void SetVertexIndexBuffer(uint32 offset, Graphics::IVertexIndexBuffer* pBuffer) sealed;

		//	/**
		//	*	设置纹理采样状态
		//	*	@param pSampler	采样对象
		//	*	@param slot		纹理通道
		//	*/
		//	virtual void SetTextureSampler(IGfxTextureSampler* pSampler, uint32 slot) sealed;

		//	/**
		//	*	设置纹理单元
		//	*	@param stage	纹理单元索引
		//	*	@param pTexture	纹理对象
		//	*/
		//	virtual void SetTexture(uint32 stage, IGfxTexture* pTexture) sealed;

		//	/**
		//	*	设置渲染目标
		//	*	@param texture	纹理对象
		//	*/
		//	virtual void SetRenderTarget(IGfxTexture* pTexture) sealed;

		//	/**
		//	*	设置常量缓冲区
		//	*	@param slot		缓冲区索引
		//	*	@param user		使用者参数
		//	*	@param buffer	常量缓冲区对象
		//	*/
		//	virtual void SetConstantBuffer(uint32 slot, GfxConstantUser user, IGfxConstantBuffer* pBuffer) sealed;

		//	/**
		//	*	设置几何着色器
		//	*	@param pShader	着色器对象
		//	*/
		//	virtual void SetGeometryShader(IGfxShader* pShader) sealed;
	public:
		/// <summary>
		/// 返回最大采样数
		/// </summary>
		/// <returns></returns>
		uint32 MaxSamplerCount();
	public:
		/// <summary>
		/// 返回GfxDevice实例对象
		/// </summary>
		/// <returns></returns>
		static D3DDevice* Instance();
	private:
		D3DStateCache	m_StateCache;
	private:
		static D3DDevicePtr	s_Instance;
	};
}

#endif
