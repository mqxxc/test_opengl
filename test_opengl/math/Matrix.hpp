#pragma once
#include "Vec.hpp"
namespace YQ
{
	template<class T>
	class Matrix
	{
	public:
		Matrix();
		Matrix(int row, int col, T defValue = T());
		Matrix(const Matrix& other);
		Matrix(const Vec<T>& vec);
		Matrix(Matrix&& other);
		virtual ~Matrix();

		const T& At(int row, int col) const;
		bool SetValue(int row, int col, const T& value);
		void Resize(int rows, int cols);
		int Rows() const;
		int Cols() const;
		void Destroy();		//释放数据空间
		void Clear();		//清理数据
		bool IsEmpty() const;
		const T* const Data() const;
		void Copy(const Matrix<T>& other);
		
		static Matrix<T> CreateOnce(int rows, int cols);			//创建单位矩阵

		bool operator ==(const Matrix<T>& other) const;
		bool operator !=(const Matrix<T>& other) const;
		void operator=(const Matrix<T>& other);
		Matrix<T> operator*(const Matrix<T>& other) const;
		Matrix<T>& operator*=(const Matrix<T>& other);
		Matrix<T> operator*(const T&) const;
		Matrix<T>& operator*=(const T&);
		Matrix<T> operator+(const Matrix<T>& other) const;
		Matrix<T>& operator+=(const Matrix<T>& other);
		Matrix<T> operator-(const Matrix<T>& other) const;
		Matrix<T>& operator-=(const Matrix<T>& other);

#ifdef _DEBUG
		void print();
#endif // DEBUG


	protected:
		int m_nRows;
		int m_nCols;
		T* m_datas = nullptr;
		T** m_pIndex = nullptr;

		void CreateIndex();
		bool CheckIndex(int row, int col) const;
	};
};

#include "../Source/Matrix.ipp"
