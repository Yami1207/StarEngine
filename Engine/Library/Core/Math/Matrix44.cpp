#include "EngineLibrary.h"

namespace StarEngine
{
	Matrix44 Matrix44::identity;

	Matrix44::Matrix44()
	{
		m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}

	Matrix44::Matrix44(F32 _m11, F32 _m12, F32 _m13, F32 _m14, F32 _m21, F32 _m22, F32 _m23, F32 _m24, F32 _m31, F32 _m32, F32 _m33, F32 _m34, F32 _m41, F32 _m42, F32 _m43, F32 _m44)
	{
		m[0][0] = _m11;	m[0][1] = _m12;	m[0][2] = _m13;	m[0][3] = _m14;
		m[1][0] = _m21; m[1][1] = _m22; m[1][2] = _m23; m[1][3] = _m24;
		m[2][0] = _m31; m[2][1] = _m32; m[2][2] = _m33; m[2][3] = _m34;
		m[3][0] = _m41; m[3][1] = _m42; m[3][2] = _m43; m[3][3] = _m44;
	}

	Matrix44::Matrix44(const Matrix44& mat)
	{
		m[0][0] = mat.m[0][0];	m[0][1] = mat.m[0][1];	m[0][2] = mat.m[0][2];	m[0][3] = mat.m[0][3];
		m[1][0] = mat.m[1][0];	m[1][1] = mat.m[1][1];	m[1][2] = mat.m[1][2];	m[1][3] = mat.m[1][3];
		m[2][0] = mat.m[2][0];	m[2][1] = mat.m[2][1];	m[2][2] = mat.m[2][2];	m[2][3] = mat.m[2][3];
		m[3][0] = mat.m[3][0];	m[3][1] = mat.m[3][1];	m[3][2] = mat.m[3][2];	m[3][3] = mat.m[3][3];
	}

	void Matrix44::Set(F32 _m11, F32 _m12, F32 _m13, F32 _m14, F32 _m21, F32 _m22, F32 _m23, F32 _m24, F32 _m31, F32 _m32, F32 _m33, F32 _m34, F32 _m41, F32 _m42, F32 _m43, F32 _m44)
	{
		m[0][0] = _m11;	m[0][1] = _m12;	m[0][2] = _m13;	m[0][3] = _m14;
		m[1][0] = _m21; m[1][1] = _m22; m[1][2] = _m23; m[1][3] = _m24;
		m[2][0] = _m31; m[2][1] = _m32; m[2][2] = _m33; m[2][3] = _m34;
		m[3][0] = _m41; m[3][1] = _m42; m[3][2] = _m43; m[3][3] = _m44;
	}

	void Matrix44::Identity()
	{
		m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}

	Matrix44& Matrix44::Transpose()
	{
		F32 temp;
		MathLib::Swap(m[0][1], m[1][0], temp);
		MathLib::Swap(m[0][2], m[2][0], temp);
		MathLib::Swap(m[0][3], m[3][0], temp);
		MathLib::Swap(m[1][2], m[2][1], temp);
		MathLib::Swap(m[1][3], m[3][1], temp);
		MathLib::Swap(m[2][3], m[3][2], temp);
		return *this;
	}

