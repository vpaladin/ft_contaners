#ifndef UTILS_HPP
#define UTILS_HPP

#include <type_traits>

namespace ft {

	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type;};


	template<class T, bool v>
	struct integral_constant
	{
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const { return value; }
	};
	template <class T>
	struct is_integral:							public integral_constant<bool, false> {};
	template <>
	struct is_integral<bool>:					public integral_constant<bool, true> {};
	template <>
	struct is_integral<char>:					public integral_constant<bool, true> {};
	template <>
	struct is_integral<signed char>:			public integral_constant<bool, true> {};
	template <>
	struct is_integral<unsigned char>:			public integral_constant<bool, true> {};
	template <>
	struct is_integral<wchar_t>:				public integral_constant<bool, true> {};
	template <>
	struct is_integral<char16_t>:				public integral_constant<bool, true> {};
	template <>
	struct is_integral<char32_t>:				public integral_constant<bool, true>{};
	template <>
	struct is_integral<short>:					public integral_constant<bool, true> {};
	template <>
	struct is_integral<unsigned short>:			public integral_constant<bool, true> {};
	template <>
	struct is_integral<int>:					public integral_constant<bool, true> {};
	template <>
	struct is_integral<unsigned int>:			public integral_constant<bool, true> {};
	template <>
	struct is_integral<long>:					public integral_constant<bool, true> {};
	template <>
	struct is_integral<unsigned long>:			public integral_constant<bool, true> {};
	template <>
	struct is_integral<long long>:				public integral_constant<bool, true> {};
	template <>
	struct is_integral<unsigned long long>:		public integral_constant<bool, true> {};

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (!(*first1 == *first2))
				return false;
		return true;
	}
	
	template <class InputIterator1, class InputIterator2, typename BinaryPredicate>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (!pred(*first1, *first2))
				return false;
		return true;
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (!comp(*first2, *first1))
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		while (first1!=last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}
}

#endif
