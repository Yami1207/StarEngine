#include "Core/BaseTypes.h"
#include "Core/Macros.h"

#include "Color.h"

namespace StarEngine
{
	Color Color::white(1.0f, 1.0f, 1.0f);
	Color Color::black(0.0f, 0.0f, 0.0f);
	Color Color::red(1.0f, 0.0f, 0.0f);
	Color Color::green(0.0f, 1.0f, 0.0f);
	Color Color::blue(0.0f, 0.0f, 1.0f);

	Color::Color(uint32 argb)
	{
		SetARGBPack(argb);
	}

	Color::Color(uint8 _r, uint8 _g, uint8 _b, uint8 _a /*= 255*/)
	{
		F32 oneOverNum = 1.0f / 255.0f;
		r = oneOverNum * _r;
		g = oneOverNum * _g;
		b = oneOverNum * _b;
		a = oneOverNum * _a;
	}

	void Color::SetARGBPack(uint32 value)
	{
		F32 oneOverNum = 1.0f / 255.0f;
		r = oneOverNum * (uint8)(value >> 16);
		g = oneOverNum * (uint8)(value >> 8);
		b = oneOverNum * (uint8)(value);
		a = oneOverNum * (uint8)(value >> 24);
	}

	void Color::SetRGBAPack(uint32 value)
	{
		F32 oneOverNum = 1.0f / 255.0f;
		r = oneOverNum * (uint8)(value >> 24);
		g = oneOverNum * (uint8)(value >> 16);
		b = oneOverNum * (uint8)(value >> 8);
		a = oneOverNum * (uint8)(value);
	}

	void Color::SetABGRPack(uint32 value)
	{
		F32 oneOverNum = 1.0f / 255.0f;
		r = oneOverNum * (uint8)(value);
		g = oneOverNum * (uint8)(value >> 8);
		b = oneOverNum * (uint8)(value >> 16);
		a = oneOverNum * (uint8)(value >> 24);
	}

	void Color::Saturate()
	{
		r = MathLib::Clamp(r, 0.0f, 1.0f);
		g = MathLib::Clamp(g, 0.0f, 1.0f);
		b = MathLib::Clamp(b, 0.0f, 1.0f);
		a = MathLib::Clamp(a, 0.0f, 1.0f);
	}

	void Color::Lerp(const Color& from, const Color& to, F32 t)
	{
		F32 t1 = 1.0f - t;
		r = (from.r * t1) + (to.r * t);
		g = (from.g * t1) + (to.g * t);
		b = (from.b * t1) + (to.b * t);
		a = (from.a * t1) + (to.a * t);
	}
}