	void Matrix44::Inverse()
	{
		int32 iRow, i, j, iTemp, iTest;
		F32 mul, fTest, fLargest;
		F32 mat[4][8];
		int32 rowMap[4], iLargest;
		F32 *pIn, *pOut, *pRow, *pScaleRow;

		for (i = 0; i < 4; i++)
		{
			pIn = m[i];
			pOut = mat[i];

			for (j = 0; j < 4; j++)
			{
				pOut[j] = pIn[j];
			}

			pOut[4] = 0.0f;
			pOut[5] = 0.0f;
			pOut[6] = 0.0f;
			pOut[7] = 0.0f;
			pOut[i + 4] = 1.0f;

			rowMap[i] = i;
		}

		for (iRow = 0; iRow < 4; iRow++)
		{
			//Find the row with the largest element in this column.
			fLargest = 0.001f;
			iLargest = -1;
			for (iTest = iRow; iTest < 4; iTest++)
			{
				fTest = (F32)fabs(mat[rowMap[iTest]][iRow]);
				if (fTest > fLargest)
				{
					iLargest = iTest;
					fLargest = fTest;
				}
			}

			//They're all too small.. sorry.
			if (iLargest == -1)
				return;

			//Swap the rows.
			iTemp = rowMap[iLargest];
			rowMap[iLargest] = rowMap[iRow];
			rowMap[iRow] = iTemp;

			pRow = mat[rowMap[iRow]];

			//Divide this row by the element.
			mul = 1.0f / pRow[iRow];
			for (j = 0; j < 8; j++)
				pRow[j] *= mul;

			//! Preserve accuracy...
			pRow[iRow] = 1.0f;

			//Eliminate this element from the other rows using operation 2.
			for (i = 0; i < 4; i++)
			{
				if (i == iRow)
					continue;

				pScaleRow = mat[rowMap[i]];

				//Multiply this row by -(iRow*the element).
				mul = -pScaleRow[iRow];
				for (j = 0; j < 8; j++)
					pScaleRow[j] += pRow[j] * mul;

				pScaleRow[iRow] = 0.0f; //! Preserve accuracy...
			}
		}

		//The inverse is on the right side of AX now (the identity is on the left).
		for (i = 0; i < 4; i++)
		{
			pIn = mat[rowMap[i]] + 4;
			pOut = m[i];

			for (j = 0; j < 4; j++)
			{
				pOut[j] = pIn[j];
			}
		}
	}

	F32 Matrix44::Det()
	{
		F32 f1 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
		F32 f2 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
		F32 f3 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
		F32 f4 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
		F32 f5 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
		F32 f6 = m[2][2] * m[3][3] - m[2][3] * m[3][2];

		F32 t11 = m[1][1] * f6 - m[1][2] * f5 + m[1][3] * f4;
		F32 t12 = m[1][0] * f6 - m[1][2] * f3 + m[1][3] * f2;
		F32 t13 = m[1][0] * f5 - m[1][1] * f3 + m[1][3] * f1;
		F32 t14 = m[1][0] * f4 - m[1][1] * f2 + m[1][2] * f1;

		return m[0][0] * t11 - m[0][1] * t12 + m[0][2] * t13 - m[0][3] * t14;
	}

	Vector3 Matrix44::MultiplyPoint(const Vector3& v)
	{
		Vector3 out;
		F32 w = this->m[3][0] * v.x + this->m[3][1] * v.y + this->m[3][2] * v.z + this->m[3][3];
		if(w == 0.0f)
		{
			out.x = out.y = out.z = 0.0f;
		}
		else if(w == 1.0f)
		{
			out.x = this->m[0][0] * v.x + this->m[0][1] * v.y + this->m[0][2] * v.z + this->m[0][3];
			out.y = this->m[1][0] * v.x + this->m[1][1] * v.y + this->m[1][2] * v.z + this->m[1][3];
			out.z = this->m[2][0] * v.x + this->m[2][1] * v.y + this->m[2][2] * v.z + this->m[2][3];
		}
		else
		{
			F32 one_over_w = 1.0f / w;
			out.x = (this->m[0][0] * v.x + this->m[0][1] * v.y + this->m[0][2] * v.z + this->m[0][3]) * one_over_w;
			out.y = (this->m[1][0] * v.x + this->m[1][1] * v.y + this->m[1][2] * v.z + this->m[1][3]) * one_over_w;
			out.z = (this->m[2][0] * v.x + this->m[2][1] * v.y + this->m[2][2] * v.z + this->m[2][3]) * one_over_w;
		}
		return out;
	}

