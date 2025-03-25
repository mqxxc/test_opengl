#pragma once
#include "Matrix.hpp"
#include <assert.h>

namespace YQ
{
	template<typename T, int nRow, int nCol>
	Matrix<T, nRow, nCol>::Matrix()
	{
		m_nRows = nRow;
		m_nCols = nCol;

		int nCount = m_nRows * m_nCols;
		if (nCount <= 0)
		{
			return;
		}

		m_datas = new T[nCount];
		CreateIndex();
	}

	template<typename T, int nRow, int nCol>
	Matrix<T, nRow, nCol>::Matrix(T defValue)
		: Matrix()
	{
		int nCount = m_nRows * m_nCols;
		for (int i = 0; i < nCount; ++i)
		{
			m_datas[i] = defValue;
		}
	}

	template<typename T, int nRow, int nCol>
	Matrix<T, nRow, nCol>::Matrix(const Matrix& other)
	{
		Destroy();
		m_nRows = other.m_nRows;
		m_nCols = other.m_nCols;
		int nCount = m_nRows * m_nCols;
		m_datas = new T[nCount];
		CreateIndex();

		for (int i = 0; i < nCount; ++i)
		{
			m_datas[i] = other.m_datas[i];
		}
	}

	template<typename T, int nRow, int nCol>
	Matrix<T, nRow, nCol>::Matrix(Matrix&& other)
	{
		m_nRows = other.m_nRows;
		m_nCols = other.m_nCols;

		m_datas = other.m_datas;
		other.m_datas = nullptr;

		m_pIndex = other.m_pIndex;
		other.m_pIndex = nullptr;
	}

	template<typename T, int nRow, int nCol>
	Matrix<T, nRow, nCol>::~Matrix()
	{
		Destroy();
	}

	template<typename T, int nRow, int nCol>
	const T& Matrix<T, nRow, nCol>::At(int row, int col) const
	{
		if (CheckIndex(row, col))
		{
			return m_pIndex[row][col];
		}
		return T();
	}

	template<typename T, int nRow, int nCol>
	bool Matrix<T, nRow, nCol>::SetValue(int row, int col, const T& value)
	{
		if (CheckIndex(row, col))
		{
			m_pIndex[row][col] = value;
			return true;
		}
		return false;
	}

	template<typename T, int nRow, int nCol>
	int Matrix<T, nRow, nCol>::Rows() const
	{
		return m_nRows;
	}

	template<typename T, int nRow, int nCol>
	int Matrix<T, nRow, nCol>::Cols() const
	{
		return m_nCols;
	}

	template<typename T, int nRow, int nCol>
	void Matrix<T, nRow, nCol>::Destroy()
	{
		if (m_datas != nullptr)
		{
			delete m_datas;
			m_datas = nullptr;
		}

		if (m_pIndex != nullptr)
		{
			delete m_pIndex;
			m_pIndex = nullptr;
		}
		m_nRows = 0;
		m_nCols = 0;
	}

	template<typename T, int nRow, int nCol>
	void Matrix<T, nRow, nCol>::Clear()
	{
		if (m_datas != nullptr)
		{
			delete m_datas;
			m_datas = nullptr;
		}

		if (m_pIndex != nullptr)
		{
			delete m_pIndex;
			m_pIndex = nullptr;
		}

		m_nCols = 0;
		m_nRows = 0;
	}

	template<typename T, int nRow, int nCol>
	bool Matrix<T, nRow, nCol>::IsEmpty() const
	{
		return m_datas == nullptr;
	}

	template<typename T, int nRow, int nCol>
	const T* const Matrix<T, nRow, nCol>::Data() const
	{
		return m_datas;
	}

	template<typename T, int nRow, int nCol>
	inline Matrix<T, nCol, nRow> Matrix<T, nRow, nCol>::Transposition() const
	{
		Matrix<T, nCol, nRow> temp;
		for (int row = 0; row < m_nRows; ++row)
		{
			for (int col = 0; col < m_nCols; ++col)
			{
				temp.m_pIndex[col][row] = m_pIndex[row][col];
			}
		}
		return temp;
	}

	template<typename T, int nRow, int nCol>
	template<int otherRow, int otherCol>
	void Matrix<T, nRow, nCol>::Copy(const Matrix<T, otherRow, otherCol>& other)
	{
		for (int row = 0; row < m_nRows && row < other.Rows(); ++row)
		{
			for (int col = 0; col < m_nCols && col < other.Cols(); ++col)
			{
				m_pIndex[row][col] = other.At(row,col);
			}
		}
	}

	template<typename T, int nRow, int nCol>
	Matrix<T, nRow, nCol> Matrix<T, nRow, nCol>::CreateOnce()
	{
		if (nRow != nCol)
		{
			return Matrix<T, nRow, nCol>();
		}

		Matrix<T, nRow, nCol> matrix;

		for (int row = 0; row < nRow; ++row)
		{
			for (int col = 0; col < nCol; ++col)
			{
				matrix.m_pIndex[row][col] = row == col ? static_cast<T>(1) : static_cast<T>(0);
			}
		}

		return matrix;
	}

	template<typename T, int nRow, int nCol>
	bool Matrix<T, nRow, nCol>::operator==(const Matrix<T, nRow, nCol>& other) const
	{
		if (m_nRows != other.m_nRows || m_nCols != m_nCols)
		{
			return false;
		}

		int nCount = m_nRows * m_nCols;
		for (int nIndex = 0; nIndex < nCount; ++nIndex)
		{
			if (m_datas[nIndex] != other.m_datas[nIndex])
			{
				return false;
			}
		}

		return true;
	}

