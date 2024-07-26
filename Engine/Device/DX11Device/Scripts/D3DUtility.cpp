#include "D3DPrivate.h"
#include "D3DUtility.h"

#include <map>

#include "D3DDevice.h"
#include "D3DDeviceWindow.h"

using namespace StarEngine::Graphics;

namespace StarEngine
{
	namespace
	{
		static ID3D11Device* g_pD3DDevice = sNull;
		static ID3D11DeviceContext* g_pImmediateContext = sNull;

		static IDXGIDevice* g_pDXGIDevice = sNull;
		static IDXGIAdapter* g_pDXGIAdapter = sNull;
		static IDXGIFactory* g_pDXGIFactory = sNull;

		static DeviceWindow* g_pActiveWindow = sNull;

		static const DXGI_FORMAT g_kShaderVertexFormat[4] = {
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_R32G32B32_FLOAT,
			DXGI_FORMAT_R32G32B32A32_FLOAT
		};

		static const D3D11_PRIMITIVE_TOPOLOGY g_kPrimitiveTopology[] = {
			// 点列表
			D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,

			// 线列表(每两个点画成一条线段)
			D3D11_PRIMITIVE_TOPOLOGY_LINELIST,

			// 线列表(从一点开始,把所有的点首尾相接)
			D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,

			// 三角形列表(每三个是一个三角形的定点)
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,

			// 三角形带状图形
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,

			// 
			D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST,
		};
	}

	sBoolean InitializeDevice(std::string& error)
	{
		uint32 createFlags = 0;
#ifdef _DEBUG
		createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// 创建Direct3D设备
		D3D_FEATURE_LEVEL level;
		if (FAILED(D3D11CreateDevice(sNull, D3D_DRIVER_TYPE_HARDWARE, nullptr, createFlags, sNull, 0, D3D11_SDK_VERSION, &g_pD3DDevice, &level, &g_pImmediateContext)))
		{
			error = "Create d3d device failed.";
			return sFalse;
		}

		if (FAILED(g_pD3DDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&g_pDXGIDevice)))
		{
			error = "Create DXGI device failed.";
			return sFalse;
		}

