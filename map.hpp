#ifndef MAP_HPP
#define MAP_HPP

#include "RBtree.hpp"


namespace ft {

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef pair<const Key, T>							value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef std::ptrdiff_t								difference_type;
		typedef	std::size_t									size_type;

		class value_compare {
			key_compare _compare;

		public:
			value_compare(const key_compare & compare) : _compare(compare) {}

			bool operator()(const value_type & x, const value_type & y) const{
				return (_compare(x.first, y.first));
			}
		};

		typedef RBtree<value_type, value_compare, allocator_type>	tree_type;
		typedef typename tree_type::iterator						iterator;
		typedef typename tree_type::const_iterator					const_iterator;
		typedef typename tree_type::reverse_iterator				reverse_iterator;
		typedef typename tree_type::const_reverse_iterator			const_reverse_iterator;

	private:
			tree_type		_tree;
			key_compare		_compare;

	public:
		map(const key_compare& comp = key_compare(),  const allocator_type& alloc = allocator_type()):
				_tree(tree_type(comp, alloc)), _compare(comp) {}
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()): _tree(tree_type(comp, alloc)), _compare(comp) {
			_tree.insert(first, last);
		}
		map	&operator=(const map &x) {
			if (this != &x) {
				_tree = x._tree;
				_compare = x.key_comp();
			}
			return (*this);
		}
		~map() {}

		mapped_type& operator[] (const key_type& k) {
			return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
		}

		ft::pair<iterator, bool> insert (const value_type& val) {
			return _tree.insert(val);
		}

		iterator insert(iterator position, const value_type& val) {
			(void)position;
			return (_tree.insert(val)).first;
		}

		template <class InputIterator>
		void insert (typename ft::enable_if< !is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last) {
			_tree.insert(first, last);
		};
		void erase(iterator position) {
			_tree.erase(position);
		}
		size_type erase(const key_type& key) {
			return _tree.erase(ft::make_pair(key, mapped_type()));
		}
		void erase (iterator first, iterator last) {
			while (first != last) {
				iterator temp = ++first;
				first--;
				erase(first);
				first = temp;
			}
		}
		void	swap(map& x) {
			std::swap(_compare, x._compare);
				_tree.swap(x._tree);
		}
		iterator		lower_bound(const key_type& k)			{ return _tree.lower_bound(ft::make_pair(k, mapped_type()));}
		const_iterator	lower_bound(const key_type& k) const	{ return _tree.lower_bound(ft::make_pair(k, mapped_type()));}
		iterator		upper_bound(const key_type& k)			{ return _tree.upper_bound(ft::make_pair(k, mapped_type()));}
		const_iterator	upper_bound(const key_type& k) const	{ return _tree.upper_bound(ft::make_pair(k, mapped_type()));}
		allocator_type	get_allocator() const					{ return allocator_type(); }
		size_type		size() const							{ return _tree.size(); }
		size_type		max_size() const						{ return _tree.max_size(); }
		bool			empty() const							{ return _tree.empty(); }
		value_compare	value_comp() const						{ return _tree.value_comp(); }
		key_compare		key_comp() const						{ return _compare; }
		iterator		find(const key_type& k)					{ return _tree.find(ft::make_pair(k, mapped_type())); }
		const_iterator 	find(const key_type& k) const			{ return _tree.find(ft::make_pair(k, mapped_type())); }
		size_type		count (const key_type& k) const			{ return _tree.count(ft::make_pair(k, mapped_type())); }
		pair<iterator,iterator>	equal_range(const key_type& k)	{
			return _tree.equal_range(ft::make_pair(k, mapped_type()));
		}
		pair<const_iterator,const_iterator>	equal_range(const key_type& k) const {
			return _tree.equal_range(ft::make_pair(k, mapped_type()));
		}


		iterator				begin()			{ return _tree.begin(); }
		iterator				end()			{ return _tree.end(); }
		const_iterator			begin() const	{ return _tree.begin(); }
		const_iterator			end() const		{ return _tree.end(); }
		reverse_iterator		rbegin()		{ return _tree.rbegin(); }
		const_reverse_iterator	rbegin() const	{ return _tree.rbegin(); }
		reverse_iterator		rend()			{ return _tree.rend(); }
		const_reverse_iterator	rend() const	{ return _tree.rend(); }

		void clear() {
			_tree.clear(_tree.get_root());
		}
	};

	template< class Key, class T, class compare, class alloc >
	bool operator==( const ft::map<Key,T,compare,alloc>& lhs, const ft::map<Key,T,compare,alloc>& rhs ) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(rhs == lhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return rhs < lhs;
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs > rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	}
}

#endif
