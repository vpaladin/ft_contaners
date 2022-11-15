#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
	template <class Iterator> class reverse_iterator {
	public:
		typedef Iterator	iterator_type;
		typedef typename	iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename	iterator_traits<Iterator>::value_type			value_type;
		typedef typename	iterator_traits<Iterator>::pointer				pointer;
		typedef typename	iterator_traits<Iterator>::reference			reference;
		typedef typename	iterator_traits<Iterator>::iterator_category	iterator_category;
	protected:
		iterator_type	iter;
	public:
		explicit reverse_iterator() : iter() {};
		explicit reverse_iterator(iterator_type	iter) : iter(iter) {}
		template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it) : iter(rev_it.base()) {}

		iterator_type	base()	const							{ return (iter); }

		reference			operator*() const			 		{ iterator_type temp = iter; return *(--temp); }
		reverse_iterator	operator+(difference_type n) const	{ return (reverse_iterator(iter - n)) ;}
		reverse_iterator	operator-(difference_type n) const	{ return (reverse_iterator(iter + n)) ;}
		reverse_iterator&	operator++()						{ (--iter); return *this; }
		reverse_iterator	operator++(int)						{ reverse_iterator temp(*this); --iter; return temp; }
		reverse_iterator&	operator--()						{ (++iter); return *this; }
		reverse_iterator	operator--(int)						{ reverse_iterator temp(*this); ++iter; return temp; }
		reverse_iterator&	operator+=(difference_type n)		{ iter -=n; return (*this); }
		reverse_iterator&	operator-=(difference_type n)		{ iter +=n; return (*this); }
		pointer				operator->() const					{ return &(operator*()); }
		reference			operator[](difference_type n) const	{ return (*(*this + n)); }
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() == rhs.base();
	};
	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() != rhs.base();
	};
	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() > rhs.base();
	};
	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() >= rhs.base();
	};
	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() < rhs.base();
	};
	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() <= rhs.base();
	};
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (rhs.base() - lhs.base());};
	
	template <class Iterator>
	reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { 
		return reverse_iterator<Iterator>(rev_it.base() - n); 
	};
}
#endif