	Vector3 Matrix44::MultiplyPoint(const Vector3& v) const
	{
		Vector3 out;
		F32 w = this->m[3][0] * v.x + this->m[3][1] * v.y + this->m[3][2] * v.z + this->m[3][3];
		if(w == 0.0f)
		{
			out.x = out.y = out.z = 0.0f;
		}
		else if(w == 1.0f)
		{
			out.x = this->m[0][0] * v.x + this->m[0][1] * v.y + this->m[0][2] * v.z + this->m[0][3];
			out.y = this->m[1][0] * v.x + this->m[1][1] * v.y + this->m[1][2] * v.z + this->m[1][3];
			out.z = this->m[2][0] * v.x + this->m[2][1] * v.y + this->m[2][2] * v.z + this->m[2][3];
		}
		else
		{
			F32 one_over_w = 1.0f / w;
			out.x = (this->m[0][0] * v.x + this->m[0][1] * v.y + this->m[0][2] * v.z + this->m[0][3]) * one_over_w;
			out.y = (this->m[1][0] * v.x + this->m[1][1] * v.y + this->m[1][2] * v.z + this->m[1][3]) * one_over_w;
			out.z = (this->m[2][0] * v.x + this->m[2][1] * v.y + this->m[2][2] * v.z + this->m[2][3]) * one_over_w;
		}
		return out;
	}

	Vector3 Matrix44::MultiplyVector(const Vector3& v)
	{
		Vector3 out;
		out.x = this->m[0][0] * v.x + this->m[0][1] * v.y + this->m[0][2] * v.z;
		out.y = this->m[1][0] * v.x + this->m[1][1] * v.y + this->m[1][2] * v.z;
		out.z = this->m[2][0] * v.x + this->m[2][1] * v.y + this->m[2][2] * v.z;
		return out;
	}

	Vector3 Matrix44::MultiplyVector(const Vector3& v) const
	{
		Vector3 out;
		out.x = this->m[0][0] * v.x + this->m[0][1] * v.y + this->m[0][2] * v.z;
		out.y = this->m[1][0] * v.x + this->m[1][1] * v.y + this->m[1][2] * v.z;
		out.z = this->m[2][0] * v.x + this->m[2][1] * v.y + this->m[2][2] * v.z;
		return out;
	}

	Vector3 Matrix44::PointMultiply(const Vector3& v)
	{
		Vector3 out;
		F32 w = this->m[0][3] * v.x + this->m[1][3] * v.y + this->m[2][3] * v.z + this->m[3][3];
		if (w == 0.0f)
		{
			out.x = out.y = out.z = 0.0f;
		}
		else if (w == 1.0f)
		{
			out.x = this->m[0][0] * v.x + this->m[1][0] * v.y + this->m[2][0] * v.z + this->m[3][0];
			out.y = this->m[0][1] * v.x + this->m[1][1] * v.y + this->m[2][1] * v.z + this->m[3][1];
			out.z = this->m[0][2] * v.x + this->m[1][2] * v.y + this->m[2][2] * v.z + this->m[3][2];
		}
		else
		{
			F32 one_over_w = 1.0f / w;
			out.x = (this->m[0][0] * v.x + this->m[1][0] * v.y + this->m[2][0] * v.z + this->m[3][0]) * one_over_w;
			out.y = (this->m[0][1] * v.x + this->m[1][1] * v.y + this->m[2][1] * v.z + this->m[3][1]) * one_over_w;
			out.z = (this->m[0][2] * v.x + this->m[1][2] * v.y + this->m[2][2] * v.z + this->m[3][2]) * one_over_w;
		}
		return out;
	}

	Vector3 Matrix44::PointMultiply(const Vector3& v) const
	{
		Vector3 out;
		F32 w = this->m[0][3] * v.x + this->m[1][3] * v.y + this->m[2][3] * v.z + this->m[3][3];
		if (w == 0.0f)
		{
			out.x = out.y = out.z = 0.0f;
		}
		else if (w == 1.0f)
		{
			out.x = this->m[0][0] * v.x + this->m[1][0] * v.y + this->m[2][0] * v.z + this->m[3][0];
			out.y = this->m[0][1] * v.x + this->m[1][1] * v.y + this->m[2][1] * v.z + this->m[3][1];
			out.z = this->m[0][2] * v.x + this->m[1][2] * v.y + this->m[2][2] * v.z + this->m[3][2];
		}
		else
		{
			F32 one_over_w = 1.0f / w;
			out.x = (this->m[0][0] * v.x + this->m[1][0] * v.y + this->m[2][0] * v.z + this->m[3][0]) * one_over_w;
			out.y = (this->m[0][1] * v.x + this->m[1][1] * v.y + this->m[2][1] * v.z + this->m[3][1]) * one_over_w;
			out.z = (this->m[0][2] * v.x + this->m[1][2] * v.y + this->m[2][2] * v.z + this->m[3][2]) * one_over_w;
		}
		return out;
	}

