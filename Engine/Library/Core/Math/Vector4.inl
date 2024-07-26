#pragma once

namespace StarEngine
{
	inline Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
	}

	inline Vector4::Vector4(F32 value) : x(value), y(value), z(value), w(value)
	{
	}

	inline Vector4::Vector4(F32 _x, F32 _y, F32 _z, F32 _w /* = 0.0f */) : x(_x), y(_y), z(_z), w(_w)
	{
	}

	inline Vector4::Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w)
	{
	}

	inline void Vector4::Set(F32 x, F32 y, F32 z, F32 w /* = 0.0f */)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	inline void Vector4::Set(const Vector4& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->w = other.w;
	}

	inline void Vector4::StoreXY(F32* p)
	{
		p[0] = x;
		p[1] = y;
	}

	inline void Vector4::StoreXYZ(F32* p)
	{
		p[0] = x;
		p[1] = y;
		p[2] = z;
	}

	inline F32 Vector4::DotProduct(const Vector4& other) const
	{
		return (other.x * x) + (other.y * y) + (other.z * z) + (other.w * w);
	}

	inline Vector4& Vector4::operator =(const Vector4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;

		return *this;
	}

	inline Vector4& Vector4::operator =(F32 value)
	{
		x = y = z = w = value;
		return *this;
	}

	inline Vector4& Vector4::operator +=(const Vector4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	inline Vector4& Vector4::operator -=(const Vector4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	inline Vector4& Vector4::operator *=(F32 value)
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;
		this->w *= value;

		return *this;
	}

	inline Vector4& Vector4::operator /=(F32 value)
	{
		F32 fReciprocal = 1.0f / value;

		x *= fReciprocal;
		y *= fReciprocal;
		z *= fReciprocal;
		w *= fReciprocal;

		return *this;
	}

	inline F32& Vector4::operator [](int32 nIndex)
	{
		return v[nIndex];
	}

	inline const F32& Vector4::operator [](int32 nIndex) const
	{
		return v[nIndex];
	}

	//////////////////////////////////////////////////////////////////////////
	inline Vector4 operator +(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	inline Vector4 operator -(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	inline Vector4 operator *(const Vector4& a, F32 value)
	{
		return Vector4(a.x * value, a.y * value, a.z * value, a.w * value);
	}

	inline Vector4 operator *(F32 value, const Vector4& a)
	{
		return Vector4(a.x * value, a.y * value, a.z * value, a.w * value);
	}

	inline Vector4 operator /(const Vector4& a, F32 value)
	{
		F32 fReciprocal = 1.0f / value;
		return Vector4(a.x * fReciprocal, a.y * fReciprocal, a.z * fReciprocal, a.w * fReciprocal);
	}

	inline bool operator ==(const Vector4& v1, const Vector4& v2)
	{
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
	}

	inline bool operator !=(const Vector4& v1, const Vector4& v2)
	{
		return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z || v1.w != v2.w;
	}

	inline bool operator <(const Vector4& v1, const Vector4& v2)
	{
		if (v1.x < v2.x) return true;
		if (v1.x > v2.x) return false;
		if (v1.y < v2.y) return true;
		if (v1.y > v2.y) return false;
		if (v1.z < v2.z) return true;
		if (v1.z > v2.z) return false;
		return v1.w < v2.w;
	}
}
