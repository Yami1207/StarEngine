#ifndef __GRAPHICS_TYPES_H__
#define __GRAPHICS_TYPES_H__

#include "GraphicsEnums.h"
#include "Shader/ShaderTypes.h"
#include "Utility/SmartPointer.h"

#if PLATFORM_WINDOWS
typedef struct HWND__* PlatformWindowHandle;
#else
typedef void* PlatformWindowHandle;
#endif

// 最大支持渲染目标（RT）数
#define MAX_SUPPORTED_RENDER_TARGETS	8

// 顶点布局最大数
#define MAX_VERTEX_ELEMENTS				32

#define MAX_SHADER_TEXCOORD_CHANNELS	8

namespace StarEngine
{
	namespace Graphics
	{
		struct RasterizerDesc
		{
			RasterizerDesc();

			FillMode	fillMode;
			CullMode	cullMode;

			// 逆时针为正面
			sBoolean	frontCounterClockwise;

			// 像素深度偏移值
			int32		depthBias;

			// 像素最大深度偏差
			F32			depthBiasClamp;

			// 像素斜率上标量
			F32			slopeScaledDepthBias;

			// 启用基于距离剪裁
			sBoolean	enableDepthClip;

			// 启用矩形剔除
			sBoolean	enableScissor;

			// 启用四边形或alpha线抗锯齿算法
			sBoolean	enableMultisample;

			// 启用行抗锯齿
			sBoolean	enableAntialiasedLine;
		};

		struct RenderTargetBlendStateDesc
		{
			RenderTargetBlendStateDesc();

			BlendOp		blendOp;
			BlendMode	srcBlend;
			BlendMode	dstBlend;

			BlendOp		blendOpAlpha;
			BlendMode	srcBlendAlpha;
			BlendMode	dstBlendAlpha;

			uint8		writeMask;
		};

		struct BlendStateDesc
		{
			BlendStateDesc();

			sBoolean	enableIndependentBlend;

			RenderTargetBlendStateDesc	rt[MAX_SUPPORTED_RENDER_TARGETS];
		};

		struct DepthStencilOpDesc
		{
			DepthStencilOpDesc();

			StencilOp	stencilFailOp;
			StencilOp	stencilDepthFailOp;
			StencilOp	stencilPassOp;
			CompareFunc	stencilFunc;
		};

		struct DepthStencilDesc
		{
			DepthStencilDesc();

			sBoolean	enableDepth;
			sBoolean	enableDepthWrite;
			CompareFunc	depthFunc;

			sBoolean	enableStencil;
			uint8		stencilReadMask;
			uint8		stencilWriteMask;

			DepthStencilOpDesc	frontFace;
			DepthStencilOpDesc	backFace;
		};

		struct VertexDeclaration
		{
			ShaderVertexType	type;

			uint8	dimension;
			uint32	offset;
		};

		class IDevcieState : public IReferenceCount
		{
		public:
			virtual ~IDevcieState() { }

			virtual void Destroy() const
			{
				delete const_cast<IDevcieState*>(this);
			}
		};

		class IRasterizerState : public IDevcieState
		{
		public:
			/// <summary>
			/// 应用状态
			/// </summary>
			/// <returns></returns>
			virtual void Apply() = 0;
		};

		class IBlendState : public IDevcieState
		{
		public:
			/// <summary>
			/// 应用状态
			/// </summary>
			/// <param name="factor">混合因子</param>
			/// <param name="mask">采样</param>
			virtual void Apply(const Vector4& factor = Vector4::zero, uint32 mask = 0xffffffff) = 0;
		};

		class IDepthStencilState : public IDevcieState
		{
		public:
			/// <summary>
			/// 应用状态
			/// </summary>
			/// <param name="ref">模板参考值</param>
			virtual void Apply(uint32 ref = 0) = 0;
		};

		class IDevcieResource
		{
		public:
			virtual ~IDevcieResource() {}
		};

		class IInputLayout : public IDevcieResource
		{
		};

		class IVertexShader : public IDevcieResource
		{
		};

		class IPixelShader : public IDevcieResource
		{
		};

		class IBaseBuffer : public IDevcieResource
		{
		public:
			/// <summary>
			/// 是否有效
			/// </summary>
			/// <returns></returns>
			virtual sBoolean IsValid() = 0;

			/// <summary>
			/// 返回数据大小
			/// </summary>
			/// <returns></returns>
			virtual uint32 DataBytes() = 0;
		};

		class IVertexBuffer : public IBaseBuffer
		{
		};

		class IVertexIndexBuffer : public IBaseBuffer
		{
		};

		class IConstantBuffer : public IBaseBuffer
		{
		public:
			/// <summary>
			/// 设置数据
			/// </summary>
			/// <param name="pData"></param>
			/// <param name="size"></param>
			virtual void SetData(const void* pData, uint32 size) = 0;

			/// <summary>
			/// 绑定常量缓冲区
			/// </summary>
			/// <param name="slot">寄存器索引</param>
			virtual void Bind(uint32 slot) = 0;
		};

		typedef SmartPointer<IRasterizerState> RasterizerStatePtr;
		typedef SmartPointer<IBlendState> BlendStatePtr;
		typedef SmartPointer<IDepthStencilState> DepthStencilStatePtr;

		/// <summary>
		/// 返回图元数
		/// </summary>
		/// <param name="type">图元类型</param>
		/// <param name="count">顶点数或顶点索引数</param>
		/// <returns></returns>
		uint32 ToPrimitives(PrimitiveTopology type, uint32 count);

		/// <summary>
		/// 根据图元类型返回绘制所需的顶点数或顶点索引数
		/// </summary>
		/// <param name="type">图元类型</param>
		/// <param name="primitives">图元数</param>
		/// <returns></returns>
		uint32 ToDrawCount(PrimitiveTopology type, uint32 primitives);
	}
}

#endif // !__GRAPHICS_TYPES_H__
