#ifndef __MATRIX44_H__
#define __MATRIX44_H__

namespace StarEngine
{
	class Matrix44
	{
	public:
		Matrix44();
		Matrix44(F32 _m11, F32 _m12, F32 _m13, F32 _m14, F32 _m21, F32 _m22, F32 _m23, F32 _m24, F32 _m31, F32 _m32, F32 _m33, F32 _m34, F32 _m41, F32 _m42, F32 _m43, F32 _m44);
		Matrix44(const Matrix44& mat);

		/**
		 * @brief Set	���þ���
		 * @return
		 */
		void Set(F32 _m11, F32 _m12, F32 _m13, F32 _m14, F32 _m21, F32 _m22, F32 _m23, F32 _m24, F32 _m31, F32 _m32, F32 _m33, F32 _m34, F32 _m41, F32 _m42, F32 _m43, F32 _m44);

		/**
		 * @brief Identity	��λ����
		 * @return
		 */
		void Identity();

		/// <summary>
		/// ת�þ���
		/// </summary>
		/// <returns></returns>
		Matrix44& Transpose();

		/// <summary>
		/// �����
		/// </summary>
		void Inverse();

		//����ʽ
		F32				Det();

		Vector3			MultiplyPoint(const Vector3& v);
		Vector3			MultiplyPoint(const Vector3& v) const;

		Vector3			MultiplyVector(const Vector3& v);
		Vector3			MultiplyVector(const Vector3& v) const;

		Vector3			PointMultiply(const Vector3& v);
		Vector3			PointMultiply(const Vector3& v) const;

		Vector3			VectorMultiply(const Vector3& v);
		Vector3			VectorMultiply(const Vector3& v) const;

		/**
		 * @brief ApplyToUnitAxisVector	����������
		 * @param axis	������
		 * @return
		 */
		const Vector3& ApplyToUnitAxisVector(int32 axis) const;

		/**
		 * @brief ApplyToOrigin	����ƽ������
		 * @return
		 */
		const Vector3& ApplyToOrigin() const;

		/// <summary>
		/// ���þ���
		/// </summary>
		/// <param name="pos">ƽ��</param>
		/// <param name="rot">��ת</param>
		/// <param name="scale">����</param>
		void SetTRS(const Vector3& pos, const Quaternion& rot, const Vector3& scale);

		/**
		 * @brief SetRow	����������
		 * @param index		������
		 * @param v			������
		 * @return
		 */
		void SetRow(uint32 index, const Vector3& v);

		/**
		 * @brief SetRow	����������
		 * @param index		������
		 * @return
		 */
		Vector3 GetRow(uint32 index) const;
	public:
		/**
		 * @brief operator =	����ֵ
		 * @param ohter	�������
		 * @return
		 */
		Matrix44& operator =(const Matrix44& ohter);

		/**
		 * @brief operator +=	�������
		 * @param mat	�������
		 * @return
		 */
		Matrix44& operator +=(const Matrix44& mat);

		/**
		 * @brief operator -=	�������
		 * @param mat	�������
		 * @return
		 */
		Matrix44& operator -=(const Matrix44& mat);

		/**
		 * @brief operator *=	������������
		 * @param value	����
		 * @return
		 */
		Matrix44& operator *=(F32 value);

		/**
		 * @brief operator *=	�������
		 * @param mat	�������
		 * @return
		 */
		Matrix44& operator *=(const Matrix44& mat);

		/**
		 * @brief operator /=	������ڱ���
		 * @param value	����
		 * @return
		 */
		Matrix44& operator /=(F32 f1);

		/**
		 * @brief operator !=	�жϾ����Ƿ���ͬ
		 * @param mat	�������
		 * @return
		 */
		sBoolean operator ==(const Matrix44& mat);

		/**
		 * @brief operator !=	�жϾ����Ƿ���ͬ
		 * @param mat	�������
		 * @return
		 */
		sBoolean operator !=(const Matrix44& mat);

		/**
		 * @brief operator []	����������
		 * @param index	������
		 * @return
		 */
		Vector3 operator [](int32 index) const;
	public:
		/// <summary>
		/// ת�þ���
		/// </summary>
		/// <param name="source">Դ����</param>
		/// <returns></returns>
		static Matrix44 Transpose(const Matrix44& source);

		/// <summary>
		/// �����
		/// </summary>
		/// <param name="source">Դ����</param>
		/// <param name="dest">Ŀ�����</param>
		/// <returns></returns>
		static Matrix44 Invert(const Matrix44& source);

		/// <summary>
		/// ����ƽ�ƾ���
		/// </summary>
		/// <param name="x">x����</param>
		/// <param name="y">y����</param>
		/// <param name="z">z����</param>
		static Matrix44 Translation(F32 x, F32 y, F32 z);

		/// <summary>
		/// ����ƽ�ƾ���
		/// </summary>
		/// <param name="translation">ƽ������</param>
		static Matrix44 Translation(const Vector3& translation);


		/// <summary>
		/// ������ת����
		/// </summary>
		/// <param name="radian">����</param>
		/// <param name="axis">����</param>
		/// <returns></returns>
		static Matrix44 Rotate(F32 radian, const Vector3& axis);

		/// <summary>
		/// ������ת����
		/// </summary>
		/// <param name="rot"></param>
		/// <returns></returns>
		static Matrix44 Rotate(const Quaternion& rot);

		/// <summary>
		/// �������ž���
		/// </summary>
		/// <param name="x">x����</param>
		/// <param name="y">y����</param>
		/// <param name="z">z����</param>
		static Matrix44 Scale(F32 x, F32 y, F32 z);

		/// <summary>
		/// �������ž���
		/// </summary>
		/// <param name="scale">��������</param>
		/// <returns></returns>
		static Matrix44 Scale(const Vector3& scale);

		/// <summary>
		/// ���ر任����
		/// </summary>
		/// <param name="pos">ƽ��</param>
		/// <param name="rot">��ת</param>
		/// <param name="scale">����</param>
		static Matrix44 TRS(const Vector3& pos, const Quaternion& rot, const Vector3& scale);
	public:
		union
		{
			F32 m[4][4];
			struct
			{
				F32	m11, m12, m13, m14;
				F32 m21, m22, m23, m24;
				F32 m31, m32, m33, m34;
				F32 m41, m42, m43, m44;
			};
		};
	public:
		static Matrix44 identity;
	};

	Matrix44 operator +(const Matrix44& mat1, const Matrix44& mat2);
	Matrix44 operator -(const Matrix44& mat1, const Matrix44& mat2);
	Matrix44 operator *(const Matrix44& mat1, const Matrix44& mat2);
}

#include "Matrix44.inl"

#endif