	Vector3 Matrix44::VectorMultiply(const Vector3& v)
	{
		Vector3 out;
		out.x = this->m[0][0] * v.x + this->m[1][0] * v.y + this->m[2][0] * v.z;
		out.y = this->m[0][1] * v.x + this->m[1][1] * v.y + this->m[2][1] * v.z;
		out.z = this->m[0][2] * v.x + this->m[1][2] * v.y + this->m[2][2] * v.z;
		return out;
	}

	Vector3 Matrix44::VectorMultiply(const Vector3& v) const
	{
		Vector3 out;
		out.x = this->m[0][0] * v.x + this->m[1][0] * v.y + this->m[2][0] * v.z;
		out.y = this->m[0][1] * v.x + this->m[1][1] * v.y + this->m[2][1] * v.z;
		out.z = this->m[0][2] * v.x + this->m[1][2] * v.y + this->m[2][2] * v.z;
		return out;
	}

	const Vector3& Matrix44::ApplyToUnitAxisVector(int32 axis) const
	{
		return *reinterpret_cast<const Vector3*>(m[axis]);
	}

	const Vector3& Matrix44::ApplyToOrigin() const
	{
		return *reinterpret_cast<const Vector3*>(m[3]);
	}

	void Matrix44::SetTRS(const Vector3& pos, const Quaternion& rot, const Vector3& scale)
	{
		*this = Matrix44::TRS(pos, rot, scale);
	}

	void Matrix44::SetRow(uint32 index, const Vector3& value)
	{
		m[index][0] = value.x;
		m[index][1] = value.y;
		m[index][2] = value.z;
	}

	Vector3 Matrix44::GetRow(uint32 index) const
	{
		return Vector3(m[index][0], m[index][1], m[index][2]);
	}

	Matrix44& Matrix44::operator =(const Matrix44& ohter)
	{
		m[0][0] = ohter.m[0][0];	m[0][1] = ohter.m[0][1];	m[0][2] = ohter.m[0][2];	m[0][3] = ohter.m[0][3];
		m[1][0] = ohter.m[1][0];	m[1][1] = ohter.m[1][1];	m[1][2] = ohter.m[1][2];	m[1][3] = ohter.m[1][3];
		m[2][0] = ohter.m[2][0];	m[2][1] = ohter.m[2][1];	m[2][2] = ohter.m[2][2];	m[2][3] = ohter.m[2][3];
		m[3][0] = ohter.m[3][0];	m[3][1] = ohter.m[3][1];	m[3][2] = ohter.m[3][2];	m[3][3] = ohter.m[3][3];
		return *this;
	}

	Matrix44& Matrix44::operator +=(const Matrix44& mat)
	{
		m[0][0] += mat.m[0][0];	m[0][1] += mat.m[0][1];	m[0][2] += mat.m[0][2];	m[0][3] += mat.m[0][3];
		m[1][0] += mat.m[1][0];	m[1][1] += mat.m[1][1];	m[1][2] += mat.m[1][2];	m[1][3] += mat.m[1][3];
		m[2][0] += mat.m[2][0];	m[2][1] += mat.m[2][1];	m[2][2] += mat.m[2][2];	m[2][3] += mat.m[2][3];
		m[3][0] += mat.m[3][0];	m[3][1] += mat.m[3][1];	m[3][2] += mat.m[3][2];	m[3][3] += mat.m[3][3];
		return *this;
	}

