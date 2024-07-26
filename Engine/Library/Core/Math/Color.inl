#pragma once

namespace StarEngine
{
	//////////////////////////////////////////////////////////////////////////
	inline Color::Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f)
	{
	}

	inline Color::Color(const Color& other) : r(other.r), g(other.g), b(other.b), a(other.a)
	{
	}

	inline Color::Color(F32 _r, F32 _g, F32 _b, F32 _a /* = 1.0f */) : r(_r), g(_g), b(_b), a(_a)
	{
	}

	inline void Color::Set(const Color& other)
	{
		r = other.r; g = other.g; b = other.b; a = other.a;
	}

	inline void Color::Set(F32 _r, F32 _g, F32 _b, F32 _a /* = 1.0f */)
	{
		r = _r; g = _g; b = _b; a = _a;
	}

	inline sBoolean Color::IsValidColor() const
	{
		if ((r >= 0.0f && r <= 1.0f) && (g >= 0.0f && g <= 1.0f) && (b >= 0.0f && b <= 1.0f) && (a >= 0.0f && a <= 1.0f))
			return sTrue;
		return sFalse;
	}

	inline uint32 Color::GetARGBPack() const
	{
		return (uint32(a * 255.0f + 0.5) << 24) | (uint32(r * 255.0f + 0.5) << 16) | (uint32(g * 255.0f + 0.5) << 8) | (uint32(b * 255.0f + 0.5) << 0);
	}

	inline uint32 Color::GetRGBAPack() const
	{
		return (uint32(r * 255.0f + 0.5) << 24) | (uint32(g * 255.0f + 0.5) << 16) | (uint32(b * 255.0f + 0.5) << 8) | (uint32(a * 255.0f + 0.5) << 0);
	}

	inline uint32 Color::GetABGRPack() const
	{
		return (uint32(a * 255.0f + 0.5) << 24) | (uint32(b * 255.0f + 0.5) << 16) | (uint32(g * 255.0f + 0.5) << 8) | (uint32(r * 255.0f + 0.5) << 0);
	}

	inline Color Color::operator +(const Color& other) const
	{
		return Color(r + other.r, g + other.g, b + other.b, a + other.a);
	}

	inline Color Color::operator -(const Color& other) const
	{
		return Color(r - other.r, g - other.g, b - other.b, a - other.a);
	}

	inline Color& Color::operator +=(const Color& other)
	{
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;
		return *this;
	}

	inline Color& Color::operator -=(const Color& other)
	{
		r -= other.r;
		g -= other.g;
		b -= other.b;
		a -= other.a;
		return *this;
	}

	inline Color& Color::operator *=(F32 value)
	{
		r *= value;
		g *= value;
		b *= value;
		a *= value;
		return *this;
	}

	inline Color& Color::operator *=(const Color& other)
	{
		r *= other.r;
		g *= other.g;
		b *= other.b;
		a *= other.a;
		return *this;
	}

	inline Color Color::operator /(F32 value) const
	{
		F32 inv = 1.0f / value;
		return Color(r * inv, g * inv, b * inv, a * inv);
	}

	inline Color& Color::operator /=(F32 value)
	{
		F32 inv = 1.0f / value;
		r *= inv;
		g *= inv;
		b *= inv;
		a *= inv;
		return *this;
	}

	inline Color Color::operator -() const
	{
		return Color(-r, -g, -b, -a);
	}

	inline Color& Color::operator =(const Color& other)
	{
		this->r = other.r;
		this->g = other.g;
		this->b = other.b;
		this->a = other.a;
		return *this;
	}

	inline bool Color::operator ==(const Color& other) const
	{
		return (r == other.r && g == other.g && b == other.b && a == other.a);
	}

	inline bool Color::operator !=(const Color& other) const
	{
		return (r != other.r || g != other.g || b != other.b || a != other.a);
	}

	inline F32& Color::operator [](int32 nIndex)
	{
		return value[nIndex];
	}

	inline const F32& Color::operator [](int32 nIndex) const
	{
		return value[nIndex];
	}

	//////////////////////////////////////////////////////////////////////////
	inline Color operator *(F32 value, const Color& color)
	{
		return Color(color.r * value, color.g * value, color.b * value, color.a * value);
	}

	inline Color operator *(const Color& color, F32 value)
	{
		return Color(color.r * value, color.g * value, color.b * value, color.a * value);
	}

	inline Color operator *(const Color& c0, const Color& c1)
	{
		return Color(c0.r * c1.r, c0.g * c1.g, c0.b * c1.b, c0.a * c1.a);
	}

	inline bool operator <(const Color& c0, const Color& c1)
	{
		if (c0.r < c1.r) return true;
		if (c0.r > c1.r) return false;
		if (c0.g < c1.g) return true;
		if (c0.g > c1.g) return false;
		if (c0.b < c1.b) return true;
		if (c0.b > c1.b) return false;
		if (c0.a < c1.a) return true;
		return false;
	}
}
