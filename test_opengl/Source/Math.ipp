#pragma once
#include "Math.hpp"
#include <assert.h>
#include <math.h>
#include <cmath>
const double M_PI = 3.14159265358979323846;

namespace YQ
{
	namespace Math
	{
		YQ::Matrix<float> YQ::Math::CreaPerspective(float VerticalAngle, float aspect, float near, float far)
		{
			assert(near > 0 && near < far);
			YQ::Matrix<float>temp(4, 4, 0);
			temp.SetValue(1, 1, 1.0f / tan(DegreesToRadians(VerticalAngle) / 2.0f));
			temp.SetValue(0, 0, temp.At(1, 1) / aspect);
			temp.SetValue(2, 2, (near + far) / (far - near));
			temp.SetValue(2, 3, 2.0f * near * far / (near - far));
			temp.SetValue(3, 2, -1);

			return temp;
		}

		float YQ::Math::DegreesToRadians(float angle)
		{
			return angle * ((float)M_PI / 180.0f);
		}

		template<class T, class T2>
		void Translate(YQ::Matrix<T>& matrix, const YQ::Vec<T2>& vec)
		{
			assert(!matrix.IsEmpty() && !vec.IsEmpty());

			//ππΩ®∆Ω“∆æÿ’Û
			Matrix<T2> tempMatrix = Matrix<T2>::CreateOnce(matrix.Rows(), matrix.Cols());
			int nSize = vec.Size();
			int col = matrix.Cols() - 1;
			for (int i = 0; i < vec.Size(); ++i)
			{
				tempMatrix.SetValue(i, col, vec.At(i));
			}
			matrix *= tempMatrix;
		}

		template<class T, class T2>
		Matrix<T> Rotate(const Matrix<T>& matrix, float angle, Vec<T2>& vec)
		{
			int nSize = vec.Size();
			float radian = DegreesToRadians(angle);
			Vec<T2>unitVec(vec);
			unitVec.Normalization();

			Matrix<T2> once = Matrix<T2>::CreateOnce(nSize, nSize);
			once *= static_cast<T2>(cos(radian));
			//Õ‚ª˝æÿ’Û
			Matrix<T2> outerProduct(nSize, nSize);
			for (int row = 0; row < outerProduct.Rows(); ++row)
			{
				for (int col = 0; col < outerProduct.Cols(); ++col)
				{
					outerProduct.SetValue(row, col, unitVec.At(row) * unitVec.At(col));
				}
			}
			outerProduct *= (1 - cos(radian));

			//≤Ê≥Àæÿ’Û
			Matrix<T2> skewSymmetric(nSize, nSize, 0.0f);
			skewSymmetric.SetValue(0, 1, -unitVec.At(2));
			skewSymmetric.SetValue(0, 2, unitVec.At(1));
			skewSymmetric.SetValue(1, 0, unitVec.At(2));
			skewSymmetric.SetValue(1, 2, -unitVec.At(0));
			skewSymmetric.SetValue(2, 0, -unitVec.At(1));
			skewSymmetric.SetValue(2, 1, unitVec.At(0));
			skewSymmetric *= sin(radian);

			once += outerProduct;
			once += skewSymmetric;

			//¿©’π
			Matrix<T2> RMatrix = Matrix<T2>::CreateOnce(matrix.Rows(), matrix.Cols());
			RMatrix.Copy(once);

			return matrix * RMatrix;
		}
	}
}