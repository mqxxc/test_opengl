#pragma once
#include "Matrix.hpp"
#include "Vec.hpp"

namespace YQ
{
	namespace Math
	{
		YQ::Matrix<float> CreaPerspective(float VerticalAngle, 
			float aspect, float near, float far);

		template<class T, class T2>
		void Translate(YQ::Matrix<T>& matrix, const YQ::Vec<T2>& vec);

		template<class T, class T2>
		Matrix<T> Rotate(const Matrix<T>& matrix, float angle, Vec<T2>& vec);

		float DegreesToRadians(float angle);
		
	}
};

#include "../Source/Math.ipp"