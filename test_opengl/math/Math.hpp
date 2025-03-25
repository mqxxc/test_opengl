#pragma once
#include "Matrix.hpp"
#include "Vec.hpp"

namespace YQ
{
	using Matrix4f = Matrix<float, 4, 4>;
	using Matrix3f = Matrix<float, 3, 3>;
	using Vec3f = Vec<float, 3>;
	namespace Math
	{
		YQ::Matrix4f CreaPerspective(float VerticalAngle,			//创建透视矩阵
			float aspect, float near, float far);

		void Translate(Matrix4f& matrix, const Vec3f& vec);				//平移矩阵

		Matrix4f Rotate(const Matrix4f& matrix, float angle, const Vec3f& vec);		//旋转矩阵

		Vec3f NormalVec(const Vec3f& vec1, const Vec3f& vec2);		//求法向量

		Matrix4f LookAt(const Vec3f& pos, const Vec3f& sight, const Vec3f& up);		//创建视图矩阵

		float DegreesToRadians(float angle);
		
	}
};

#include "../Source/Math.ipp"