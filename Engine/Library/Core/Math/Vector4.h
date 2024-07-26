#ifndef __VECTOR4_H__
#define __VECTOR4_H__

namespace StarEngine
{
	class Vector3;

	class Vector4
	{
	public:
		Vector4();
		Vector4(F32 value);
		Vector4(const Vector3& v, F32 w = 0.0f);
		Vector4(F32 x, F32 y, F32 z, F32 w = 0.0f);
		Vector4(const Vector4& other);

		void		Set(F32 x, F32 y, F32 z, F32 w = 0.0f);
		void		Set(const Vector4& other);

		void		Normalize();
		void		Reciprocal();

		void		StoreXY(F32* p);
		void		StoreXYZ(F32* p);

		F32			Length() const;
		F32			LengthSquared() const;

		F32			Mag() const;
		F32			MagSquared() const;

		Vector4&	Saturate();

		F32			DotProduct(const Vector4& other) const;

		Vector4&	operator =(const Vector4& other);
		Vector4&	operator =(F32 value);

		Vector4&	operator +=(const Vector4& other);
		Vector4&	operator -=(const Vector4& other);

		Vector4&	operator *=(F32 value);
		Vector4&	operator /=(F32 value);

		F32&		operator [](int32 nIndex);
		const F32&	operator [](int32 nIndex) const;
	public:
		static Vector4	Normalize(const Vector4& other);
	public:
		union
		{
			F32 v[4];
			struct
			{
				F32	x, y, z, w;
			};
		};
	public:
		static Vector4 zero;
		static Vector4 one;
	};

	Vector4 operator +(const Vector4& a, const Vector4& b);
	Vector4 operator -(const Vector4& a, const Vector4& b);

	Vector4 operator *(const Vector4& a, float value);
	Vector4 operator *(float value, const Vector4& a);

	Vector4 operator /(const Vector4& a, F32 value);

	bool operator ==(const Vector4& v1, const Vector4& v2);
	bool operator !=(const Vector4& v1, const Vector4& v2);
	bool operator <(const Vector4& v1, const Vector4& v2);
}

#include "Vector4.inl"

#endif
