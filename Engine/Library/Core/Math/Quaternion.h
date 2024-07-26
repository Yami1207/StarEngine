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
		/// 单位化
		/// </summary>
		void Normalize();

		/// <summary>
		/// 四元数的逆
		/// </summary>
		void Inverse();

		/// <summary>
		/// 四元数的共軛
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
		/// 获取四元数的逆
		/// </summary>
		/// <param name="source">四元数对象</param>
		/// <returns></returns>
		static Quaternion Invert(const Quaternion& source);

		/// <summary>
		/// 欧拉角转四元数
		/// </summary>
		/// <param name="euler">欧拉角(单位:角度)</param>
		/// <returns></returns>
		static Quaternion EulerAngles(const Vector3& euler);

		/// <summary>
		/// 欧拉角转四元数
		/// </summary>
		/// <param name="pitch">俯仰角度</param>
		/// <param name="yaw">偏航角度</param>
		/// <param name="roll">翻滚角度</param>
		/// <returns></returns>
		static Quaternion EulerAngles(F32 pitch, F32 yaw, F32 roll);

		/// <summary>
		/// 四元数转欧拉角
		/// </summary>
		/// <param name="q">四元数</param>
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
	*	输出四元数标准化
	*	@param in	输入对象
	*	@param out	输出对象
	*/
	Quaternion* QuaternionNormalize(const Quaternion& in, Quaternion& out);

	Vector3* QuaternionRotatePoint(const Quaternion& q, const Vector3& v, Vector3& out);
}

#include "Quaternion.inl"

#endif