	Matrix44& Matrix44::operator -=(const Matrix44& mat)
	{
		m[0][0] -= mat.m[0][0];	m[0][1] -= mat.m[0][1];	m[0][2] -= mat.m[0][2];	m[0][3] -= mat.m[0][3];
		m[1][0] -= mat.m[1][0];	m[1][1] -= mat.m[1][1];	m[1][2] -= mat.m[1][2];	m[1][3] -= mat.m[1][3];
		m[2][0] -= mat.m[2][0];	m[2][1] -= mat.m[2][1];	m[2][2] -= mat.m[2][2];	m[2][3] -= mat.m[2][3];
		m[3][0] -= mat.m[3][0];	m[3][1] -= mat.m[3][1];	m[3][2] -= mat.m[3][2];	m[3][3] -= mat.m[3][3];
		return *this;
	}

	Matrix44& Matrix44::operator *=(F32 f1)
	{
		m[0][0] *= f1;	m[0][1] *= f1;	m[0][2] *= f1;	m[0][3] *= f1;
		m[1][0] *= f1;	m[1][1] *= f1;	m[1][2] *= f1;	m[1][3] *= f1;
		m[2][0] *= f1;	m[2][1] *= f1;	m[2][2] *= f1;	m[2][3] *= f1;
		m[3][0] *= f1;	m[3][1] *= f1;	m[3][2] *= f1;	m[3][3] *= f1;
		return *this;
	}

	Matrix44& Matrix44::operator *=(const Matrix44& mat)
	{
		m[0][0] = m[0][0] * mat.m[0][0] + m[0][1] * mat.m[1][0] + m[0][2] * mat.m[2][0] + m[0][3] * mat.m[3][0];
		m[0][1] = m[0][0] * mat.m[0][1] + m[0][1] * mat.m[1][1] + m[0][2] * mat.m[2][1] + m[0][3] * mat.m[3][1];
		m[0][2] = m[0][0] * mat.m[0][2] + m[0][1] * mat.m[1][2] + m[0][2] * mat.m[2][2] + m[0][3] * mat.m[3][2];
		m[0][3] = m[0][0] * mat.m[0][3] + m[0][1] * mat.m[1][3] + m[0][2] * mat.m[2][3] + m[0][3] * mat.m[3][3];

		m[1][0] = m[1][0] * mat.m[0][0] + m[1][1] * mat.m[1][0] + m[1][2] * mat.m[2][0] + m[1][3] * mat.m[3][0];
		m[1][1] = m[1][0] * mat.m[0][1] + m[1][1] * mat.m[1][1] + m[1][2] * mat.m[2][1] + m[1][3] * mat.m[3][1];
		m[1][2] = m[1][0] * mat.m[0][2] + m[1][1] * mat.m[1][2] + m[1][2] * mat.m[2][2] + m[1][3] * mat.m[3][2];
		m[1][3] = m[1][0] * mat.m[0][3] + m[1][1] * mat.m[1][3] + m[1][2] * mat.m[2][3] + m[1][3] * mat.m[3][3];

		m[2][0] = m[2][0] * mat.m[0][0] + m[2][1] * mat.m[1][0] + m[2][2] * mat.m[2][0] + m[2][3] * mat.m[3][0];
		m[2][1] = m[2][0] * mat.m[0][1] + m[2][1] * mat.m[1][1] + m[2][2] * mat.m[2][1] + m[2][3] * mat.m[3][1];
		m[2][2] = m[2][0] * mat.m[0][2] + m[2][1] * mat.m[1][2] + m[2][2] * mat.m[2][2] + m[2][3] * mat.m[3][2];
		m[2][3] = m[2][0] * mat.m[0][3] + m[2][1] * mat.m[1][3] + m[2][2] * mat.m[2][3] + m[2][3] * mat.m[3][3];

		m[3][0] = m[3][0] * mat.m[0][0] + m[3][1] * mat.m[1][0] + m[3][2] * mat.m[2][0] + m[3][3] * mat.m[3][0];
		m[3][1] = m[3][0] * mat.m[0][1] + m[3][1] * mat.m[1][1] + m[3][2] * mat.m[2][1] + m[3][3] * mat.m[3][1];
		m[3][2] = m[3][0] * mat.m[0][2] + m[3][1] * mat.m[1][2] + m[3][2] * mat.m[2][2] + m[3][3] * mat.m[3][2];
		m[3][3] = m[3][0] * mat.m[0][3] + m[3][1] * mat.m[1][3] + m[3][2] * mat.m[2][3] + m[3][3] * mat.m[3][3];

		return *this;
	}

