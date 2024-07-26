#pragma once

namespace StarEngine
{
	inline Matrix44 Matrix44::Translation(const Vector3& translation)
	{
		return Matrix44::Translation(translation.x, translation.y, translation.z);
	}

	inline Matrix44 Matrix44::Scale(const Vector3& scale)
	{
		return Matrix44::Scale(scale.x, scale.y, scale.z);
	}
}
