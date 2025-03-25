#pragma once

namespace YQ
{
	template<typename T, int nRow, int nCol>
	class Matrix
	{
	public:
		Matrix();
		Matrix(T defValue);
		Matrix(const Matrix& other);
		Matrix(Matrix&& other);
		virtual ~Matrix();

		const T& At(int row, int col) const;
		bool SetValue(int row, int col, const T& value);
		int Rows() const;
		int Cols() const;
		void Destroy();		//释放数据空间
		void Clear();		//清理数据
		bool IsEmpty() const;
		const T* const Data() const;
		Matrix<T, nCol, nRow> Transposition() const;		//转至矩阵

		template<int otherRow, int otherCol>
		void Copy(const Matrix<T, otherRow, otherCol>& other);

		static Matrix<T, nRow, nCol> CreateOnce();			//创建单位矩阵
		
		bool operator ==(const Matrix<T, nRow, nCol>& other) const;
		bool operator !=(const Matrix<T, nRow, nCol>& other) const;
		void operator=(const Matrix<T, nRow, nCol>& other);
		template<int otherRow, int otherCol>
		Matrix<T, nRow, nCol> operator*(const Matrix<T, otherRow, otherCol>& other) const;
		template<int otherRow, int otherCol>
		Matrix<T, nRow, nCol>& operator*=(const Matrix<T, otherRow, otherCol>& other);
		Matrix<T, nRow, nCol> operator*(const T&) const;
		Matrix<T, nRow, nCol>& operator*=(const T&);
		Matrix<T, nRow, nCol> operator+(const Matrix<T, nRow, nCol>& other) const;
		Matrix<T, nRow, nCol>& operator+=(const Matrix<T, nRow, nCol>& other);
		Matrix<T, nRow, nCol> operator-(const Matrix<T, nRow, nCol>& other) const;
		Matrix<T, nRow, nCol>& operator-=(const Matrix<T, nRow, nCol>& other);

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
