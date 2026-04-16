#pragma once

#include <assert.h>
#include <math.h>
#include <cmath>
#include "YQMath_global.h"
#include "../include/Matrix/Matrix.hpp"
#include "../include/Vec/Vec3.hpp"

namespace YQ
{
	using Vec3f = Vec3<float>;
	using Vec2f = Vec2<float>;

	using Matrix4f = Matrix<float, 4, 4>;
	using Matrix3f = Matrix<float, 3, 3>;

#ifndef BUILD_STATIC
	#ifndef YQMATH_EXPORTS
	extern template class YQMath_EXPORT Vec3<float>;
	extern template class YQMath_EXPORT Vec2<float>;
	extern template class YQMath_EXPORT Matrix<float, 4, 4>;
	extern template class YQMath_EXPORT Matrix<float, 3, 3>;
	#endif
#endif

	namespace Math
	{
		constexpr double M_PI = 3.14159265358979323846;

		void YQMath_EXPORT Translate(YQ::Matrix4f& matrix, const YQ::Vec3f& vec);				//平移矩阵

		YQ::Matrix4f YQMath_EXPORT Rotate(const YQ::Matrix4f& matrix, float angle, const YQ::Vec3f& vec);		//旋转矩阵

		void YQMath_EXPORT Scale(YQ::Matrix4f& matrix, const YQ::Vec3f& vec);				//缩放矩阵

		YQ::Vec3f YQMath_EXPORT NormalVec(const YQ::Vec3f& vec1, const YQ::Vec3f& vec2);		//求法向量

		YQ::Matrix4f YQMath_EXPORT LookAt(const YQ::Vec3f& pos, const YQ::Vec3f& sight, const YQ::Vec3f& up);		//创建视图矩阵

		YQ::Matrix4f YQMath_EXPORT CreaPerspective(float VerticalAngle,			//创建透视矩阵
			float aspect, float near, float far);

		float DegreesToRadians(float angle);		//角度转弧度


		//内联实现
		inline float DegreesToRadians(float angle)
		{
			return angle * ((float)M_PI / 180.0f);
		}
	}
}
