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
		 * @brief Set	设置矩阵
		 * @return
		 */
		void Set(F32 _m11, F32 _m12, F32 _m13, F32 _m14, F32 _m21, F32 _m22, F32 _m23, F32 _m24, F32 _m31, F32 _m32, F32 _m33, F32 _m34, F32 _m41, F32 _m42, F32 _m43, F32 _m44);

		/**
		 * @brief Identity	单位矩阵
		 * @return
		 */
		void Identity();

		/// <summary>
		/// 转置矩阵
		/// </summary>
		/// <returns></returns>
		Matrix44& Transpose();

		/// <summary>
		/// 逆矩阵
		/// </summary>
		void Inverse();

		//行列式
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
		 * @brief ApplyToUnitAxisVector	返回轴向量
		 * @param axis	坐标轴
		 * @return
		 */
		const Vector3& ApplyToUnitAxisVector(int32 axis) const;

		/**
		 * @brief ApplyToOrigin	返回平移向量
		 * @return
		 */
		const Vector3& ApplyToOrigin() const;

		/// <summary>
		/// 设置矩阵
		/// </summary>
		/// <param name="pos">平移</param>
		/// <param name="rot">旋转</param>
		/// <param name="scale">缩放</param>
		void SetTRS(const Vector3& pos, const Quaternion& rot, const Vector3& scale);

		/**
		 * @brief SetRow	设置行数据
		 * @param index		行索引
		 * @param v			行向量
		 * @return
		 */
		void SetRow(uint32 index, const Vector3& v);

		/**
		 * @brief SetRow	返回行数据
		 * @param index		行索引
		 * @return
		 */
		Vector3 GetRow(uint32 index) const;
	public:
		/**
		 * @brief operator =	矩阵赋值
		 * @param ohter	矩阵对象
		 * @return
		 */
		Matrix44& operator =(const Matrix44& ohter);

		/**
		 * @brief operator +=	矩阵相加
		 * @param mat	矩阵对象
		 * @return
		 */
		Matrix44& operator +=(const Matrix44& mat);

		/**
		 * @brief operator -=	矩阵相减
		 * @param mat	矩阵对象
		 * @return
		 */
		Matrix44& operator -=(const Matrix44& mat);

		/**
		 * @brief operator *=	矩阵与变量相乘
		 * @param value	变量
		 * @return
		 */
		Matrix44& operator *=(F32 value);

		/**
		 * @brief operator *=	矩阵相乘
		 * @param mat	矩阵对象
		 * @return
		 */
		Matrix44& operator *=(const Matrix44& mat);

		/**
		 * @brief operator /=	矩阵除于变量
		 * @param value	变量
		 * @return
		 */
		Matrix44& operator /=(F32 f1);

		/**
		 * @brief operator !=	判断矩阵是否相同
		 * @param mat	矩阵对象
		 * @return
		 */
		sBoolean operator ==(const Matrix44& mat);

		/**
		 * @brief operator !=	判断矩阵是否不相同
		 * @param mat	矩阵对象
		 * @return
		 */
		sBoolean operator !=(const Matrix44& mat);

		/**
		 * @brief operator []	返回行数据
		 * @param index	行索引
		 * @return
		 */
		Vector3 operator [](int32 index) const;
	public:
		/// <summary>
		/// 转置矩阵
		/// </summary>
		/// <param name="source">源矩阵</param>
		/// <returns></returns>
		static Matrix44 Transpose(const Matrix44& source);

		/// <summary>
		/// 逆矩阵
		/// </summary>
		/// <param name="source">源矩阵</param>
		/// <param name="dest">目标矩阵</param>
		/// <returns></returns>
		static Matrix44 Invert(const Matrix44& source);

		/// <summary>
		/// 返回平移矩阵
		/// </summary>
		/// <param name="x">x分量</param>
		/// <param name="y">y分量</param>
		/// <param name="z">z分量</param>
		static Matrix44 Translation(F32 x, F32 y, F32 z);

		/// <summary>
		/// 返回平移矩阵
		/// </summary>
		/// <param name="translation">平移向量</param>
		static Matrix44 Translation(const Vector3& translation);


		/// <summary>
		/// 返回旋转矩阵
		/// </summary>
		/// <param name="radian">弧度</param>
		/// <param name="axis">轴心</param>
		/// <returns></returns>
		static Matrix44 Rotate(F32 radian, const Vector3& axis);

		/// <summary>
		/// 返回旋转矩阵
		/// </summary>
		/// <param name="rot"></param>
		/// <returns></returns>
		static Matrix44 Rotate(const Quaternion& rot);

		/// <summary>
		/// 返回缩放矩阵
		/// </summary>
		/// <param name="x">x分量</param>
		/// <param name="y">y分量</param>
		/// <param name="z">z分量</param>
		static Matrix44 Scale(F32 x, F32 y, F32 z);

		/// <summary>
		/// 返回缩放矩阵
		/// </summary>
		/// <param name="scale">缩放向量</param>
		/// <returns></returns>
		static Matrix44 Scale(const Vector3& scale);

		/// <summary>
		/// 返回变换矩阵
		/// </summary>
		/// <param name="pos">平移</param>
		/// <param name="rot">旋转</param>
		/// <param name="scale">缩放</param>
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