	Matrix44& Matrix44::operator /=(F32 f1)
	{
		ASSERT_DEBUG(fabs(f1) < EPSILON_E5);

		f1 = 1.0f / f1;
		m[0][0] *= f1;	m[0][1] *= f1;	m[0][2] *= f1;	m[0][3] *= f1;
		m[1][0] *= f1;	m[1][1] *= f1;	m[1][2] *= f1;	m[1][3] *= f1;
		m[2][0] *= f1;	m[2][1] *= f1;	m[2][2] *= f1;	m[2][3] *= f1;
		m[3][0] *= f1;	m[3][1] *= f1;	m[3][2] *= f1;	m[3][3] *= f1;
		return *this;
	}

	sBoolean Matrix44::operator ==(const Matrix44& mat)
	{
		for (int col = 0; col < 4; ++col)
			for (int row = 0; row < 4; ++row)
				if (m[col][row] != mat.m[col][row])
					return sFalse;
		return sTrue;
	}

	sBoolean Matrix44::operator !=(const Matrix44& mat)
	{
		for (int col = 0; col < 4; ++col)
			for (int row = 0; row < 4; ++row)
				if (m[col][row] != mat.m[col][row])
					return sTrue;
		return sFalse;
	}

	Vector3 Matrix44::operator [](int32 index) const
	{
		return Vector3(m[index][0], m[index][1], m[index][2]);
	}

	Matrix44 Matrix44::Transpose(const Matrix44& source)
	{
		Matrix44 mat;
		mat.m[0][0] = source.m[0][0];	mat.m[0][1] = source.m[1][0];	mat.m[0][2] = source.m[2][0];	mat.m[0][3] = source.m[3][0];
		mat.m[1][0] = source.m[0][1];	mat.m[1][1] = source.m[1][1];	mat.m[1][2] = source.m[2][1];	mat.m[1][3] = source.m[3][1];
		mat.m[2][0] = source.m[0][2];	mat.m[2][1] = source.m[1][2];	mat.m[2][2] = source.m[2][2];	mat.m[2][3] = source.m[3][2];
		mat.m[3][0] = source.m[0][3];	mat.m[3][1] = source.m[1][3];	mat.m[3][2] = source.m[2][3];	mat.m[3][3] = source.m[3][3];
		return mat;
	}

	Matrix44 Matrix44::Invert(const Matrix44& source)
	{
		Matrix44 mat = source;
		mat.Inverse();
		return mat;
	}

	Matrix44 Matrix44::Translation(F32 x, F32 y, F32 z)
	{
		Matrix44 mat;
		mat.m41 = x;
		mat.m42 = y;
		mat.m43 = z;
		return mat;
	}

	Matrix44 Matrix44::Rotate(F32 radian, const Vector3& axis)
	{
		F32 s, c, t;
		F32 tx, ty, tz;
		F32 sx, sy, sz;

		s = sinf(radian);
		c = cosf(radian);
		t = 1.f - c;

		tx = t * axis.x;
		ty = t * axis.y;
		tz = t * axis.z;

		sx = s * axis.x;
		sy = s * axis.y;
		sz = s * axis.z;

		Matrix44 mat;
		mat.m[0][0] = tx * axis.x + c;
		mat.m[1][0] = tx * axis.y + sz;
		mat.m[2][0] = tx * axis.z - sy;

		mat.m[0][1] = tx * axis.y - sz;
		mat.m[1][1] = ty * axis.y + c;
		mat.m[2][1] = ty * axis.z + sx;

		mat.m[0][2] = tx * axis.z + sy;
		mat.m[1][2] = ty * axis.z - sx;
		mat.m[2][2] = tz * axis.z + c;

		return mat;
	}

