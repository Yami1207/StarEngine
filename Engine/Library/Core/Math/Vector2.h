#ifndef __VECTOR2_H__
#define __VECTOR2_H__

namespace StarEngine
{
	class Vector2
	{
	public:
		Vector2();
		Vector2(F32 value);
		Vector2(F32 x, F32 y);
		Vector2(const Vector2& other);

		void	Set(F32 x, F32 y);
		void	Set(const Vector2& other);

		void	Normalize();

		F32		Length() const;
		F32		LengthSquared() const;

		F32		DotProduct(const Vector2& other) const;
		F32		CrossProduct(const Vector2& other) const;

		Vector2&	operator =(const Vector2& other);
		Vector2&	operator =(F32 fValue);

		Vector2&	operator +=(const Vector2& other);
		Vector2&	operator -=(const Vector2& other);

		Vector2&	operator *=(F32 fValue);
		Vector2&	operator /=(F32 fValue);

		F32&		operator [](int32 nIndex);
		const F32&	operator [](int32 nIndex) const;
	public:
		static Vector2	Normalize(const Vector2& other);

		/**
		*	向量点乘
		*	@param v0	向量2
		*	@param v1	向量1
		*/
		static F32 Dot(const Vector2& v0, const Vector2& v1);
	public:
		union
		{
			F32 v[2];
			struct
			{
				F32 x, y;
			};
		};
	public:
		static Vector2 zero;
		static Vector2 one;
	};

	Vector2 operator +(const Vector2& a, const Vector2& b);
	Vector2 operator -(const Vector2& a, const Vector2& b);

	Vector2 operator *(F32 fValue, const Vector2& v);
	Vector2 operator *(const Vector2& v, F32 fValue);

	Vector2 operator /(const Vector2& v, F32 fValue);

	sBoolean operator ==(const Vector2& v0, const Vector2& v1);
	sBoolean operator !=(const Vector2& v0, const Vector2& v1);

	sBoolean operator <(const Vector2& v1, const Vector2& v2);
}

#include "Vector2.inl"

#endif
