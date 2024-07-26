#pragma once

namespace StarEngine
{
	namespace Graphics
	{
		enum class GraphicsFormat
		{
			None = 0,
			First = None,

			// sRGB formats
			R8_SRGB,
			R8G8_SRGB,
			R8G8B8_SRGB,
			R8G8B8A8_SRGB,

			// 8 bit integer formats
			R8_UNorm,
			R8G8_UNorm,
			R8G8B8_UNorm,
			R8G8B8A8_UNorm,
			R8_SNorm,
			R8G8_SNorm,
			R8G8B8_SNorm,
			R8G8B8A8_SNorm,
			R8_UInt,
			R8G8_UInt,
			R8G8B8_UInt,
			R8G8B8A8_UInt,
			R8_SInt,
			R8G8_SInt,
			R8G8B8_SInt,
			R8G8B8A8_SInt,

			// 16 bit integer formats
			R16_UNorm,
			R16G16_UNorm,
			R16G16B16_UNorm,
			R16G16B16A16_UNorm,
			R16_SNorm,
			R16G16_SNorm,
			R16G16B16_SNorm,
			R16G16B16A16_SNorm,
			R16_UInt,
			R16G16_UInt,
			R16G16B16_UInt,
			R16G16B16A16_UInt,
			R16_SInt,
			R16G16_SInt,
			R16G16B16_SInt,
			R16G16B16A16_SInt,

			// 32 bit integer formats
			R32_UInt,
			R32G32_UInt,
			R32G32B32_UInt,
			R32G32B32A32_UInt,
			R32_SInt,
			R32G32_SInt,
			R32G32B32_SInt,
			R32G32B32A32_SInt,

			// HDR formats
			R16_SFloat,
			R16G16_SFloat,
			R16G16B16_SFloat,
			R16G16B16A16_SFloat,
			R32_SFloat,
			R32G32_SFloat,
			R32G32B32_SFloat,
			R32G32B32A32_SFloat,

			// Luminance and Alpha format
			L8_UNorm,
			A8_UNorm,
			A16_UNorm,

			// BGR formats
			B8G8R8_SRGB,
			B8G8R8A8_SRGB,
			B8G8R8_UNorm,
			B8G8R8A8_UNorm,
			B8G8R8_SNorm,
			B8G8R8A8_SNorm,
			B8G8R8_UInt,
			B8G8R8A8_UInt,
			B8G8R8_SInt,
			B8G8R8A8_SInt,

			// 16 bit packed formats
			R4G4B4A4_UNormPack16,
			B4G4R4A4_UNormPack16,
			R5G6B5_UNormPack16,
			B5G6R5_UNormPack16,
			R5G5B5A1_UNormPack16,
			B5G5R5A1_UNormPack16,
			A1R5G5B5_UNormPack16,

			// Packed formats
			E5B9G9R9_UFloatPack32,
			B10G11R11_UFloatPack32,

			A2B10G10R10_UNormPack32,
			A2B10G10R10_UIntPack32,
			A2B10G10R10_SIntPack32,
			A2R10G10B10_UNormPack32,
			A2R10G10B10_UIntPack32,
			A2R10G10B10_SIntPack32,
			A2R10G10B10_XRSRGBPack32,
			A2R10G10B10_XRUNormPack32,
			R10G10B10_XRSRGBPack32,
			R10G10B10_XRUNormPack32,
			A10R10G10B10_XRSRGBPack32,
			A10R10G10B10_XRUNormPack32,

			// ARGB formats... TextureFormat legacy
			A8R8G8B8_SRGB,
			A8R8G8B8_UNorm,
			A32R32G32B32_SFloat,

			// Depth Stencil for formats
			D16_UNorm,
			D24_UNorm,
			D24_UNorm_S8_UInt,
			D32_SFloat,
			D32_SFloat_S8_Uint,
			S8_Uint,

			// Compression formats
			RGBA_DXT1_SRGB, DXTCFirst = RGBA_DXT1_SRGB,
			RGBA_DXT1_UNorm,
			RGBA_DXT3_SRGB,
			RGBA_DXT3_UNorm,
			RGBA_DXT5_SRGB,
			RGBA_DXT5_UNorm, DXTCLast = RGBA_DXT5_UNorm,
			R_BC4_UNorm, RGTCFirst = R_BC4_UNorm,
			R_BC4_SNorm,
			RG_BC5_UNorm,
			RG_BC5_SNorm, RGTCLast = RG_BC5_SNorm,
			RGB_BC6H_UFloat, BPTCFirst = RGB_BC6H_UFloat,
			RGB_BC6H_SFloat,
			RGBA_BC7_SRGB,
			RGBA_BC7_UNorm, BPTCLast = RGBA_BC7_UNorm,

			Last = BPTCLast,
		};

		enum
		{
			GraphicsFormatCount = (int32)(GraphicsFormat::Last)-(int32)(GraphicsFormat::First) + 1,
		};
	}
}

