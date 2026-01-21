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
		Vec<T> operator*(const U& value) const;
		template<typename U = T, typename std::enable_if<!std::is_same<U, Vec<T>>::value, bool>::type = false>
		Vec<T> operator*=(const U& value);
		template<typename U = T, typename std::enable_if<!std::is_same<U, Vec<T>>::value, bool>::type = false>
		Vec<T> operator/(const U& value) const;
		template<typename U = T, typename std::enable_if<!std::is_same<U, Vec<T>>::value, bool>::type = false>
		Vec<T> operator/=(const U& value);

		Vec<T> operator+(const Vec<T>& vec) const;
		Vec<T>& operator+=(const Vec<T>& vec);
		Vec<T> operator-(const Vec<T>& vec) const;
		Vec<T>& operator-=(const Vec<T>& vec);
		void operator=(const Vec<T>& vec);
		bool operator==(const Vec<T>& vec) const;
		bool operator!=(const Vec<T>& vec) const;

#ifdef _DEBUG
		void print() const;
#endif // _DEBUG

	protected:
		T* m_data = nullptr;
		int m_nSize;
	};
};

#include "Vec.inl"