	Matrix44 Matrix44::Rotate(const Quaternion& rot)
	{
		Vector3 right = rot.Right(), up = rot.Up(), forward = rot.Forward();

		Matrix44 mat;
		mat.m11 = right.x;		mat.m12 = right.y;		mat.m13 = right.z;
		mat.m21 = up.x;			mat.m22 = up.y;			mat.m23 = up.z;
		mat.m31 = forward.x;	mat.m32 = forward.y;	mat.m33 = forward.z;
		return mat;
	}

	Matrix44 Matrix44::Scale(F32 x, F32 y, F32 z)
	{
		Matrix44 mat;
		mat.m11 = x;
		mat.m22 = y;
		mat.m33 = z;
		return mat;
	}

	Matrix44 Matrix44::TRS(const Vector3& pos, const Quaternion& rot, const Vector3& scale)
	{
		Matrix44 t = Matrix44::Translation(pos);
		Matrix44 r = Matrix44::Rotate(rot);
		Matrix44 s = Matrix44::Scale(scale);
		return t * r * s;
	}

	//////////////////////////////////////////////////////////////////////////
	Matrix44 operator +(const Matrix44& mat1,const Matrix44& mat2)
	{
		Matrix44 matOut;
		matOut.m[0][0] = mat1.m[0][0] + mat2.m[0][0];	matOut.m[0][1] = mat1.m[0][1] + mat2.m[0][1];
		matOut.m[0][2] = mat1.m[0][2] + mat2.m[0][2];	matOut.m[0][3] = mat1.m[0][3] + mat2.m[0][3];

		matOut.m[1][0] = mat1.m[1][0] + mat2.m[1][0];	matOut.m[1][1] = mat1.m[1][1] + mat2.m[1][1];
		matOut.m[1][2] = mat1.m[1][2] + mat2.m[1][2];	matOut.m[1][3] = mat1.m[1][3] + mat2.m[1][3];

		matOut.m[2][0] = mat1.m[2][0] + mat2.m[2][0];	matOut.m[2][1] = mat1.m[2][1] + mat2.m[2][1];
		matOut.m[2][2] = mat1.m[2][2] + mat2.m[2][2];	matOut.m[2][3] = mat1.m[2][3] + mat2.m[2][3];

		matOut.m[3][0] = mat1.m[3][0] + mat2.m[3][0];	matOut.m[3][1] = mat1.m[3][1] + mat2.m[3][1];
		matOut.m[3][2] = mat1.m[3][2] + mat2.m[3][2];	matOut.m[3][3] = mat1.m[3][3] + mat2.m[3][3];

		return matOut;
	}

	Matrix44 operator -(const Matrix44& mat1,const Matrix44& mat2)
	{
		Matrix44 matOut;
		matOut.m[0][0] = mat1.m[0][0] - mat2.m[0][0];	matOut.m[0][1] = mat1.m[0][1] - mat2.m[0][1];
		matOut.m[0][2] = mat1.m[0][2] - mat2.m[0][2];	matOut.m[0][3] = mat1.m[0][3] - mat2.m[0][3];

		matOut.m[1][0] = mat1.m[1][0] - mat2.m[1][0];	matOut.m[1][1] = mat1.m[1][1] - mat2.m[1][1];
		matOut.m[1][2] = mat1.m[1][2] - mat2.m[1][2];	matOut.m[1][3] = mat1.m[1][3] - mat2.m[1][3];

		matOut.m[2][0] = mat1.m[2][0] - mat2.m[2][0];	matOut.m[2][1] = mat1.m[2][1] - mat2.m[2][1];
		matOut.m[2][2] = mat1.m[2][2] - mat2.m[2][2];	matOut.m[2][3] = mat1.m[2][3] - mat2.m[2][3];

		matOut.m[3][0] = mat1.m[3][0] - mat2.m[3][0];	matOut.m[3][1] = mat1.m[3][1] - mat2.m[3][1];
		matOut.m[3][2] = mat1.m[3][2] - mat2.m[3][2];	matOut.m[3][3] = mat1.m[3][3] - mat2.m[3][3];

		return matOut;
	}

