#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "reverse_iterator.hpp"
# include "iterator.hpp"
# include "pair.hpp"
# include "utils.hpp"

namespace ft {
	
	template<typename T, class Allocator = std::allocator<T> > class vector {
	class VecIter;
	class VecIter_const;
	public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::reference			&reference;
		typedef typename allocator_type::const_reference 	&const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef VecIter										iterator;
		typedef VecIter_const								const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;
		pointer			_begin;

		class VecIter: public ft::iterator<std::random_access_iterator_tag, value_type> {
		public:
			typedef ft::iterator<std::random_access_iterator_tag, value_type>	ancestor;
			typedef	pointer														iterator_type;
			typedef typename ancestor::pointer									pointer;
			typedef typename ancestor::reference								reference;
			typedef typename ancestor::difference_type							difference_type;
		private:
			pointer ptr;
			template <typename, typename> friend class vector;
			VecIter(pointer x): ptr(x) {};
		public:
			VecIter() {};
			VecIter(const VecIter &other): ptr(other.base()) {};
			~VecIter() {};
			
			VecIter &operator=(const VecIter &other) {
				if (this != &other)
					ptr = other.base();
				return *this;
			}
			pointer	base() const								{ return ptr; }
			
			VecIter	&operator++()								{ ++ptr; return *this; }
			VecIter	operator++(int)								{ VecIter tmp(*this); ++ptr; return tmp; }
			VecIter	&operator--()								{ --ptr; return *this; }
			VecIter	operator--(int)								{ VecIter tmp(*this); --ptr; return tmp; }
			VecIter	operator+(const difference_type n) const	{ return ptr + n; }
			VecIter	operator-(const difference_type n) const	{ return ptr - n; }
			VecIter	&operator+=(const difference_type n)		{ ptr += n; return *this; }
			VecIter	&operator-=(const difference_type n)		{ ptr -= n; return *this; }

			pointer		operator->() const						{ return ptr; }
			reference	operator*() const						{ return *ptr; }
			reference	operator[](difference_type n) const 	{ return *(ptr + n); }

			friend difference_type	operator-(const VecIter &a, const VecIter &b)				{ return a.ptr - b.ptr; }
			friend VecIter			operator+(typename VecIter::difference_type n, VecIter &a)	{ a.ptr = a.ptr + n; return a.ptr; }

			friend bool operator>(const VecIter &lhs, const VecIter &rhs) {
				return lhs.ptr > rhs.ptr;
			}
			friend bool operator<(const VecIter &lhs, const VecIter &rhs) {
				return lhs.ptr < rhs.ptr;
			}
			friend bool operator==(const VecIter &lhs, const VecIter &rhs) {
				return lhs.ptr == rhs.ptr;
			}
			friend bool operator!=(const VecIter &lhs, const VecIter &rhs) {
				return lhs.ptr != rhs.ptr;
			}
			friend bool operator>=(const VecIter &lhs, const VecIter &rhs) {
				return lhs.ptr >= rhs.ptr;
			}
			friend bool operator<=(const VecIter &lhs, const VecIter &rhs) {
				return lhs.ptr <= rhs.ptr;
			}
		};

		class VecIter_const : public ft::iterator<std::random_access_iterator_tag, const value_type> {
		public:
			typedef ft::iterator<std::random_access_iterator_tag, const value_type>	ancestor;
			typedef	pointer															iterator_type;
			typedef typename ancestor::pointer										pointer;
			typedef typename ancestor::reference									reference;
			typedef typename ancestor::difference_type								difference_type;
		private:
			pointer ptr;
			template <typename, typename> friend class vector;

			VecIter_const(pointer x): ptr(x) {}
		public:
			VecIter_const() {};
			VecIter_const(const VecIter &other): ptr(other.base()) {}
			VecIter_const(const VecIter_const &other): ptr(other.base()) {}
			~VecIter_const() {}

			VecIter_const	&operator=(const VecIter_const &other) {
				if (this != &other)
					ptr = other.base();
				return *this;
			}
			pointer			base() const								{ return ptr; }

			VecIter_const	&operator++()								{ ++ptr; return *this; }
			VecIter_const	operator++(int)								{ VecIter_const tmp(*this); ++ptr; return tmp; }
			VecIter_const	&operator--()								{ --ptr; return *this; }
			VecIter_const	operator--(int)								{ VecIter_const tmp(*this); --ptr; return tmp; }
			VecIter_const	operator+(const difference_type n) const	{ return ptr + n; }
			VecIter_const	operator-(const difference_type n) const	{ return ptr - n; }
			VecIter_const	&operator+=(const difference_type n)		{ ptr += n; return *this; }
			VecIter_const	&operator-=(const difference_type n)		{ ptr -= n; return *this; }

			pointer		operator->() const							{ return ptr; }
			reference	operator*() const							{ return *ptr; }
			reference	operator[](difference_type n) const 		{ return *(ptr + n); }

			friend difference_type		operator-(const VecIter_const &a, const VecIter_const &b)				{ return a.ptr - b.ptr; }
			friend VecIter_const		operator+(typename VecIter_const::difference_type n, VecIter_const &a)	{ a.ptr = a.ptr + n; return a.ptr; }

			friend bool operator>(const VecIter_const &lhs, const VecIter_const &rhs) {
				return lhs.ptr > rhs.ptr;
			}
			friend bool operator<(const VecIter_const &lhs, const VecIter_const &rhs) {
				return lhs.ptr < rhs.ptr;
			}
			friend bool operator==(const VecIter_const &lhs, const VecIter_const &rhs) {
				return lhs.ptr == rhs.ptr;
			}
			friend bool operator!=(const VecIter_const &lhs, const VecIter_const &rhs) {
				return lhs.ptr != rhs.ptr;
			}
			friend bool operator>=(const VecIter_const &lhs, const VecIter_const &rhs) {
				return lhs.ptr >= rhs.ptr;
			}
			friend bool operator<=(const VecIter_const &lhs, const VecIter_const &rhs) {
				return lhs.ptr <= rhs.ptr;
			}
		};

	public:
		// CONSTRUCTORS-DESTRUCTORS
		explicit vector (const allocator_type &alloc = allocator_type()):
				_size(0), _capacity(0),  _alloc(alloc), _begin(0) {};
		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()): _size(n), _capacity(n), _alloc(alloc) {
			if (n > max_size())
				throw std::out_of_range("out of range");
			_begin = _alloc.allocate(n);
			for (size_type i = 0; i < n; ++i)
				_alloc.construct(_begin + i, val);
		};
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) : _alloc(alloc) {
			_size = _capacity = last - first;
			if (_size > max_size())
				throw std::out_of_range("out of range");
			_begin = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; ++i, ++first)
				_alloc.construct(_begin + i, *first);
		};
		vector(const vector& x): _size(0), _capacity(0) {
			*this = x;
		};
		~vector()
		{
			clear();
			if (_capacity != 0)
				_alloc.deallocate(_begin, _capacity);
		}
		// ITERATORS

		iterator	begin()				{ return iterator(_begin); }
		iterator	end()				{ return iterator(_begin + _size); }

		const_iterator	begin() const	{ return const_iterator(_begin); }
		const_iterator	end() const		{ return const_iterator(_begin + _size); }

		reverse_iterator	rbegin()	{ return reverse_iterator(end()); }
		reverse_iterator	rend()		{ return reverse_iterator(begin()); }

		const_reverse_iterator	rbegin()	const { return const_reverse_iterator(end()); }
		const_reverse_iterator	rend()		const { return const_reverse_iterator(begin()); }

		//OPERATORS
		vector  &operator=(const vector &other) {
			if (this != &other)
			{
				clear();
				_size = other._size;
				if (_capacity < _size)
				{
					if (_capacity != 0)
						_alloc.deallocate(_begin, _capacity);
					_capacity = _size;
					_begin = _alloc.allocate(_capacity);
				}
				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(_begin + i, other[i]);
			}
			return *this;
		};

		// CAPACITY:
		size_type size() const {
			return _size;
		};
		size_type max_size() const {
			return _alloc.max_size();
		};
		void resize(size_type n, value_type val = value_type ()) {
			if (n > max_size())
				throw std::length_error("vector");
			if (n < _size) {
				for (size_type i = n; i < _size; ++i)
					_alloc.destroy(_begin + i);
				_size = n;
			}
			else
				insert(end(), n - _size, val);
		};
		size_type capacity() const {
			return _capacity;
		};
		bool empty() const {
			return (_size == 0);
		};
		void reserve (size_type n) {
			if (n > max_size())
				throw std::length_error("length error");
			if (n > _capacity)
			{
				pointer new_vec;
				new_vec = _alloc.allocate(n);
				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(new_vec + i, *(_begin + i));
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_begin + i);
				if (_capacity != 0)
					_alloc.deallocate(_begin, _capacity);
				_begin = new_vec;
				_capacity = n;
			}
		};
		// ELEMENT ACCESS
		reference operator[](size_type n) {
			return (*(_begin + n));
		};
		const_reference operator[](size_type n) const {
			return (*(_begin + n));
		};
		reference		at(size_type n) {
			if (n >= _size)
				throw std::out_of_range("vector");
			return (*(_begin + n));
		};
		const_reference	at(size_type n) const {
			if (n >= _size)
				throw std::out_of_range("vector");
			return (*(_begin + n));
		};
		reference front() {
			return (*_begin);
		};
		const_reference front() const {
			return (*_begin);
		};
		reference back() {
			return (*(_begin + _size - 1));
		};
		const_reference back() const {
			return (*(_begin + _size - 1));
		};
		//MODIFIERS
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
			clear();
			_size = last - first;
			if (_size > _capacity) {
				_alloc.deallocate(_begin, _capacity);
				_begin = _alloc.allocate(_size);
				_capacity = _size;
			}
			for (size_type i = 0; i != _size; ++first, ++i)
				_alloc.construct(_begin + i, *first);
		};
		void assign (size_type n, const value_type & val) {
			clear();
			if (n > _capacity) {
				_alloc.deallocate(_begin, _capacity);
				_begin = _alloc.allocate(n);
				_capacity = n;
			}
			for (size_type i = 0; i < n; ++i)
				_alloc.construct(_begin + i, val);
			_size = n;
		}
		void push_back(const value_type& val) {
			if (_size + 1 <= _capacity)
				_alloc.construct(_begin + _size, val);
			else {
				reserve((_capacity == 0) ? 1 : _capacity * 2);
				_alloc.construct(_begin + _size, val);
			}
			++_size;
		};
		void pop_back () {
			_alloc.destroy(_begin + _size);
			--_size;
		};
		iterator insert(iterator position, const value_type& val) {
			size_type dist = position - begin();
			insert(position, 1, val);
			return (_begin + dist);
		}
		void insert(iterator position, size_type n, const value_type& val) {
			if (position < begin() || position > end())
				throw std::logic_error("vector");
			else if (n == 0)
				return ;
			else if (max_size() - _size < n)
				throw std::length_error("vector");
			size_type dist = position.base() - _begin;
			if (_size + n <= _capacity) {
				for (size_type i = _size; i > dist; --i) {
					_alloc.destroy(_begin + i + n - 1);
					_alloc.construct(_begin + i + n - 1, *(_begin + i - 1));
				}
				for (size_type i = 0; i < n; ++i) {
					_alloc.destroy(_begin + dist + i);
					_alloc.construct(_begin + dist + i, val);
				}
			}
			else {
				size_type tmp = _capacity * 2 >= _capacity + n ? _capacity * 2 : _capacity + n;
				pointer ptr = _alloc.allocate(tmp);
				size_type i = 0;
				for (; i < dist; ++i)
					_alloc.construct(ptr + i, *(_begin + i));
				for (size_type k = 0; k < n; ++k)
					_alloc.construct(ptr + dist + k, val);
				for (; i < _size; ++i)
					_alloc.construct(ptr + i + n, *(_begin + i));
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_begin + i);
				_alloc.deallocate(_begin, _capacity);
				_capacity = tmp;
				_begin = ptr;
			}
			_size += n;
		}
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
			if (position < begin() || position > end() || first > last)
				throw std::logic_error("vector");
			size_type n = last - first;
			size_type dist = position.base() - _begin;
			size_type tmp = _size + n <= _capacity? _capacity : _capacity * 2 >= _capacity + n ? _capacity * 2 : _capacity + n;
			pointer ptr = _alloc.allocate(tmp);
			size_type i = 0;
			size_type count = 0;
			try {
				for (; i < dist; ++i, ++count)
					_alloc.construct(ptr + i, *(_begin + i));
				for (size_type k = 0; k < n; ++k, ++count)
					_alloc.construct(ptr + dist + k, *(first + k));
				for (; i < _size; ++i, ++count)
					_alloc.construct(ptr + i + n, *(_begin + i));
			}
			catch (...) {
				for (size_type m = 0; m < count; ++m)
					_alloc.destroy(ptr + m);
				_alloc.deallocate(ptr, tmp);
				throw;
			}
			for (size_type i = 0; i < _size; ++i)
				_alloc.destroy(_begin + i);
			_alloc.deallocate(_begin, _capacity);
			_capacity = tmp;
			_begin = ptr;
			_size += n;
		}
		iterator erase (iterator position){
			_alloc.destroy(position.base());
			if (position != end() - 1) {
				pointer pos = position.base();
				size_type new_size = (_begin + _size - pos - 1) * sizeof(value_type);
				std::memmove(pos, pos + 1, new_size);
			}
			--_size;
			return iterator(position.base());
		}
		iterator erase (iterator first, iterator last) {
			if (first != last) {
				size_type n = last - first;
				size_type new_size = (_begin + _size - last) * sizeof(value_type);
				for (size_type i = 0; i < n; ++i) {
					_alloc.destroy(first.base() + i);
				}
				std::memmove(first.base(), last.base(), new_size);
				_size -= n;
			}
			return iterator(first.base());
		}
		void swap(vector& x) {
			if (this != &x) {
				std::swap(_alloc, x._alloc);
				std::swap(_begin, x._begin);
				std::swap(_capacity, x._capacity);
				std::swap(_size, x._size);
			}
		}
		void clear() {
			for (size_type i = 0; i < _size; ++i)
				_alloc.destroy(_begin + i);
			_size = 0;
		};
		//ALLOCATOR
		allocator_type get_allocator() const{
			return(_alloc);
		}
	};
	// Non-member function overloads
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		if (&x != &y)
			x.swap(y);
	}
	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};
	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(rhs < lhs);
	};
	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return rhs < lhs;
	};
	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}
}

#endif
