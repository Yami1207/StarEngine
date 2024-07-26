#include "Core/BaseTypes.h"
#include "Vector3.h"

namespace StarEngine
{
	Vector3 Vector3::zero(0.0f, 0.0f, 0.0f);
	Vector3 Vector3::one(1.0f, 1.0f, 1.0f);
	Vector3 Vector3::right(1.0f, 0.0f, 0.0f);
	Vector3 Vector3::up(0.0f, 1.0f, 0.0f);
	Vector3 Vector3::forward(0.0f, 0.0f, 1.0f);

	void Vector3::Normalize()
	{
		F32 reciprocal = 1.0f / this->Length();
		x *= reciprocal;
		y *= reciprocal;
		z *= reciprocal;
	}

	F32 Vector3::Length()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	F32 Vector3::Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	Vector3 Vector3::Normalize(const Vector3& v)
	{
		F32 reciprocal = 1.0f / v.Length();
		return Vector3(v.x * reciprocal, v.y * reciprocal, v.z * reciprocal);
	}

	F32 Vector3::Distance(const Vector3& v0, const Vector3& v1)
	{
		return (v0 - v1).Length();
	}

	F32 Vector3::Dot(const Vector3& v0, const Vector3& v1)
	{
		return v0.DotProduct(v1);
	}

	Vector3 Vector3::Cross(const Vector3& v0, const Vector3& v1)
	{
		return v0.CrossProduct(v1);
	}
}
