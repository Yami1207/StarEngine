#pragma once

namespace StarEngine
{
	inline Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f), pad(0.0f)
	{
	}

	inline Vector3::Vector3(F32 value) : x(value), y(value), z(value), pad(0.0f)
	{
	}

	inline Vector3::Vector3(F32 _x, F32 _y, F32 _z) : x(_x), y(_y), z(_z), pad(0.0f)
	{
	}

	inline Vector3::Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z), pad(0.0f)
	{
	}

	inline Vector3& Vector3::operator =(const Vector3& other)
	{
		this->Set(other);
		return *this;
	}

	inline Vector3& Vector3::operator =(F32 value)
	{
		x = y = z = value;
		return *this;
	}

	inline Vector3& Vector3::operator +=(const Vector3& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	inline Vector3& Vector3::operator -=(const Vector3& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}

	inline Vector3& Vector3::operator *=(F32 value)
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;
		return *this;
	}

	inline Vector3& Vector3::operator /=(F32 value)
	{
		F32 fReciprocal = 1.0f / value;
		this->x *= fReciprocal;
		this->y *= fReciprocal;
		this->z *= fReciprocal;
		return *this;
	}

	inline F32& Vector3::operator [](int32 nIndex)
	{
		return *((F32*)(this) + nIndex);
	}

	inline const F32& Vector3::operator [](int32 nIndex) const
	{
		return *((F32*)(this) + nIndex);
	}

	inline void Vector3::Set(F32 x, F32 y, F32 z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline void Vector3::Set(const Vector3& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}

	inline F32 Vector3::LengthSquared()
	{
		return x * x + y * y + z * z;
	}

	inline F32 Vector3::LengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	inline Vector3 Vector3::ComponentProduct(const Vector3& other) const
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	inline F32 Vector3::DotProduct(const Vector3& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	inline Vector3 Vector3::CrossProduct(const Vector3& other) const
	{
		return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}

	//////////////////////////////////////////////////////////////////////////
	inline Vector3 operator +(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	inline Vector3 operator +(F32 value, const Vector3& v)
	{
		return Vector3(value + v.x, value + v.y, value + v.z);
	}

	inline Vector3 operator +(const Vector3& v, F32 value)
	{
		return Vector3(value + v.x, value + v.y, value + v.z);
	}

	inline Vector3 operator -(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	inline Vector3 operator -(F32 value, const Vector3& v)
	{
		return Vector3(value - v.x, value - v.y, value - v.z);
	}

	inline Vector3 operator -(const Vector3& v, F32 value)
	{
		return Vector3(v.x - value, v.y - value, v.z - value);
	}

	inline Vector3 operator -(const Vector3& v)
	{
		return Vector3(-v.x, -v.y, -v.z);
	}

	inline Vector3 operator *(const Vector3& a, F32 value)
	{
		return Vector3(a.x * value, a.y * value, a.z * value);
	}

	inline Vector3 operator *(F32 value, const Vector3& a)
	{
		return Vector3(a.x * value, a.y * value, a.z * value);
	}

	inline Vector3 operator /(const Vector3& a, F32 value)
	{
		F32 reciprocal = 1.0f / value;
		return Vector3(a.x * reciprocal, a.y * reciprocal, a.z * reciprocal);
	}

	inline bool operator ==(const Vector3& a, const Vector3& b)
	{
		return a.x == b.x && a.y == b.y && a.z == b.z;
	}

	inline bool operator !=(const Vector3& a, const Vector3& b)
	{
		return a.x != b.x || a.y != b.y || a.z != b.z;
	}

	inline bool operator <(const Vector3& v1, const Vector3& v2)
	{
		if (v1.x < v2.x) return true;
		if (v1.x > v2.x) return false;
		if (v1.y < v2.y) return true;
		if (v1.y > v2.y) return false;
		return v1.z < v2.z;
	}
}
