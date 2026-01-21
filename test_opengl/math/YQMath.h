#pragma once
#include "pch.h"

#include <assert.h>
#include <math.h>
#include <cmath>

namespace YQ
{
	namespace Math
	{
		constexpr double M_PI = 3.14159265358979323846;

		void Translate(YQ::Matrix4f& matrix, const YQ::Vec3f& vec);				//平移矩阵

		YQ::Matrix4f Rotate(const YQ::Matrix4f& matrix, float angle, const YQ::Vec3f& vec);		//旋转矩阵

		void Scale(YQ::Matrix4f& matrix, const YQ::Vec3f& vec);				//缩放矩阵

		YQ::Vec3f NormalVec(const YQ::Vec3f& vec1, const YQ::Vec3f& vec2);		//求法向量

		YQ::Matrix4f LookAt(const YQ::Vec3f& pos, const YQ::Vec3f& sight, const YQ::Vec3f& up);		//创建视图矩阵

		YQ::Matrix4f CreaPerspective(float VerticalAngle,			//创建透视矩阵
			float aspect, float near, float far);

		float DegreesToRadians(float angle);		//角度转弧度



		inline float DegreesToRadians(float angle)
		{
			return angle * ((float)M_PI / 180.0f);
		}
	}
}
