#ifndef __VECTOR3_H__
#define __VECTOR3_H__

namespace StarEngine
{
	class Vector3
	{
	public:
		Vector3();
		Vector3(F32 value);
		Vector3(F32 x, F32 y, F32 z);
		Vector3(const Vector3& other);

		Vector3&	operator =(const Vector3& other);
		Vector3&	operator =(F32 value);

		Vector3&	operator +=(const Vector3& other);
		Vector3&	operator -=(const Vector3& other);

		Vector3&	operator *=(F32 value);
		Vector3&	operator /=(F32 value);

		F32&		operator [](int32 nIndex);
		const F32&	operator [](int32 nIndex) const;
	public:
		void	Set(F32 x, F32 y, F32 z);
		void	Set(const Vector3& other);

		/**
		*	向量单位化
		*/
		void Normalize();

		/**
		*	返回向量距离
		*/
		F32 Length();

		/**
		*	返回向量距离
		*/
		F32 Length() const;

		/**
		*	返回向量距离平方
		*/
		F32 LengthSquared();

		/**
		*	返回向量距离平方
		*/
		F32 LengthSquared() const;

		Vector3	ComponentProduct(const Vector3& other) const;
		F32		DotProduct(const Vector3& other) const;
		Vector3	CrossProduct(const Vector3& other) const;
	public:

		/**
		*	返回单位化向量
		*	@param v	向量
		*/
		static Vector3 Normalize(const Vector3& v);

		/**
		*	返回向量间距离
		*	@param v0	向量
		*	@param v1	向量
		*/
		static F32 Distance(const Vector3& v0, const Vector3& v1);

		/**
		*	向量点乘
		*	@param v0	向量
		*	@param v1	向量
		*/
		static F32 Dot(const Vector3& v0, const Vector3& v1);

		/**
		*	向量叉乘
		*	@param v0	向量
		*	@param v1	向量
		*/
		static Vector3 Cross(const Vector3& v0, const Vector3& v1);
	public:
		mutable F32	x, y, z;
	protected:
		F32	pad;
	public:
		static Vector3 zero;
		static Vector3 one;

		static Vector3 right;
		static Vector3 up;
		static Vector3 forward;
	};

	Vector3 operator +(const Vector3& a, const Vector3& b);
	Vector3 operator +(F32 value, const Vector3& v);
	Vector3 operator +(const Vector3& v, F32 value);

	Vector3 operator -(const Vector3& a, const Vector3& b);
	Vector3 operator -(F32 value, const Vector3& v);
	Vector3 operator -(const Vector3& v, F32 value);
	Vector3 operator -(const Vector3& v);

	Vector3 operator *(const Vector3& a, F32 value);
	Vector3 operator *(F32 value, const Vector3& a);

	Vector3 operator /(const Vector3& a, F32 value);

	bool operator ==(const Vector3& a, const Vector3& b);
	bool operator !=(const Vector3& a, const Vector3& b);

	bool operator <(const Vector3& v1, const Vector3& v2);
}

#include "Vector3.inl"

#endif