		if (FAILED(g_pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&g_pDXGIAdapter)))
		{
			error = "Get DXGI adapter failed.";
			return sFalse;
		}

		// 获得IDXGIFactory接口
		if (FAILED(g_pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&g_pDXGIFactory)))
		{
			error = "Get DXGI factory failed.";
			return sFalse;
		}

		return sTrue;
	}

	void DestroyDevice()
	{
		g_pActiveWindow = sNull;

		SAFE_RELEASE(g_pDXGIFactory);
		SAFE_RELEASE(g_pDXGIAdapter);
		SAFE_RELEASE(g_pDXGIDevice);

		SAFE_RELEASE(g_pImmediateContext);
		SAFE_RELEASE(g_pD3DDevice);
	}

	ID3D11Device* GetD3DDevice()
	{
		return g_pD3DDevice;
	}

	ID3D11DeviceContext* GetImmediateContext()
	{
		return g_pImmediateContext;
	}

	IDXGIFactory* GetDXGIFactory()
	{
		return g_pDXGIFactory;
	}

	void SetActiveWindow(DeviceWindow* pWindow)
	{
		if (g_pActiveWindow != pWindow)
			g_pActiveWindow = pWindow;

		if (g_pActiveWindow != sNull)
		{
			g_pImmediateContext->OMSetRenderTargets(1, &pWindow->ColorSurface().pRenderTargetView, pWindow->DepthSurface().pDepthStencilView);

			uint32 width, height;
			pWindow->GetWindowSize(width, height);
			D3DDevice::Instance()->SetViewport(0, 0, width, height, 0.0f, 1.0f);
		}
		else
		{
			g_pImmediateContext->OMSetRenderTargets(0, sNull, sNull);
			g_pImmediateContext->Flush();
		}
	}

	DeviceWindow* GetActiveWindow()
	{
		return g_pActiveWindow;
	}

	void InitVertexInputLayout(D3D11_INPUT_ELEMENT_DESC& desc, const VertexDeclaration& decl)
	{
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		desc.AlignedByteOffset = decl.offset;
		desc.InputSlot = 0;//element.stream;

		switch (decl.type)
		{
		case ShaderVertexType::Position:
			{
				desc.SemanticName = "POSITION";
				desc.SemanticIndex = 0;
			}
			break;
		case ShaderVertexType::Normal:
			{
				desc.SemanticName = "NORMAL";
				desc.SemanticIndex = 0;
			}
			break;
		case ShaderVertexType::Tangent:
			{
				desc.SemanticName = "TANGENT";
				desc.SemanticIndex = 0;
			}
			break;
		case ShaderVertexType::Color:
			{
				desc.SemanticName = "COLOR";
				desc.SemanticIndex = 0;
			}
			break;
		case ShaderVertexType::TexCoord0:
		case ShaderVertexType::TexCoord1:
		case ShaderVertexType::TexCoord2:
		case ShaderVertexType::TexCoord3:
		case ShaderVertexType::TexCoord4:
		case ShaderVertexType::TexCoord5:
		case ShaderVertexType::TexCoord6:
		case ShaderVertexType::TexCoord7:
			{
				desc.SemanticName = "TEXCOORD";
				desc.SemanticIndex = (uint32)decl.type - (uint32)ShaderVertexType::TexCoord;
			}
			break;
		default:
			break;
		}

		desc.Format = g_kShaderVertexFormat[MathLib::Clamp(decl.dimension - 1, 0, 3)];
	}

	DXGI_FORMAT GetDepthBufferFormat(DepthBufferFormat format)
	{
		if (format == DepthBufferFormat::Depth16Bits)
			return DXGI_FORMAT_D16_UNORM;
		return DXGI_FORMAT_D24_UNORM_S8_UINT;
	}

	//	void TextureDownSampling(uint32 width, uint32 height, uint8* pDestData, const uint8* pSrcData)
	//	{
	//		uint8* pBuffer = pDestData;
	//		for (uint32 y = 0; y < height; ++y)
	//		{
	//			for (uint32 x = 0; x < width; ++x)
	//			{
	//				uint32 dx = x << 1, dy = y << 1;
	//				const uint8* pData0 = pSrcData + ((dx + dy * (width << 1)) << 2);
	//				const uint8* pData1 = pSrcData + ((dx + dy * (width << 1) + 1) << 2);
	//				const uint8* pData2 = pSrcData + ((dx + (dy + 1) * (width << 1)) << 2);
	//				const uint8* pData3 = pSrcData + ((dx + (dy + 1) * (width << 1) + 1) << 2);
	//
	//				for (uint32 index = 0; index < 4; ++index)
	//					pBuffer[index] = (uint8)((pData0[index] + pData1[index] + pData2[index] + pData3[index]) * 0.25f);
	//				pBuffer += 4;
	//			}
	//		}
	//	}

	D3D11_COMPARISON_FUNC ToCompareFunc(CompareFunc compare)
	{
		static const D3D11_COMPARISON_FUNC kCompareFunc[] = {
			D3D11_COMPARISON_LESS,
			D3D11_COMPARISON_LESS_EQUAL,
			D3D11_COMPARISON_GREATER,
			D3D11_COMPARISON_GREATER_EQUAL,
			D3D11_COMPARISON_EQUAL,
			D3D11_COMPARISON_NOT_EQUAL,
			D3D11_COMPARISON_NEVER,
			D3D11_COMPARISON_ALWAYS,
		};
		return kCompareFunc[(uint32)compare];
	}

	DXGI_FORMAT GetDXGIFormat(GraphicsFormat format)
	{
		switch (format)
		{
		case GraphicsFormat::R8G8B8_SRGB:				return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case GraphicsFormat::R8G8B8A8_SRGB:				return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;

		case GraphicsFormat::R8_UNorm:					return DXGI_FORMAT_R8_UNORM;
		case GraphicsFormat::R8G8_UNorm:				return DXGI_FORMAT_R8G8_UNORM;
		case GraphicsFormat::R8G8B8A8_UNorm:			return DXGI_FORMAT_R8G8B8A8_UNORM;

		case GraphicsFormat::R8_SNorm:					return DXGI_FORMAT_R8_SNORM;
		case GraphicsFormat::R8G8_SNorm:				return DXGI_FORMAT_R8G8_SNORM;
		case GraphicsFormat::R8G8B8A8_SNorm:			return DXGI_FORMAT_R8G8B8A8_SNORM;

		case GraphicsFormat::R8_UInt:					return DXGI_FORMAT_R8_UINT;
		case GraphicsFormat::R8G8_UInt:					return DXGI_FORMAT_R8G8_UINT;
		case GraphicsFormat::R8G8B8A8_UInt:				return DXGI_FORMAT_R8G8B8A8_UINT;

		case GraphicsFormat::R8_SInt:					return DXGI_FORMAT_R8_SINT;
		case GraphicsFormat::R8G8_SInt:					return DXGI_FORMAT_R8G8_SINT;
		case GraphicsFormat::R8G8B8A8_SInt:				return DXGI_FORMAT_R8G8B8A8_SINT;

		case GraphicsFormat::R16_UNorm:					return DXGI_FORMAT_R16_UNORM;
		case GraphicsFormat::R16G16_UNorm:				return DXGI_FORMAT_R16G16_UNORM;
		case GraphicsFormat::R16G16B16A16_UNorm:		return DXGI_FORMAT_R16G16B16A16_UNORM;

		case GraphicsFormat::R16_SNorm:					return DXGI_FORMAT_R16_SNORM;
		case GraphicsFormat::R16G16_SNorm:				return DXGI_FORMAT_R16G16_SNORM;
		case GraphicsFormat::R16G16B16A16_SNorm:		return DXGI_FORMAT_R16G16B16A16_SNORM;

		case GraphicsFormat::R16_UInt:					return DXGI_FORMAT_R16_UINT;
		case GraphicsFormat::R16G16_UInt:				return DXGI_FORMAT_R16G16_UINT;
		case GraphicsFormat::R16G16B16A16_UInt:			return DXGI_FORMAT_R16G16B16A16_UINT;

		case GraphicsFormat::R16_SInt:					return DXGI_FORMAT_R16_SINT;
		case GraphicsFormat::R16G16_SInt:				return DXGI_FORMAT_R16G16_SINT;
		case GraphicsFormat::R16G16B16A16_SInt:			return DXGI_FORMAT_R16G16B16A16_SINT;

		case GraphicsFormat::R32_UInt:					return DXGI_FORMAT_R32_UINT;
		case GraphicsFormat::R32G32_UInt:				return DXGI_FORMAT_R32G32_UINT;
		case GraphicsFormat::R32G32B32_UInt:			return DXGI_FORMAT_R32G32B32_UINT;
		case GraphicsFormat::R32G32B32A32_UInt:			return DXGI_FORMAT_R32G32B32A32_UINT;

		case GraphicsFormat::R32_SInt:					return DXGI_FORMAT_R32_SINT;
		case GraphicsFormat::R32G32_SInt:				return DXGI_FORMAT_R32G32_SINT;
		case GraphicsFormat::R32G32B32_SInt:			return DXGI_FORMAT_R32G32B32_SINT;
		case GraphicsFormat::R32G32B32A32_SInt:			return DXGI_FORMAT_R32G32B32A32_SINT;

		case GraphicsFormat::R16_SFloat:				return DXGI_FORMAT_R16_FLOAT;
		case GraphicsFormat::R16G16_SFloat:				return DXGI_FORMAT_R16G16_FLOAT;
		case GraphicsFormat::R16G16B16A16_SFloat:		return DXGI_FORMAT_R16G16B16A16_FLOAT;

		case GraphicsFormat::R32_SFloat:				return DXGI_FORMAT_R32_FLOAT;
		case GraphicsFormat::R32G32_SFloat:				return DXGI_FORMAT_R32G32_FLOAT;
		case GraphicsFormat::R32G32B32_SFloat:			return DXGI_FORMAT_R32G32B32_FLOAT;
		case GraphicsFormat::R32G32B32A32_SFloat:		return DXGI_FORMAT_R32G32B32A32_FLOAT;

		case GraphicsFormat::L8_UNorm:					return DXGI_FORMAT_A8_UNORM;
		case GraphicsFormat::A8_UNorm:					return DXGI_FORMAT_A8_UNORM;
		case GraphicsFormat::A16_UNorm:					return DXGI_FORMAT_R16_UNORM;

		case GraphicsFormat::B8G8R8_SRGB:				return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case GraphicsFormat::B8G8R8A8_SRGB:				return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;

		case GraphicsFormat::B8G8R8_UNorm:				return DXGI_FORMAT_B8G8R8X8_UNORM;
		case GraphicsFormat::B8G8R8A8_UNorm:			return DXGI_FORMAT_B8G8R8A8_UNORM;

		case GraphicsFormat::R4G4B4A4_UNormPack16:		return DXGI_FORMAT_B4G4R4A4_UNORM;
		case GraphicsFormat::B4G4R4A4_UNormPack16:		return DXGI_FORMAT_B4G4R4A4_UNORM;

		case GraphicsFormat::R5G6B5_UNormPack16:		return DXGI_FORMAT_B5G6R5_UNORM;
		case GraphicsFormat::B5G6R5_UNormPack16:		return DXGI_FORMAT_B5G6R5_UNORM;

		case GraphicsFormat::R5G5B5A1_UNormPack16:		return DXGI_FORMAT_B5G5R5A1_UNORM;
		case GraphicsFormat::B5G5R5A1_UNormPack16:		return DXGI_FORMAT_B5G5R5A1_UNORM;

		case GraphicsFormat::E5B9G9R9_UFloatPack32:		return DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
		case GraphicsFormat::B10G11R11_UFloatPack32:	return DXGI_FORMAT_R11G11B10_FLOAT;

		case GraphicsFormat::A2B10G10R10_UNormPack32:	return DXGI_FORMAT_R10G10B10A2_UNORM;
		case GraphicsFormat::A2B10G10R10_UIntPack32:	return DXGI_FORMAT_R10G10B10A2_UINT;
		case GraphicsFormat::A2R10G10B10_XRUNormPack32:	return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
		case GraphicsFormat::R10G10B10_XRUNormPack32:	return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;

		case GraphicsFormat::D16_UNorm:					return DXGI_FORMAT_D16_UNORM;
		case GraphicsFormat::D24_UNorm_S8_UInt:			return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case GraphicsFormat::D32_SFloat:				return DXGI_FORMAT_D32_FLOAT;
		case GraphicsFormat::D32_SFloat_S8_Uint:		return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		case GraphicsFormat::S8_Uint:					return DXGI_FORMAT_X24_TYPELESS_G8_UINT;

		case GraphicsFormat::RGBA_DXT1_SRGB:			return DXGI_FORMAT_BC1_UNORM_SRGB;
		case GraphicsFormat::RGBA_DXT1_UNorm:			return DXGI_FORMAT_BC1_UNORM;
		case GraphicsFormat::RGBA_DXT3_SRGB:			return DXGI_FORMAT_BC2_UNORM_SRGB;
		case GraphicsFormat::RGBA_DXT3_UNorm:			return DXGI_FORMAT_BC2_UNORM;
		case GraphicsFormat::RGBA_DXT5_SRGB:			return DXGI_FORMAT_BC3_UNORM_SRGB;
		case GraphicsFormat::RGBA_DXT5_UNorm:			return DXGI_FORMAT_BC3_UNORM;
		case GraphicsFormat::R_BC4_UNorm:				return DXGI_FORMAT_BC4_UNORM;
		case GraphicsFormat::R_BC4_SNorm:				return DXGI_FORMAT_BC4_SNORM;
		case GraphicsFormat::RG_BC5_UNorm:				return DXGI_FORMAT_BC5_UNORM;
		case GraphicsFormat::RG_BC5_SNorm:				return DXGI_FORMAT_BC5_SNORM;
		case GraphicsFormat::RGB_BC6H_UFloat:			return DXGI_FORMAT_BC6H_UF16;
		case GraphicsFormat::RGB_BC6H_SFloat:			return DXGI_FORMAT_BC6H_SF16;
		case GraphicsFormat::RGBA_BC7_SRGB:				return DXGI_FORMAT_BC7_UNORM_SRGB;
		case GraphicsFormat::RGBA_BC7_UNorm:			return DXGI_FORMAT_BC7_UNORM;
		}

		return DXGI_FORMAT_R8G8B8A8_UNORM;
	}

	D3D11_FILL_MODE ToFileMode(FillMode mode)
	{
		static const D3D11_FILL_MODE kFillMode[] = {
			D3D11_FILL_WIREFRAME,
			D3D11_FILL_SOLID
		};
		return kFillMode[(int)mode];
	}

	D3D11_CULL_MODE ToCullMode(CullMode mode)
	{
		static const D3D11_CULL_MODE kCullMode[] = {
			D3D11_CULL_NONE,
			D3D11_CULL_FRONT,
			D3D11_CULL_BACK
		};
		return kCullMode[(int)mode];
	}

	D3D11_BLEND_OP ToBlendOp(BlendOp op)
	{
		static const D3D11_BLEND_OP kBlendOp[] = {
			D3D11_BLEND_OP_ADD,
			D3D11_BLEND_OP_SUBTRACT,
			D3D11_BLEND_OP_REV_SUBTRACT,
			D3D11_BLEND_OP_MIN,
			D3D11_BLEND_OP_MAX,
		};
		return kBlendOp[(uint32)op];
	}

	D3D11_BLEND ToBlendMode(BlendMode mode)
	{
		static const D3D11_BLEND kBlendMode[] = {
			D3D11_BLEND_ZERO,				// 混合因子为(0,0,0,0)
			D3D11_BLEND_ONE,				// 混合因子为(1,1,1,1)

			D3D11_BLEND_SRC_COLOR,			// 混合因子为(src_red,src_green,src_blue,src_alpha)
			D3D11_BLEND_INV_SRC_COLOR,		// 混合因子为(1 - src_red,1 - src_green,1 - src_blue,1 - src_alpha)
			D3D11_BLEND_SRC_ALPHA,			// 混合因子为(src_alpha,src_alpha,src_alpha,src_alpha)
			D3D11_BLEND_INV_SRC_ALPHA,		// 混合因子为(1 - src_alpha,1 - src_alpha,1 - src_alpha,1 - src_alpha)

			D3D11_BLEND_DEST_COLOR,			// 混合因子为(dst_red,dst_green,dst_blue,dst_alpha)
			D3D11_BLEND_INV_DEST_COLOR,		// 混合因子为(1 - dst_red,1 - dst_green,1 - dst_blue,1 - dst_alpha)
			D3D11_BLEND_DEST_ALPHA,			// 混合因子为(dst_alpha,dst_alpha,dst_alpha,dst_alpha)
			D3D11_BLEND_INV_DEST_ALPHA,		// 混合因子为(1 - dst_alpha,1 - dst_alpha,1 - dst_alpha,1 - dst_alpha)

			D3D11_BLEND_SRC_ALPHA_SAT,		// 

			D3D11_BLEND_BLEND_FACTOR,		// 混合因子为(blend_factor_red,blend_factor_green,blend_factor_blue,blend_factor_alpha)
			D3D11_BLEND_INV_BLEND_FACTOR,	// 混合因子为(1 - blend_factor_red,1 - blend_factor_green,1 - blend_factor_blue,1 - blend_factor_alpha)
		};
		return kBlendMode[(uint32)mode];
	}
	
	D3D11_STENCIL_OP ToStencilOp(StencilOp op)
	{
		static const D3D11_STENCIL_OP kStencilOp[] = {
			D3D11_STENCIL_OP_KEEP,
			D3D11_STENCIL_OP_ZERO,
			D3D11_STENCIL_OP_REPLACE,
			D3D11_STENCIL_OP_INCR_SAT,
			D3D11_STENCIL_OP_DECR_SAT,
			D3D11_STENCIL_OP_INVERT,
			D3D11_STENCIL_OP_INCR,
			D3D11_STENCIL_OP_DECR,
		};
		return kStencilOp[(uint32)op];
	}

	//	D3D11_FILTER GetTextureFilter(GfxTextureFilter filter)
	//	{
	//		static const D3D11_FILTER sTextureFilter[] = {
	//			D3D11_FILTER_MIN_MAG_MIP_POINT,
	//			D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,
	//			D3D11_FILTER_MIN_MAG_MIP_LINEAR,
	//			D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT,
	//			D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
	//			D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
	//		};
	//		return sTextureFilter[(int)filter];
	//	}
	//
	//	D3D11_TEXTURE_ADDRESS_MODE GetTextureAddress(GfxTextureAddress address)
	//	{
	//		static const D3D11_TEXTURE_ADDRESS_MODE sTextureAddress[] = {
	//			D3D11_TEXTURE_ADDRESS_WRAP,		// 叠映射寻址
	//			D3D11_TEXTURE_ADDRESS_MIRROR,	// 镜像纹理寻址
	//			D3D11_TEXTURE_ADDRESS_CLAMP,	// 夹取纹理寻址
	//			D3D11_TEXTURE_ADDRESS_BORDER,	// 边框纹理寻址
	//		};
	//		return sTextureAddress[(int)address];
	//	}
	
	D3D11_PRIMITIVE_TOPOLOGY ToPrimitiveTopology(PrimitiveTopology type)
	{
		return g_kPrimitiveTopology[(int32)type];
	}
}
