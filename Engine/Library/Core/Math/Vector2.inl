#pragma once

namespace StarEngine
{
	inline Vector2::Vector2() : x(0.0f), y(0.0f)
	{
	}

	inline Vector2::Vector2(F32 value) : x(value), y(value)
	{
	}

	inline Vector2::Vector2(F32 _x, F32 _y) : x(_x), y(_y)
	{
	}

	inline Vector2::Vector2(const Vector2& other) : x(other.x), y(other.y)
	{
	}

	inline void Vector2::Set(F32 x, F32 y)
	{
		this->x = x;
		this->y = y;
	}

	inline void Vector2::Set(const Vector2& other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	inline F32 Vector2::DotProduct(const Vector2& other) const
	{
		return x * other.x + y * other.y;
	}

	inline F32 Vector2::CrossProduct(const Vector2& other) const
	{
		return x * other.y - y * other.x;
	}

	inline Vector2& Vector2::operator =(const Vector2& other)
	{
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	inline Vector2& Vector2::operator =(F32 fValue)
	{
		this->x = this->y = fValue;
		return *this;
	}

	inline Vector2& Vector2::operator +=(const Vector2& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	inline Vector2& Vector2::operator -=(const Vector2& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	inline Vector2& Vector2::operator *=(F32 fValue)
	{
		this->x *= fValue;
		this->y *= fValue;
		return *this;
	}

	inline Vector2& Vector2::operator /=(F32 fValue)
	{
		F32 fReciprocal = 1.0f / fValue;
		this->x *= fReciprocal;
		this->y *= fReciprocal;
		return *this;
	}

	inline F32& Vector2::operator [](int32 nIndex)
	{
		return v[nIndex];
	}

	inline const F32& Vector2::operator [](int32 nIndex) const
	{
		return v[nIndex];
	}

	//////////////////////////////////////////////////////////////////////////
	inline Vector2 operator +(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	inline Vector2 operator -(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	inline Vector2 operator *(F32 fValue, const Vector2& v)
	{
		return Vector2(v.x * fValue, v.y * fValue);
	}

	inline Vector2 operator *(const Vector2& v, F32 fValue)
	{
		return Vector2(v.x * fValue, v.y * fValue);
	}

	inline Vector2 operator /(const Vector2& v, F32 fValue)
	{
		F32 fReciprocal = 1.0f / fValue;
		return Vector2(v.x * fReciprocal, v.y * fReciprocal);
	}

	inline sBoolean operator ==(const Vector2& v0, const Vector2& v1)
	{
		return v0.x == v1.x && v0.y == v1.y;
	}

	inline sBoolean operator !=(const Vector2& v0, const Vector2& v1)
	{
		return v0.x != v1.x || v0.y != v1.y;
	}

	inline sBoolean operator <(const Vector2& v1, const Vector2& v2)
	{
		if (v1.x < v2.x) return sTrue;
		if (v1.x > v2.x) return sFalse;
		return (v1.y < v2.y) ? sTrue : sFalse;
	}
}
