#pragma once

namespace StarEngine
{
	inline Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{
	}

	inline Quaternion::Quaternion(F32 _x, F32 _y, F32 _z, F32 _w) : x(_x), y(_y), z(_z), w(_w)
	{
	}

	inline Quaternion::Quaternion(const Quaternion& other) : x(other.x), y(other.y), z(other.z), w(other.w)
	{
	}

	inline void Quaternion::Set(F32 x /* = 0.0f */, F32 y /* = 0.0f */, F32 z /* = 0.0f */, F32 w /* = 0.0f */)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	//µ¥Î»»¯
	inline void Quaternion::Identity()
	{
		x = y = z = 0.0f;
		w = 1.0f;
	}

	inline Quaternion Quaternion::Conjugate()
	{
		return Quaternion(-x, -y, -z, w);
	}

	inline void Quaternion::Rotate(F32 radian, const Vector3& axis)
	{
		Quaternion rotation(radian, axis);
		*this = (*this) * rotation;
	}

	inline F32 Quaternion::LengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	inline F32& Quaternion::operator [](int32 i)
	{
		return m[i];
	}

	inline const F32& Quaternion::operator [](int32 i) const
	{
		return m[i];
	}

	inline Quaternion& Quaternion::operator =(const Quaternion& rRot)
	{
		x = rRot.x;
		y = rRot.y;
		z = rRot.z;
		w = rRot.w;

		return *this;
	}

	inline Quaternion& Quaternion::operator ~()
	{
		this->Conjugate();
		return *this;
	}

	inline Quaternion Quaternion::operator +() const
	{
		return Quaternion(-x, -y, -z, -w);
	}

	inline Quaternion Quaternion::operator -() const
	{
		return *this;
	}

	inline Quaternion&	Quaternion::operator *=(const Quaternion& rRot)
	{
		*this = *this * rRot;

		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	inline sBoolean operator ==(const Quaternion& q0, const Quaternion& q1)
	{
		return q0.x == q1.x && q0.y == q1.y && q0.z == q1.z && q0.w == q1.w;
	}

	inline sBoolean operator !=(const Quaternion& q0, const Quaternion& q1)
	{
		return q0.x != q1.x || q0.y != q1.y || q0.z != q1.z || q0.w != q1.w;
	}
}
