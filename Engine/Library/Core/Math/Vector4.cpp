#include "Core/BaseTypes.h"
#include "Vector3.h"
#include "Vector4.h"

namespace StarEngine
{
	Vector4 Vector4::zero(0.0f, 0.0f, 0.0f, 0.0f);
	Vector4 Vector4::one(1.0f, 1.0f, 1.0f, 1.0f);

	Vector4::Vector4(const Vector3& v, F32 _w /* = 0.0f */) : x(v.x), y(v.y), z(v.z), w(_w)
	{
	}

	void Vector4::Normalize()
	{
		F32 reciprocal = 1.0f / Length();
		x = x * reciprocal;
		y = y * reciprocal;
		z = z * reciprocal;
	}

	void Vector4::Reciprocal()
	{
		x = 1.0f / x;
		y = 1.0f / y;
		z = 1.0f / z;
		w = 1.0f / w;
	}

	F32 Vector4::Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	F32 Vector4::LengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	F32 Vector4::Mag() const
	{
		return Length();
	}

	F32 Vector4::MagSquared() const
	{
		return LengthSquared();
	}

	Vector4& Vector4::Saturate()
	{
		x = MathLib::Clamp(x, 0.0f, 1.0f);
		y = MathLib::Clamp(y, 0.0f, 1.0f);
		z = MathLib::Clamp(z, 0.0f, 1.0f);
		w = MathLib::Clamp(w, 0.0f, 1.0f);
		return *this;
	}

	Vector4 Vector4::Normalize(const Vector4& other)
	{
		F32 fReciprocal = 1.0f / other.Length();
		return Vector4(other.x * fReciprocal,other.y * fReciprocal,other.z * fReciprocal,other.w * fReciprocal);
	}
}