	Matrix44 operator *(const Matrix44& mat1, const Matrix44& mat2)
	{
		Matrix44 out;
		out.m[0][0] = mat1.m[0][0] * mat2.m[0][0] + mat1.m[0][1] * mat2.m[1][0] + mat1.m[0][2] * mat2.m[2][0] + mat1.m[0][3] * mat2.m[3][0];
		out.m[0][1] = mat1.m[0][0] * mat2.m[0][1] + mat1.m[0][1] * mat2.m[1][1] + mat1.m[0][2] * mat2.m[2][1] + mat1.m[0][3] * mat2.m[3][1];
		out.m[0][2] = mat1.m[0][0] * mat2.m[0][2] + mat1.m[0][1] * mat2.m[1][2] + mat1.m[0][2] * mat2.m[2][2] + mat1.m[0][3] * mat2.m[3][2];
		out.m[0][3] = mat1.m[0][0] * mat2.m[0][3] + mat1.m[0][1] * mat2.m[1][3] + mat1.m[0][2] * mat2.m[2][3] + mat1.m[0][3] * mat2.m[3][3];

		out.m[1][0] = mat1.m[1][0] * mat2.m[0][0] + mat1.m[1][1] * mat2.m[1][0] + mat1.m[1][2] * mat2.m[2][0] + mat1.m[1][3] * mat2.m[3][0];
		out.m[1][1] = mat1.m[1][0] * mat2.m[0][1] + mat1.m[1][1] * mat2.m[1][1] + mat1.m[1][2] * mat2.m[2][1] + mat1.m[1][3] * mat2.m[3][1];
		out.m[1][2] = mat1.m[1][0] * mat2.m[0][2] + mat1.m[1][1] * mat2.m[1][2] + mat1.m[1][2] * mat2.m[2][2] + mat1.m[1][3] * mat2.m[3][2];
		out.m[1][3] = mat1.m[1][0] * mat2.m[0][3] + mat1.m[1][1] * mat2.m[1][3] + mat1.m[1][2] * mat2.m[2][3] + mat1.m[1][3] * mat2.m[3][3];

		out.m[2][0] = mat1.m[2][0] * mat2.m[0][0] + mat1.m[2][1] * mat2.m[1][0] + mat1.m[2][2] * mat2.m[2][0] + mat1.m[2][3] * mat2.m[3][0];
		out.m[2][1] = mat1.m[2][0] * mat2.m[0][1] + mat1.m[2][1] * mat2.m[1][1] + mat1.m[2][2] * mat2.m[2][1] + mat1.m[2][3] * mat2.m[3][1];
		out.m[2][2] = mat1.m[2][0] * mat2.m[0][2] + mat1.m[2][1] * mat2.m[1][2] + mat1.m[2][2] * mat2.m[2][2] + mat1.m[2][3] * mat2.m[3][2];
		out.m[2][3] = mat1.m[2][0] * mat2.m[0][3] + mat1.m[2][1] * mat2.m[1][3] + mat1.m[2][2] * mat2.m[2][3] + mat1.m[2][3] * mat2.m[3][3];

		out.m[3][0] = mat1.m[3][0] * mat2.m[0][0] + mat1.m[3][1] * mat2.m[1][0] + mat1.m[3][2] * mat2.m[2][0] + mat1.m[3][3] * mat2.m[3][0];
		out.m[3][1] = mat1.m[3][0] * mat2.m[0][1] + mat1.m[3][1] * mat2.m[1][1] + mat1.m[3][2] * mat2.m[2][1] + mat1.m[3][3] * mat2.m[3][1];
		out.m[3][2] = mat1.m[3][0] * mat2.m[0][2] + mat1.m[3][1] * mat2.m[1][2] + mat1.m[3][2] * mat2.m[2][2] + mat1.m[3][3] * mat2.m[3][2];
		out.m[3][3] = mat1.m[3][0] * mat2.m[0][3] + mat1.m[3][1] * mat2.m[1][3] + mat1.m[3][2] * mat2.m[2][3] + mat1.m[3][3] * mat2.m[3][3];

		return out;
	}
}
