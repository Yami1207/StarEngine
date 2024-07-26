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
		*	������λ��
		*/
		void Normalize();

		/**
		*	������������
		*/
		F32 Length();

		/**
		*	������������
		*/
		F32 Length() const;

		/**
		*	������������ƽ��
		*/
		F32 LengthSquared();

		/**
		*	������������ƽ��
		*/
		F32 LengthSquared() const;

		Vector3	ComponentProduct(const Vector3& other) const;
		F32		DotProduct(const Vector3& other) const;
		Vector3	CrossProduct(const Vector3& other) const;
	public:

		/**
		*	���ص�λ������
		*	@param v	����
		*/
		static Vector3 Normalize(const Vector3& v);

		/**
		*	�������������
		*	@param v0	����
		*	@param v1	����
		*/
		static F32 Distance(const Vector3& v0, const Vector3& v1);

		/**
		*	�������
		*	@param v0	����
		*	@param v1	����
		*/
		static F32 Dot(const Vector3& v0, const Vector3& v1);

		/**
		*	�������
		*	@param v0	����
		*	@param v1	����
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
