#include "EngineLibrary.h"

namespace StarEngine
{
	Quaternion::Quaternion(F32 radian, const Vector3& axis)
	{
		radian *= 0.5f;
		F32 s = sinf(radian);
		x = s * axis.x;
		y = s * axis.y;
		z = s * axis.z;
		w = cosf(radian);
	}

	void Quaternion::Normalize()
	{
		F32 mag = ::sqrtf(x * x + y * y + z * z + w * w);
		if (mag > 0.0f)
		{
			F32 oneOverMag = 1.0f / mag;
			this->x *= oneOverMag;
			this->y *= oneOverMag;
			this->z *= oneOverMag;
			this->w *= oneOverMag;
		}
	}

	void Quaternion::Inverse()
	{
		this->Normalize();
		*this = this->Conjugate();
	}

	F32 Quaternion::Length() const
	{
		return ::sqrtf(x * x + y * y + z * z + w * w);
	}

	Vector3 Quaternion::Right()
	{
		//vDir.x = 1.0f - 2.0f * (y * y + z * z);
		//vDir.y = 2.0f * (x * y - w * z);
		//vDir.z = 2.0f * (x * z + w * y);
		return Vector3::Normalize(Vector3(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y + w * z), 2.0f * (x * z - w * y)));
	}

	Vector3 Quaternion::Right() const
	{
		//vDir.x = 1.0f - 2.0f * (y * y + z * z);
		//vDir.y = 2.0f * (x * y - w * z);
		//vDir.z = 2.0f * (x * z + w * y);
		return Vector3::Normalize(Vector3(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y + w * z), 2.0f * (x * z - w * y)));
	}

	Vector3 Quaternion::Up()
	{
		return Vector3::Normalize(Vector3(2.0f * (x * y - w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z + w * x)));
	}

	Vector3 Quaternion::Up() const
	{
		return Vector3::Normalize(Vector3(2.0f * (x * y - w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z + w * x)));
	}

	Vector3 Quaternion::Forward()
	{
		//vDir.x = 2.0f * (x * z - w * y);
		//vDir.y = 2.0f * (y * z + w * x);
		//vDir.z = 1.0f - 2.0f * (x * x + y * y);
		return Vector3::Normalize(Vector3(2.0f * (x * z + w * y), 2.0f * (y * z - w * x), 1.0f - 2.0f * (x * x + y * y)));
	}

	Vector3 Quaternion::Forward() const
	{
		//vDir.x = 2.0f * (x * z - w * y);
		//vDir.y = 2.0f * (y * z + w * x);
		//vDir.z = 1.0f - 2.0f * (x * x + y * y);
		return Vector3::Normalize(Vector3(2.0f * (x * z + w * y), 2.0f * (y * z - w * x), 1.0f - 2.0f * (x * x + y * y)));
	}

	Quaternion Quaternion::Invert(const Quaternion& source)
	{
		Quaternion out = source;
		out.Inverse();
		return out;
	}

	Quaternion Quaternion::EulerAngles(const Vector3& euler)
	{
		return EulerAngles(euler.x, euler.y, euler.z);
	}

	Quaternion Quaternion::EulerAngles(F32 pitch, F32 yaw, F32 roll)
	{
		// 角度转化为弧度
		pitch = 0.5f * ANGLE_TO_RADIAN(pitch);
		yaw = 0.5f * ANGLE_TO_RADIAN(yaw);
		roll = 0.5f * ANGLE_TO_RADIAN(roll);

		F32 xs = sinf(pitch), xc = cosf(pitch);
		F32 ys = sinf(yaw), yc = cosf(yaw);
		F32 zs = sinf(roll), zc = cosf(roll);

		Quaternion q;
		q.w = yc * xc * zc + ys * xs * zs;
		q.x = yc * xs * zc + ys * xc * zs;
		q.y = ys * xc * zc - yc * xs * zs;
		q.z = yc * xc * zs - ys * xs * zc;
		//QuaternionComputeW(q);
		return q;
	}

	Vector3 Quaternion::ToEulerAngles(const Quaternion& q)
	{
		// http://www.geometrictools.com/Documentation/EulerAngles.pdf
		F32 sp = -2.0f * (q.y * q.z - q.w * q.x);
		if (sp < -0.995f)
			return Vector3(-90.0f, 0.0f, -RADIAN_TO_ANGLE((atan2f(2.0f * (q.x * q.z - q.w * q.y), 1.0f - 2.0f * (q.y * q.y + q.z * q.z)))));
		if (sp > 0.995f)
			return Vector3(90.0f, 0.0f, RADIAN_TO_ANGLE((atan2f(2.0f * (q.x * q.z - q.w * q.y), 1.0f - 2.0f * (q.y * q.y + q.z * q.z)))));

		Vector3 euler;
		euler.x = RADIAN_TO_ANGLE(asinf(sp));
		euler.y = RADIAN_TO_ANGLE(atan2f(2.0f * (q.x * q.z + q.w * q.y), 1.0f - 2.0f * (q.x * q.x + q.y * q.y)));
		euler.z = RADIAN_TO_ANGLE(atan2f(2.0f * (q.x * q.y + q.w * q.z), 1.0f - 2.0f * (q.x * q.x + q.z * q.z)));
		return euler;

		//Vector3 euler;
		//F32 sp = -2.0f * (q.y * q.z - q.w * q.x);

		////检查是否为万向锁
		//if (::fabs(sp) > 0.9999f)
		//{
		//	euler.x = RADIAN_TO_ANGLE(atan2f(-q.x * q.z + q.w * q.y, 0.5f - q.y * q.y - q.z * q.z));
		//	euler.y = RADIAN_TO_ANGLE(MATH_PI_2 * sp);
		//	euler.z = 0.0f;
		//}
		//else
		//{
		//	euler.x = RADIAN_TO_ANGLE(atan2f(q.x * q.z + q.w * q.y, 0.5f - q.x * q.x - q.y * q.y));
		//	euler.y = RADIAN_TO_ANGLE(asinf(sp));
		//	euler.z = RADIAN_TO_ANGLE(atan2f(q.x * q.y + q.w * q.z, 0.5f - q.x * q.x - q.z * q.z));
		//}

		//return euler;
	}

	//////////////////////////////////////////////////////////////////////////
	Quaternion operator *(const Quaternion& q1, const Quaternion& q2)
	{
		F32 x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
		F32 y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
		F32 z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
		F32 w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;

		return Quaternion(x, y, z, w);
	}

	Quaternion operator *(const Quaternion& q, const Vector3& v)
	{
		F32 x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
		F32 y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
		F32 z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);
		F32 w = (q.x * v.x) + (q.y * v.y) + (q.z * v.z);

		return Quaternion(x, y, z, -w);
	}

	Vector3 operator *(const Vector3& v, const Quaternion& q)
	{
		Quaternion tmp, inv, final;
		inv.Set(-q.x, -q.y, -q.z, q.w);
		inv.Normalize();
		QuaternionMultiplyVertor(q, v, tmp);
		QuaternionMultiplyQuaternion(tmp, inv, final);

		return Vector3(final.x, final.y, final.z);
	}

	Quaternion* QuaternionMultiplyQuaternion(const Quaternion& q1, const Quaternion& q2, Quaternion& out)
	{
		out.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
		out.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
		out.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
		out.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
		return &out;
	}

	Quaternion* QuaternionMultiplyVertor(const Quaternion& q, const Vector3& v, Quaternion& out)
	{
		out.x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
		out.y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
		out.z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);
		out.w = -(q.x * v.x) - (q.y * v.y) - (q.z * v.z);

		return &out;
	}

	Vector3* VertorMultiplyQuaternion(const Quaternion& q, const Vector3& v, Vector3& out)
	{
		Quaternion tmp, inv, final;
		inv.Set(-q.x, -q.y, -q.z, q.w);
		inv.Normalize();
		QuaternionMultiplyVertor(q, v, tmp);
		QuaternionMultiplyQuaternion(tmp, inv, final);

		out.x = final.x;
		out.y = final.y;
		out.z = final.z;
		return &out;
	}

	void QuaternionComputeW(Quaternion& q)
	{
		F32 t = 1.0f - (q.x * q.x) - (q.y * q.y) - (q.z * q.z);
		if (t < 0.0f)
			q.w = 0.0f;
		else
			q.w = -::sqrtf(t);
	}

	Quaternion* QuaternionNormalize(const Quaternion& in, Quaternion& out)
	{
		out = in;
		out.Normalize();
		return &out;
	}

	Vector3* QuaternionRotatePoint(const Quaternion& q, const Vector3& v, Vector3& out)
	{
		Quaternion tmp, inv, final;
		inv.Set(-q.x, -q.y, -q.z, q.w);
		inv.Normalize();
		QuaternionMultiplyVertor(q, v, tmp);
		QuaternionMultiplyQuaternion(tmp, inv, final);

		out.x = final.x;
		out.y = final.y;
		out.z = final.z;
		return &out;
	}
}