	template<typename T, int nRow, int nCol>
	inline bool Matrix<T, nRow, nCol>::operator!=(const Matrix<T, nRow, nCol>& other) const
	{
		return !(*this) == other;
	}

	template<typename T, int nRow, int nCol>
	void Matrix<T, nRow, nCol>::operator=(const Matrix<T, nRow, nCol>& other)
	{
		assert(m_nRows == other.m_nRows && m_nCols == other.m_nCols);

		int nSize = m_nRows * m_nCols;
		for (int i = 0; i < nSize; ++i)
		{
			m_datas[i] = other.m_datas[i];
		}
	}

	template<typename T, int nRow, int nCol>
	template<int otherRow, int otherCol>
	Matrix<T, nRow, nCol> Matrix<T, nRow, nCol>::operator*(const Matrix<T, otherRow, otherCol>& other) const
	{
		assert(m_nCols == other.m_nRows && !IsEmpty() && !other.IsEmpty());
		Matrix<T, nRow, otherCol> tempMatrix;
		for (int row = 0; row < m_nRows; ++row)
		{
			for (int col = 0; col < other.m_nCols; ++col)
			{
				T temp = T();
				for (int i = 0; i < m_nCols; ++i)
				{
					temp += m_pIndex[row][i] * other.m_pIndex[i][col];
				}

				tempMatrix.SetValue(row, col, temp);
			}
		}

		return tempMatrix;
	}

	template<typename T, int nRow, int nCol>
	template<int otherRow, int otherCol>
	Matrix<T, nRow, nCol>& Matrix<T, nRow, nCol>::operator*=(const Matrix<T, otherRow, otherCol>& other)
	{
		(*this) = (*this) * other;
		return *this;
	}

	template<typename T, int nRow, int nCol>
	Matrix<T, nRow, nCol> Matrix<T, nRow, nCol>::operator*(const T& value) const
	{
		Matrix<T, nRow, nCol> temp(*this);
		int nSize = m_nRows * m_nCols;
		for (int i = 0; i < nSize; ++i)
		{
			temp.m_datas[i] *= value;
		}
		return temp;
	}

	template<typename T, int nRow, int nCol>
	Matrix<T, nRow, nCol>& Matrix<T, nRow, nCol>::operator*=(const T& value)
	{
		int nSize = m_nRows * m_nCols;
		for (int i = 0; i < nSize; ++i)
		{
			m_datas[i] *= value;
		}
		return *this;
	}

	template<typename T, int nRow, int nCol>
	Matrix<T, nRow, nCol> Matrix<T, nRow, nCol>::operator+(const Matrix<T, nRow, nCol>& other) const
	{
		assert(m_nRows == other.m_nRows && m_nCols == other.m_nCols
			&& !IsEmpty() && !other.IsEmpty());

		Matrix<T, nRow, nCol> temp;

		for (int row = 0; row < m_nRows; ++row)
		{
			for (int col = 0; col < m_nCols; ++col)
			{
				temp.m_pIndex[row][col] = m_pIndex[row][col] + other.m_pIndex[row][col];
			}
		}

		return temp;
	}

	template<typename T, int nRow, int nCol>
	Matrix<T, nRow, nCol>& Matrix<T, nRow, nCol>::operator+=(const Matrix<T, nRow, nCol>& other)
	{
		(*this) = (*this) + other;
		return (*this);
	}

	template<typename T, int nRow, int nCol>
	Matrix<T, nRow, nCol> Matrix<T, nRow, nCol>::operator-(const Matrix<T, nRow, nCol>& other) const
	{
		assert(m_nRows == other.m_nRows && m_nCols == other.m_nCols
			&& !IsEmpty() && !other.IsEmpty());

		Matrix<T, nRow, nCol> temp(m_nRows, m_nCols);

		for (int row = 0; row < m_nRows; ++row)
		{
			for (int col = 0; col < m_nCols; ++col)
			{
				temp.m_pIndex[row][col] = m_pIndex[row][col] - other.m_pIndex[row][col];
			}
		}

		return temp;
	}

	template<typename T, int nRow, int nCol>
	Matrix<T, nRow, nCol>& Matrix<T, nRow, nCol>::operator-=(const Matrix<T, nRow, nCol>& other)
	{
		(*this) = (*this) - other;
		return (*this);
	}

	template<typename T, int nRow, int nCol>
	void Matrix<T, nRow, nCol>::CreateIndex()
	{
		if (m_pIndex != nullptr)
		{
			delete m_pIndex;
		}

		m_pIndex = new T * [m_nRows];
		for (int row = 0; row < m_nRows; ++row)
		{
			m_pIndex[row] = &m_datas[row * m_nCols];
		}
	}

	template<typename T, int nRow, int nCol>
	bool Matrix<T, nRow, nCol>::CheckIndex(int row, int col) const
	{
		return (row > -1 && row < m_nRows)
			&& (col > -1 && col < m_nCols);
	}
}

#ifdef _DEBUG
#include <iostream>
template<typename T, int nRow, int nCol>
void YQ::Matrix<T, nRow, nCol>::print()
{
	for (int row = 0; row < m_nRows; ++row)
	{
		for (int col = 0; col < m_nCols; ++col)
		{
			std::cout << m_pIndex[row][col] << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
#endif // _DEBUG
