#pragma once
#include <type_traits>

#ifdef _DEBUG
#include <iostream>
#endif

namespace YQ
{
	template<typename T>
	class Vec 
	{
	public:
		Vec();
		explicit Vec(int nSize);
		template<typename... Args>
		explicit Vec(Args&&... args);
		Vec(const Vec& other);
		Vec(Vec&& other);
		virtual ~Vec();

		int Size() const;
		bool IsEmpty() const;
		const T& At(int nIndex) const;
		bool SetValue(int nIndex, const T& value);
		void Clear();
		void Destroy();
		const Vec<T> Normalization() const;
		const T* const Data() const;
		T& operator[](int nIndex);
		T DotMultiplication(const Vec<T>& vec) const;
		void Copy(const Vec<T>& other);
		//Vec<T> CrossProduct(const Vec<T>& vec) const;

		template<typename U = T, typename std::enable_if<!std::is_same<U, Vec<T>>::value, bool>::type = false>
		Vec<T> operator*(const U& vec) const;
		Vec<T> operator+(const Vec<T>& vec) const;
		Vec<T>& operator+=(const Vec<T>& vec);
		Vec<T> operator-(const Vec<T>& vec) const;
		Vec<T>& operator-=(const Vec<T>& vec);
		void operator=(const Vec<T>& vec);

#ifdef _DEBUG
		void print() const;
#endif // _DEBUG

	protected:
		T* m_data = nullptr;
		int m_nSize;
	};
/// /////////////////////////////////////
	template<typename T>
	inline Vec<T>::Vec()
	{
		m_nSize = 0;
		m_data = nullptr;
	}
	template<typename T>
	Vec<T>::Vec(int nSize)
	{
		if (nSize < 1)
		{
			throw"vec size is illegality";
		}
		m_nSize = nSize;
		m_data = new T[m_nSize];
	}

	template<typename T>
	template<typename ...Args>
	Vec<T>::Vec(Args && ...args)
		:Vec(sizeof...(args))
	{
		int i = 0;
		((m_data[i++] = std::forward<Args>(args)), ...);
	}

	template<typename T>
	Vec<T>::Vec(const Vec& other)
		: Vec(other.Size())
	{
		Copy(other);
	}

	template<typename T>
	Vec<T>::Vec(Vec&& other)
	{
		Destroy();
		m_data = other.m_data;
		m_nSize = other.m_nSize;

		other.m_data = nullptr;
		other.m_nSize = 0;
	}

	template<typename T>
	Vec<T>::~Vec()
	{
		Destroy();
	}

	template<typename T>
	int Vec<T>::Size() const
	{
		return m_nSize;
	}

	template<typename T>
	bool Vec<T>::IsEmpty() const
	{
		return m_nSize == 0;
	}

	template<typename T>
	const T& Vec<T>::At(int nIndex) const
	{
		if (m_data == nullptr || nIndex < 0 || nIndex >= m_nSize)
		{
			throw "data is null";
		}

		return m_data[nIndex];
	}

	template<typename T>
	bool Vec<T>::SetValue(int nIndex, const T& value)
	{
		if (m_data == nullptr || nIndex < 0 || nIndex >= m_nSize)
		{
			return false;
		}

		m_data[nIndex] = value;
		return true;
	}

	template<typename T>
	void Vec<T>::Clear()
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			m_data[i] = T();
		}
	}

	template<typename T>
	void Vec<T>::Destroy()
	{
		if (m_data != nullptr)
		{
			delete m_data;
			m_data = nullptr;
		}

		m_nSize = 0;
	}

	template<typename T>
	const Vec<T> Vec<T>::Normalization() const
	{
		T length = 0;
		for (int i = 0; i < m_nSize; ++i)
		{
			length += m_data[i] * m_data[i];
		}

		if (length != 0)
		{
			Vec<T> temp(Size());
			length = sqrt(length);
			for (int i = 0; i < m_nSize; ++i)
			{
				temp.m_data[i] = m_data[i] / static_cast<T>(length);
			}
			return temp;
		}
		return Vec<T>();
	}

	template<typename T>
	const T* const Vec<T>::Data() const
	{
		return m_data;
	}

	template<typename T>
	T& Vec<T>::operator[](int nIndex)
	{
		if (m_data == nullptr || nIndex < 0 || nIndex >= m_nSize)
		{
			throw "index is illegality";
		}

		return m_data[nIndex];
	}

	template<typename T>
	inline T Vec<T>::DotMultiplication(const Vec<T>& vec) const
	{
		if (Size() != vec.Size())
		{
			throw "size not equal";
		}

		T res = 0;
		for (int i = 0; i < m_nSize; ++i)
		{
			res += m_data[i] *= vec.m_data[i];
		}

		return res;
	}

	template<typename T>
	inline void Vec<T>::Copy(const Vec<T>& other)
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			m_data[i] = other.At(i);
		}
	}

	/*template<typename T>
	inline Vec<T> Vec<T>::CrossProduct(const Vec<T>& vec) const
	{
	}*/

	template<typename T>
	template<typename U, typename std::enable_if<!std::is_same<U, Vec<T>>::value, bool>::type>
	inline Vec<T> Vec<T>::operator*(const U& value) const
	{
		Vec<T> res(*this);
		for (int i = 0; i < m_nSize; ++i)
		{
			res.m_data[i] *= value;
		}
		return res;
	}

	template<typename T>
	inline Vec<T> Vec<T>::operator+(const Vec<T>& vec) const
	{
		Vec<T> res(m_nSize);
		for (int i = 0; i < m_nSize; ++i)
		{
			res[i] = m_data[i] + vec.m_data[i];
		}
		return res;
	}

	template<typename T>
	Vec<T>& Vec<T>::operator+=(const Vec<T>& vec)
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			m_data[i] += vec.At(i);
		}
		return (*this);
	}

	template<typename T>
	inline Vec<T> Vec<T>::operator-(const Vec<T>& vec) const
	{
		Vec<T> res(m_nSize);
		for (int i = 0; i < m_nSize; ++i)
		{
			res[i] = m_data[i] - vec.m_data[i];
		}
		return res;
	}

	template<typename T>
	Vec<T>& Vec<T>::operator-=(const Vec<T>& vec)
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			m_data[i] -= vec.At(i);
		}
		return (*this);
	}

	template<typename T>
	void Vec<T>::operator=(const Vec<T>& vec)
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			m_data[i] = vec.At(i);
		}
	}

#ifdef _DEBUG
	template<typename T>
	void YQ::Vec<T>::print() const
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			std::cout << m_data[i] << "   ";
		}
		std::cout << std::endl << std::endl;
	}
#endif // _DEBUG
};
