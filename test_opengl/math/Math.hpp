﻿#pragma once
#include "Matrix.hpp"
#include "Vec3.hpp"

#include <assert.h>
#include <math.h>
#include <cmath>

namespace YQ
{
	using Matrix4f = Matrix<float, 4, 4>;
	using Matrix3f = Matrix<float, 3, 3>;
	using Vec3f = Vec3<float>;
	constexpr double M_PI = 3.14159265358979323846;
	namespace Math
	{
		void Translate(Matrix4f& matrix, const Vec3f& vec);				//平移矩阵

		Matrix4f Rotate(const Matrix4f& matrix, float angle, const Vec3f& vec);		//旋转矩阵

		void Scale(Matrix4f& matrix, const Vec3f& vec);				//缩放矩阵

		Vec3f NormalVec(const Vec3f& vec1, const Vec3f& vec2);		//求法向量

		Matrix4f LookAt(const Vec3f& pos, const Vec3f& sight, const Vec3f& up);		//创建视图矩阵

		YQ::Matrix4f CreaPerspective(float VerticalAngle,			//创建透视矩阵
			float aspect, float near, float far);

		float DegreesToRadians(float angle);		//角度转弧度

		inline YQ::Matrix4f YQ::Math::CreaPerspective(float VerticalAngle, float aspect, float near, float far)
		{
			assert(near > 0 && near < far);
			Matrix4f temp(0);
			temp.SetValue(1, 1, 1.0f / tan(VerticalAngle / 2.0f));
			temp.SetValue(0, 0, temp.At(1, 1) / aspect);
			temp.SetValue(2, 2, (near + far) / (near - far));
			temp.SetValue(2, 3, 2.0f * near * far / (near - far));
			temp.SetValue(3, 2, -1);

			return temp;
		}

		inline float YQ::Math::DegreesToRadians(float angle)
		{
			return angle * ((float)M_PI / 180.0f);
		}

		inline void Translate(YQ::Matrix4f& matrix, const YQ::Vec3f& vec)
		{
			assert(!matrix.IsEmpty() && !vec.IsEmpty());

			//构建平移矩阵
			Matrix4f tempMatrix = Matrix4f::CreateOnce();
			int nSize = vec.Size();
			int col = matrix.Cols() - 1;
			for (int i = 0; i < nSize; ++i)
			{
				tempMatrix.SetValue(i, col, vec.At(i));
			}
			matrix *= tempMatrix;
		}

		inline Matrix4f Rotate(const Matrix4f& matrix, float angle, const Vec3f& vec)
		{
			int nSize = vec.Size();
			Vec3f unitVec(vec);
			unitVec = unitVec.Normalization();

			Matrix3f once = Matrix3f::CreateOnce();
			once *= float(cos(angle));
			//外积矩阵
			Matrix3f outerProduct;
			for (int row = 0; row < outerProduct.Rows(); ++row)
			{
				for (int col = 0; col < outerProduct.Cols(); ++col)
				{
					outerProduct.SetValue(row, col, unitVec.At(row) * unitVec.At(col));
				}
			}

			outerProduct *= (1 - cos(angle));

			//叉乘矩阵
			Matrix3f skewSymmetric(0.0f);
			skewSymmetric.SetValue(0, 1, -unitVec.At(2));
			skewSymmetric.SetValue(0, 2, unitVec.At(1));
			skewSymmetric.SetValue(1, 0, unitVec.At(2));
			skewSymmetric.SetValue(1, 2, -unitVec.At(0));
			skewSymmetric.SetValue(2, 0, -unitVec.At(1));
			skewSymmetric.SetValue(2, 1, unitVec.At(0));
			skewSymmetric *= sin(angle);

			once += outerProduct;
			once += skewSymmetric;

			//扩展
			Matrix4f RMatrix = Matrix4f::CreateOnce();
			RMatrix.Copy(once);

			return matrix * RMatrix;
		}

		inline void Scale(Matrix4f& matrix, const Vec3f& vec)
		{
			Matrix4f temp = Matrix4f::CreateOnce();
			for (int i = 0; i < vec.Size(); ++i)
			{
				temp.SetValue(i, i, vec.At(i));
			}
			matrix *= temp;
		}

		inline Vec3f NormalVec(const Vec3f& vec1, const Vec3f& vec2)
		{
			Vec3f vec;
			vec[0] = vec1.At(1) * vec2.At(2) - vec2.At(1) * vec1.At(2);
			vec[1] = vec1.At(2) * vec2.At(0) - vec2.At(2) * vec1.At(0);
			vec[2] = vec1.At(0) * vec2.At(1) - vec2.At(0) * vec1.At(1);
			return vec;
		}

		inline Matrix4f LookAt(const Vec3f& pos, const Vec3f& target, const Vec3f& up)
		{
			//方向向量

			Vec3f sightVec = pos - target;
			sightVec = sightVec.Normalization();

			Vec3f rVec = NormalVec(up, sightVec);
			rVec = rVec.Normalization();

			Vec3f tVec = NormalVec(sightVec, rVec);
			tVec = tVec.Normalization();

			Matrix4f res = Matrix4f::CreateOnce();
			Matrix4f posMat = Matrix4f::CreateOnce();
			for (int i = 0; i < 3; ++i)
			{
				res.SetValue(0, i, rVec.At(i));
				res.SetValue(1, i, tVec.At(i));
				res.SetValue(2, i, sightVec.At(i));

				posMat.SetValue(i, 3, -pos.At(i));
			}

			return res * posMat;
		}
	}
}
