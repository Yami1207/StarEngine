#ifndef __QUATERNION_H__
#define __QUATERNION_H__

namespace StarEngine
{
	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(F32 x, F32 y, F32 z, F32 w);
		Quaternion(F32 radian, const Vector3& axis);
		Quaternion(const Quaternion& rRot);

		void		Set(F32 x = 0.0f, F32 y = 0.0f, F32 z = 0.0f, F32 w = 0.0f);

		void		Identity();

		/// <summary>
		/// ��λ��
		/// </summary>
		void Normalize();

		/// <summary>
		/// ��Ԫ������
		/// </summary>
		void Inverse();

		/// <summary>
		/// ��Ԫ���Ĺ�ܗ
		/// </summary>
		/// <returns></returns>
		Quaternion Conjugate();

		void		Rotate(F32 radian, const Vector3& axis);

		F32			Length() const;
		F32			LengthSquared() const;

		Vector3		Right();
		Vector3		Right() const;

		Vector3		Up();
		Vector3		Up() const;

		Vector3		Forward();
		Vector3		Forward() const;

		Quaternion&	operator =(const Quaternion& rRot);
		Quaternion&	operator ~();

		Quaternion	operator +() const;
		Quaternion	operator -() const;

		Quaternion&	operator *=(const Quaternion& rRot);

		F32&		operator [](int32 i);
		const F32&	operator [](int32 i) const;
	public:
		/// <summary>
		/// ��ȡ��Ԫ������
		/// </summary>
		/// <param name="source">��Ԫ������</param>
		/// <returns></returns>
		static Quaternion Invert(const Quaternion& source);

		/// <summary>
		/// ŷ����ת��Ԫ��
		/// </summary>
		/// <param name="euler">ŷ����(��λ:�Ƕ�)</param>
		/// <returns></returns>
		static Quaternion EulerAngles(const Vector3& euler);

		/// <summary>
		/// ŷ����ת��Ԫ��
		/// </summary>
		/// <param name="pitch">�����Ƕ�</param>
		/// <param name="yaw">ƫ���Ƕ�</param>
		/// <param name="roll">�����Ƕ�</param>
		/// <returns></returns>
		static Quaternion EulerAngles(F32 pitch, F32 yaw, F32 roll);

		/// <summary>
		/// ��Ԫ��תŷ����
		/// </summary>
		/// <param name="q">��Ԫ��</param>
		/// <returns></returns>
		static Vector3 ToEulerAngles(const Quaternion& q);
	public:
		union
		{
			F32 m[4];
			struct
			{
				F32 x, y, z, w;
			};
			struct
			{
				F32 v[3];
				F32	w;
			};
		};
	};

	sBoolean operator ==(const Quaternion& q0, const Quaternion& q1);
	sBoolean operator !=(const Quaternion& q0, const Quaternion& q1);

	Quaternion operator *(const Quaternion& q1, const Quaternion& q2);
	Quaternion operator *(const Quaternion& q, const Vector3& v);
	Vector3 operator *(const Vector3& v, const Quaternion& q);

	Quaternion* QuaternionMultiplyQuaternion(const Quaternion& q1, const Quaternion& q2, Quaternion& out);
	Quaternion* QuaternionMultiplyVertor(const Quaternion& q, const Vector3& v, Quaternion& out);
	Vector3* VertorMultiplyQuaternion(const Quaternion& q, const Vector3& v, Vector3& out);

	void QuaternionComputeW(Quaternion& q);

	/**
	*	�����Ԫ����׼��
	*	@param in	�������
	*	@param out	�������
	*/
	Quaternion* QuaternionNormalize(const Quaternion& in, Quaternion& out);

	Vector3* QuaternionRotatePoint(const Quaternion& q, const Vector3& v, Vector3& out);
}

#include "Quaternion.inl"

#endif
