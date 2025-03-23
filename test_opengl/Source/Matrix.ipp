#pragma once
#include "Matrix.hpp"

template<class T>
YQ::Matrix<T>::Matrix()
{
	m_nRows = 0;
	m_nCols = 0;
}

template<class T>
 YQ::Matrix<T>::Matrix(int row, int col, T defValue)
{
	Resize(row, col);
	int nCount = m_nRows * m_nCols;
	for (int i = 0; i < nCount; ++i)
	{
		m_datas[i] = defValue;
	}
}

template<class T>
 YQ::Matrix<T>::Matrix(const Matrix& other)
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

 template<class T>
 YQ::Matrix<T>::Matrix(const YQ::Vec<T>& vec)
 {
	 Resize(1, vec.Size());

	 for (int col = 0; col < m_nCols; ++col)
	 {
		 m_datas[col] = vec.At(col);;
	 }
 }

template<class T>
 YQ::Matrix<T>::Matrix(Matrix&& other)
{
	m_nRows = other.m_nRows;
	m_nCols = other.m_nCols;

	m_datas = other.m_datas;
	other.m_datas = nullptr;

	m_pIndex = other.m_pIndex;
	other.m_pIndex = nullptr;
}

template<class T>
YQ::Matrix<T>::~Matrix()
{
	Destroy();
}

template<class T>
const T& YQ::Matrix<T>::At(int row, int col) const
{
	if (CheckIndex(row, col))
	{
		return m_pIndex[row][col];
	}
	return T();
}

template<class T>
bool YQ::Matrix<T>::SetValue(int row, int col, const T& value)
{
	if (CheckIndex(row, col))
	{
		m_pIndex[row][col] = value;
		return true;
	}
	return false;
}

template<class T>
void YQ::Matrix<T>::Resize(int rows, int cols)
{
	 int nCount = rows * cols;
	 if (nCount <= 0)
	 {
		 return;
	 }

	 Destroy();
	 m_nRows = rows;
	 m_nCols = cols;
	 m_datas = new T[nCount];
	 CreateIndex();
}

template<class T>
int YQ::Matrix<T>::Rows() const
{
	 return m_nRows;
}

template<class T>
int YQ::Matrix<T>::Cols() const
{
	return m_nCols;
}

template<class T>
inline void YQ::Matrix<T>::Destroy()
{
}

template<class T>
void YQ::Matrix<T>::Clear()
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

template<class T>
bool YQ::Matrix<T>::IsEmpty() const
{
	 return m_datas == nullptr;
}

template<class T>
const T* const YQ::Matrix<T>::Data() const
{
	 return m_datas;
}

template<class T>
void YQ::Matrix<T>::Copy(const Matrix<T>& other)
{
	for (int row = 0; row < m_nRows && row < other.m_nRows; ++row)
	{
		for (int col = 0; col < m_nCols && col < other.m_nCols; ++col)
		{
			m_pIndex[row][col] = other.m_pIndex[row][col];
		}
	}
}

template<class T>
YQ::Matrix<T> YQ::Matrix<T>::CreateOnce(int rows, int cols)
{
	if (rows != cols)
	{
		return YQ::Matrix<T>();
	}

	YQ::Matrix<T> matrix(rows, cols);

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			matrix.m_pIndex[row][col] = row == col ? static_cast<T>(1) : static_cast<T>(0);
		}
	}

	return matrix;
}

template<class T>
bool YQ::Matrix<T>::operator==(const YQ::Matrix<T>& other) const
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

template<class T>
inline bool YQ::Matrix<T>::operator!=(const Matrix<T>& other) const
{
	return !(*this) == other;
}

template<class T>
void YQ::Matrix<T>::operator=(const Matrix<T>& other)
{
	assert(m_nRows == other.m_nRows && m_nCols == other.m_nCols);

	int nSize = m_nRows * m_nCols;
	for (int i = 0; i < nSize; ++i)
	{
		m_datas[i] = other.m_datas[i];
	}
}

template<class T>
YQ::Matrix<T> YQ::Matrix<T>::operator*(const Matrix<T>& other) const
{
	assert(m_nCols == other.m_nRows && !IsEmpty() && !other.IsEmpty());
	Matrix<T> tempMatrix(m_nRows, other.m_nCols);
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

template<class T>
YQ::Matrix<T>& YQ::Matrix<T>::operator*=(const Matrix<T>& other)
{
	(*this) = (*this) * other;
	return *this;
}

template<class T>
YQ::Matrix<T> YQ::Matrix<T>::operator*(const T& value) const
{
	Matrix<T> temp(*this);
	int nSize = m_nRows * m_nCols;
	for (int i = 0; i < nSize; ++i)
	{
		temp.m_datas[i] *= value;
	}
	return temp;
}

template<class T>
YQ::Matrix<T>& YQ::Matrix<T>::operator*=(const T& value)
{
	int nSize = m_nRows * m_nCols;
	for (int i = 0; i < nSize; ++i)
	{
		m_datas[i] *= value;
	}
	return *this;
}

template<class T>
YQ::Matrix<T> YQ::Matrix<T>::operator+(const Matrix<T>& other) const
{
	assert(m_nRows == other.m_nRows && m_nCols == other.m_nCols
		&& !IsEmpty() && !other.IsEmpty());

	Matrix<T> temp(m_nRows, m_nCols);

	for (int row = 0; row < m_nRows; ++row)
	{
		for (int col = 0; col < m_nCols; ++col)
		{
			temp.m_pIndex[row][col] = m_pIndex[row][col] + other.m_pIndex[row][col];
		}
	}

	return temp;
}

template<class T>
YQ::Matrix<T>& YQ::Matrix<T>::operator+=(const Matrix<T>& other)
{
	(*this) = (*this) + other;
	return (*this);
}

template<class T>
YQ::Matrix<T> YQ::Matrix<T>::operator-(const Matrix<T>& other) const
{
	assert(m_nRows == other.m_nRows && m_nCols == other.m_nCols
		&& !IsEmpty() && !other.IsEmpty());

	Matrix<T> temp(m_nRows, m_nCols);

	for (int row = 0; row < m_nRows; ++row)
	{
		for (int col = 0; col < m_nCols; ++col)
		{
			temp.m_pIndex[row][col] = m_pIndex[row][col] - other.m_pIndex[row][col];
		}
	}

	return temp;
}

template<class T>
YQ::Matrix<T>& YQ::Matrix<T>::operator-=(const Matrix<T>& other)
{
	(*this) = (*this) - other;
	return (*this);
}

#ifdef _DEBUG
#include <iostream>
template<class T>
void YQ::Matrix<T>::print()
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

template<class T>
void YQ::Matrix<T>::CreateIndex()
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

 template<class T>
 bool YQ::Matrix<T>::CheckIndex(int row, int col) const
 {
	return (row > -1 && row < m_nRows) 
		&& (col > -1 && col < m_nCols);
 }
