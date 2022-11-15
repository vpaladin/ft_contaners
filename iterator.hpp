#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft {
	template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
			typename _Pointer = _Tp*, typename _Reference = _Tp&>
	struct iterator
	{
		typedef _Category  iterator_category;
		typedef _Tp        value_type;
		typedef _Distance  difference_type;
		typedef _Pointer   pointer;
		typedef _Reference reference;
	};

//	template <typename T>
//	class VecIter: public ft::iterator<std::random_access_iterator_tag, T> {
//	public:
//		typedef ft::iterator<std::random_access_iterator_tag, T>	ancestor;
//		typedef typename ancestor::pointer							pointer;
//		typedef typename ancestor::reference						reference;
//		typedef typename ancestor::difference_type					difference_type;
//	private:
//		pointer ptr;
//	public:
//		VecIter() {};
//		VecIter(pointer x) {
//       	this->ptr = x;
//     	};
//		VecIter(const VecIter &other) {
//			this->ptr = other.base();
//		};
//		~VecIter() {};
//
//		VecIter &operator=(const VecIter &other) {
//			if (this != &other)
//				ptr = other.ptr;
//			return *this;
//		}
//		pointer	base() const								{ return ptr; }
//		VecIter	&operator++()								{ ++ptr; return *this; }
//		VecIter	operator++(int)								{ VecIter tmp(*this); ++ptr; return tmp; }
//		VecIter	&operator--()								{ --ptr; return *this; }
//		VecIter	operator--(int)								{ VecIter tmp(*this); --ptr; return tmp; }
//		VecIter	operator+(const difference_type n) const	{ return ptr + n; }
//		VecIter	operator-(const difference_type n) const	{ return ptr - n; }
//		VecIter	&operator+=(const difference_type n)		{ ptr += n; return *this; }
//		VecIter	&operator-=(const difference_type n)		{ ptr -= n; return *this; }
//
//		pointer		operator->() const							{ return ptr; }
//		reference	operator*() const							{ return *ptr; }
//		reference	operator[](difference_type n) const 		{ return *(ptr + n); }
//
//
//		friend difference_type	operator-(const VecIter &a, const VecIter &b)		{ return a.ptr - b.ptr; }
//		friend VecIter		operator+(int n, VecIter &a) { a.ptr = a.ptr + n; return a.ptr; }
//
//		friend bool operator>(const VecIter &lhs, const VecIter &rhs) {
//			return lhs.ptr > rhs.ptr;
//		}
//		friend bool operator<(const VecIter &lhs, const VecIter &rhs) {
//			return lhs.ptr < rhs.ptr;
//		}
//		friend bool operator==(const VecIter &lhs, const VecIter &rhs) {
//			return lhs.ptr == rhs.ptr;
//		}
//		friend bool operator!=(const VecIter &lhs, const VecIter &rhs) {
//			return lhs.ptr != rhs.ptr;
//		}
//		friend bool operator>=(const VecIter &lhs, const VecIter &rhs) {
//			return lhs.ptr >= rhs.ptr;
//		}
//		friend bool operator<=(const VecIter &lhs, const VecIter &rhs) {
//			return lhs.ptr <= rhs.ptr;
//		}
//	};
}

#endif
