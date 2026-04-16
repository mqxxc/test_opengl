#pragma once
#include "Matrix.hpp"
#include "Vec3.hpp"

typedef unsigned int uint;

namespace YQ
{
	using Vec3f = Vec3<float>;
	using Vec2f = Vec2<float>;

	using Matrix4f = Matrix<float, 4, 4>;
	using Matrix3f = Matrix<float, 3, 3>;
}
