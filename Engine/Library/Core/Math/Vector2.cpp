#include "EngineLibrary.h"

namespace StarEngine
{
	Vector2 Vector2::zero(0.0f, 0.0f);
	Vector2 Vector2::one(1.0f, 1.0f);

	void Vector2::Normalize()
	{
		F32 reciprocal = 1.0f / Length();
		x *= reciprocal;
		y *= reciprocal;
	}

	F32 Vector2::Length() const
	{
		return sqrtf(x * x + y * y);
	}

	F32 Vector2::LengthSquared() const
	{
		return DotProduct(*this);
	}

	Vector2 Vector2::Normalize(const Vector2& other)
	{
		F32 reciprocal = 1.0f / other.Length();
		return Vector2(other.x * reciprocal, other.y * reciprocal);
	}

	F32 Vector2::Dot(const Vector2& v0, const Vector2& v1)
	{
		return v0.x * v1.x + v0.y * v1.y;
	}
}
