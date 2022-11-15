#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "pair.hpp"
# include "utils.hpp"
# include "iterator_traits.hpp"
# include "iterator.hpp"
# include "reverse_iterator.hpp"
# include <iostream>
# define BLACK_LIST  true
# define RED_LIST	false

namespace ft{

	template<typename T>
	struct Node {
	public:
		T				*value;
		Node			*left;
		Node    		*right;
		Node			*parent;
		bool 			color;
		bool			is_nil;
	private:
		Node(): value(NULL), left(0), right(0), parent(0), color(true), is_nil(true) {}

	public:
		Node(T *val, bool nil): value(val), left(0), right(0), parent(0), is_nil(nil) {
			color = nil ? BLACK_LIST : RED_LIST;
		}
		Node(const Node &other) {
			value = other.value;
			left = other.left;
			right = other.right;
			parent = other.parent;
			color = other.color;
			is_nil = other.is_nil;
		}
		Node	&operator=(const Node &other) {
			if (this != &other) {
				*value = *other.value;
				left = other.left;
				right = other.right;
				parent = other.parent;
				color = other.color;
				is_nil = other.is_nil;
			}
		}
		~Node() {}
	};
	///////////// ITERATORS
	template <typename value_type>
	class TreeIter: public ft::iterator<std::bidirectional_iterator_tag, value_type> {
	public:
		typedef ft::iterator<std::bidirectional_iterator_tag, value_type>	ancestor;
		typedef typename ancestor::pointer 									pointer;
		typedef typename ancestor::reference 								reference;
		typedef typename ancestor::difference_type 							difference_type;
		typedef ft::Node<typename ft::remove_const<value_type>::type >		*node_pointer;
	private:
		node_pointer ptr;

		node_pointer tree_min(node_pointer n) const {
			while(n->left != NULL && !n->left->is_nil)
				n = n->left;
			return n;
		}

		node_pointer tree_max(node_pointer n) const {
			while (!n->right->is_nil)
				n = n->right;
			return n;
		}
	public:
		TreeIter() {};
		TreeIter(node_pointer ptr): ptr(ptr) {};
		TreeIter(const TreeIter<typename ft::remove_const<value_type>::type > & other): ptr(other.base()) {};
		~TreeIter() {};

		TreeIter &operator=(const TreeIter &other) {
			if (this != &other)
				ptr = other.base();
			return *this;
		}
		node_pointer	base() const			{ return ptr; }
		reference		operator*() const		{ return *(ptr->value); }
		pointer			operator->() const		{ return ptr->value;}

		TreeIter	&operator++() {
			if (ptr->right && ptr->right->is_nil == false)
				ptr = tree_min(ptr->right);
			else if (!ptr->right->parent || (ptr->value == tree_max(ptr->right->parent)->value))
				ptr = ptr->right;
			else {
				node_pointer y = ptr->parent;
				while (y != NULL && ptr == y->right) {
					ptr = y;
					y = y->parent;
				}
				ptr = y;
			}
			return *this;
		}
		TreeIter	operator++(int) {
			TreeIter tmp(*this);
			++(*this);
			return (tmp);
		}
		TreeIter	&operator--() {
			if (ptr->is_nil && ptr->parent)
				ptr = tree_max(ptr->parent);
			else if (ptr->left && ptr->left->is_nil == false)
				ptr = tree_max(ptr->left);
			else {
				node_pointer temp = ptr->parent;
				while (temp != NULL && ptr == temp->left) {
					ptr = temp;
					temp = ptr->parent;
				}
				ptr = temp;
			}
			return *this;
		}
		TreeIter	operator--(int) {
			TreeIter tmp(*this);
			if (ptr->is_nil && ptr->parent)
				ptr = tree_max(ptr->parent);
			else if (ptr->left && ptr->left->is_nil == false)
				ptr = tree_max(ptr->left);
			else {
				node_pointer p = ptr->parent;
				while (p != NULL && ptr == p->left) {
					ptr = p;
					p = p->parent;
				}
				ptr = p;
			}
			return tmp;
		}
		friend bool operator==(const TreeIter & lhs, const TreeIter & rhs){
			return (lhs.base() == rhs.base());
		}
		friend bool operator!=(const TreeIter & lhs, const TreeIter & rhs){
			return (lhs.base() != rhs.base());
		}
	};

	template<typename value, typename Compare = std::less<value>, typename Alloc = std::allocator<value> >
	class RBtree {
	public:
		typedef value													value_type; // pair
		typedef typename Alloc::template rebind<Node<value> >::other	alloc_node_type;
		typedef Alloc													allocator_type;
		typedef typename allocator_type::pointer						pointer;
		typedef	typename alloc_node_type::pointer 						node_pointer;
		typedef Compare													value_compare;
		typedef std::size_t												size_type;
		typedef TreeIter<value>											iterator;
		typedef TreeIter<const value>					 				const_iterator;
		typedef	ft::reverse_iterator<iterator>							reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;
	private:
		allocator_type	_alloc;
		alloc_node_type	_alloc_node;
		node_pointer	_root;
		node_pointer	_nil;
		size_type		_size;
		value_compare	_comp;

		//поменять детей
		//поменять родителей
		//поменять ссылки у родителей
		//поменять ссылки на родителей у детей

		void	swap_value(node_pointer src, node_pointer dest) {

			node_pointer parent_dest = dest->parent; //  Если рут или какой-то элемент надо проверить на рут
			node_pointer right_child_dest = dest->right; //правый ребенок источника назначения
			node_pointer left_child_dest = dest->left;  //левый ребенок источника назначения
			node_pointer parent_src = src->parent; // родитель источника
			node_pointer left_child_src = src->left; // левый сын источника
			node_pointer right_child_src = src->right; // правый сын источника
			if (parent_dest == NULL) // Если источник назначение я корень, обновляем корень
				_root = src;
			else if (dest == dest->parent->left)
				parent_dest->left = src; // иначе обновляем сына у родителя
			else
				parent_dest->right = src;
			src->parent = parent_dest; //обновляем родителя источника
			if (right_child_dest == src) //Если правый ребенок это ты сам, то
				src->right = dest;  // твоим правым сыном будет dest
			else { // иначе
				src->right = right_child_dest; //обновляем правого сына источника
				right_child_dest->parent = src; // и родителя правого сына
			}
			if (left_child_dest == src) //Если левый ребенок это ты сам, то
				src->left = dest; // твой левый сын дест
			else {
				src->left = left_child_dest; //обновляем левого сына источника
				left_child_dest->parent = src; // и родителя левого сына
			}
			if (parent_src == dest) //Если родитель это ты сам, то
				dest->parent = src; // твоим отцом будет источник
			else
				dest->parent = parent_src;  // иначе промежуточный узел
			if (right_child_src != _nil) {
				dest->right = right_child_src;
				right_child_src->parent = dest;
			}
			else
				dest->right = _nil;
			if (left_child_src != _nil) {
				dest->left = left_child_src;
				left_child_src->parent = dest;
			}
			else
				dest->left = _nil;
			std::swap(src->color, dest->color); // меняем цвета
		}

		void	swap_color(node_pointer elem1, node_pointer elem2) {
			bool	tmp;

			tmp = elem1->color;
			elem1->color = elem2->color;
			elem2->color = tmp;
		}

		node_pointer create_node(const value_type &val, node_pointer side, node_pointer parent) { //возможно лефт райт просто всегда нил ставить
			pointer ptr = _alloc.allocate(1);
			_alloc.construct(ptr, val);
			node_pointer new_node = _alloc_node.allocate(1);
			_alloc_node.construct(new_node, Node<value>(ptr, false));
			new_node->left = side;
			new_node->right = side;
			new_node->parent = parent;
			return new_node;
		}
		void	rotate_left(node_pointer node) {
			node_pointer temp = node->right;
			node->right = temp->left;
			temp->left->parent = node;
			temp->parent = node->parent;
			if (node->parent == NULL)
				_root = temp;
			else if (node->parent->left == node)
				node->parent->left = temp;
			else
				node->parent->right = temp;
			temp->left = node;
			node->parent = temp;
		}

		void	rotate_right(node_pointer node) {
			node_pointer temp = node->left;
			node->left = temp->right;
			temp->right->parent = node;
			temp->parent = node->parent;
			if (node->parent == NULL)
				_root = temp;
			else if (node == node->parent->left)
				node->parent->left = temp;
			else
				node->parent->right = temp;
			temp->right = node;
			node->parent = temp;
		}

		void fix_after_insert(node_pointer node){
			if (node != _root && node->parent->color == RED_LIST) {
				node_pointer uncle;
				if (node->parent->parent->left == node->parent)
					uncle = node->parent->parent->right;
				else
					uncle = node->parent->parent->left;
				if (uncle->color == RED_LIST) {
					node->parent->color = BLACK_LIST;
					uncle->color = BLACK_LIST;
					node->parent->parent->color = RED_LIST;
					node = node->parent->parent;
				}
				else if (node->parent->parent->left == node->parent) {
					if (node == node->parent->right) {
						node = node->parent;
						rotate_left(node);
					}
					node->parent->color = BLACK_LIST;
					node->parent->parent->color = RED_LIST;
					rotate_right(node->parent->parent);
				}
				else {
					if (node == node->parent->left) {
						node = node->parent;
						rotate_right(node);
					}
					node->parent->color = BLACK_LIST;
					node->parent->parent->color = RED_LIST;
					rotate_left(node->parent->parent);
				}
				return fix_after_insert(node);
			}
			_root->color = BLACK_LIST;
		}
	/////////////////// RBtree function
	public:
		explicit RBtree(const Compare &comp, const allocator_type& alloc = allocator_type()): _alloc(alloc), _alloc_node(alloc_node_type()),
																		 _root(NULL), _size(0), _comp(comp) {
			_nil = _alloc_node.allocate(1);
			pointer val = _alloc.allocate(1);
			_alloc.construct(val, value_type());
			_alloc_node.construct(_nil, Node<value>(val, true));
			_nil->parent = _root;
		}
		RBtree(const RBtree& src): _root(NULL), _size(0), _comp(src._comp)  {
			_nil = _alloc_node.allocate(1);
			pointer val = _alloc.allocate(1);
			_alloc.construct(val, value_type());
			_alloc_node.construct(_nil, Node<value>(val, true));
			_nil->parent = _root;
			*this = src;
		}
		RBtree& operator=(const RBtree &src){
			if (this == &src)
				return *this;
			this->_alloc = src._alloc;
			this->_alloc_node = src._alloc_node;
			this->_comp = src._comp;
			if (_root != NULL) {
				clear(_root);
			}
			insert(src.begin(),src.end());
			return *this;
		}

		~RBtree() {

			clear(_root);
			_alloc.destroy(_nil->value);
			_alloc.deallocate(_nil->value, 1);
			_alloc_node.destroy(_nil);
			_alloc_node.deallocate(_nil, 1);
		}


		void clear(node_pointer node) {
			if (!node || node == _nil )
				return;
			clear(node->left);
			clear(node->right);
			_alloc.destroy(node->value);
			_alloc.deallocate(node->value, 1);
			_alloc_node.destroy(node);
			_alloc_node.deallocate(node, 1);
			_size = 0;
			_root = NULL;
			_nil->parent = _root;
		}
		iterator				end()			{ return (iterator(_nil)); }
		iterator				begin()			{ return (iterator(_size == 0 ? iterator(_nil) : iterator(tree_min(_root)))); }
		const_iterator			end() const		{ return (const_iterator(_nil)); }
		const_iterator			begin() const	{ return (const_iterator(_size == 0 ? const_iterator(_nil) : const_iterator(tree_min(_root)))); }
		reverse_iterator		rbegin()		{ return (reverse_iterator(end())); }
		const_reverse_iterator	rbegin() const	{ return (const_reverse_iterator(end())); }
		reverse_iterator		rend()			{ return (reverse_iterator(begin())); }
		const_reverse_iterator	rend() const	{ return (const_reverse_iterator(begin()));}

		node_pointer	tree_min(node_pointer node) const {
			if (node && node->left != _nil)
				return tree_min(node->left);
			return node;
		}
		node_pointer	tree_max(node_pointer node) const {
			if (node && node->right != _nil)
				return tree_max(node->right);
			return node;
		}
		size_type	erase(const value_type &val) {
			node_pointer ptr = search(_root, val);
			if (ptr)
				erase(ptr);
			return ptr == NULL ? 0:1;
		}

		void	erase(iterator pos) {  //вернуть итератор
			node_pointer ptr = pos.base();
			if (ptr) {
				erase(ptr);
			}
		}
		void delete_elem(node_pointer elem) {  //удалить один элемент
			if (elem != _root && elem == elem->parent->left)
				elem->parent->left = _nil;
			else if (elem != _root)
				elem->parent->right = _nil;
			_alloc.destroy(elem->value);
			_alloc.deallocate(elem->value, 1);
			_alloc_node.destroy(elem);
			_alloc_node.deallocate(elem, 1);
		}

		void	left_repair(node_pointer elem) {
			// case 2
			if (elem->parent->right->color == RED_LIST) {
				swap_color(elem->parent, elem->parent->right);
				rotate_left(elem->parent);
			}
			// case 3
			if (elem->parent->color == BLACK_LIST && elem->parent->right->color == BLACK_LIST
				&& elem->parent->right->right->color == BLACK_LIST && elem->parent->right->left->color == BLACK_LIST) {

				elem->parent->right->color = RED_LIST;
				return repair_tree(elem->parent); // переход к случаю 1
			}
			// case 4
			if (elem->parent->color == RED_LIST && elem->parent->right->color == BLACK_LIST
				&& elem->parent->right->right->color == BLACK_LIST && elem->parent->right->left->color == BLACK_LIST) {
				swap_color(elem->parent, elem->parent->right);
				return;
			}
			// case 5
			if (elem->parent->right->color == BLACK_LIST && elem->parent->right->right->color == BLACK_LIST
				&& elem->parent->right->left->color == RED_LIST) {
				swap_color(elem->parent->right, elem->parent->right->left);
				rotate_right(elem->parent->right);
			}
			//case 6
			if (elem->parent->right->color == BLACK_LIST && elem->parent->right->right->color == RED_LIST) {
				swap_color(elem->parent, elem->parent->right);
				elem->parent->right->right->color = BLACK_LIST;
				rotate_left(elem->parent);
			}
		}

		void	right_repair(node_pointer elem) {
			// case 2
			if (elem->parent->left->color == RED_LIST) {
				swap_color(elem->parent, elem->parent->left);
				rotate_right(elem->parent);
			}
			// case 3
			if (elem->parent->color == BLACK_LIST && elem->parent->left->color == BLACK_LIST
				&& elem->parent->left->left->color == BLACK_LIST && elem->parent->left->right->color == BLACK_LIST) {
				elem->parent->left->color = RED_LIST;
				return repair_tree(elem->parent); // переход к случаю 1
			}
			// case 4
			if (elem->parent->color == RED_LIST && elem->parent->left->color == BLACK_LIST
				&& elem->parent->left->left->color == BLACK_LIST && elem->parent->left->right->color == BLACK_LIST) {
				swap_color(elem->parent, elem->parent->left);
				return;
			}
			// case 5
			if (elem->parent->left->color == BLACK_LIST && elem->parent->left->left->color == BLACK_LIST
				&& elem->parent->left->right->color == RED_LIST) {
				swap_color(elem->parent->left, elem->parent->left->right);
				rotate_left(elem->parent->left);
			}
			//case 6
			if (elem->parent->left->color == BLACK_LIST && elem->parent->left->left->color == RED_LIST) {
				swap_color(elem->parent, elem->parent->left);
				elem->parent->left->left->color = BLACK_LIST;
				rotate_right(elem->parent);
			}
		}
		void repair_tree(node_pointer elem) {
			// case 1
			if (elem == _root) {
				elem->color = BLACK_LIST;
				return;
			}
			if (elem->parent->left == elem)//элемент левый потомок
				left_repair(elem);
			else //элемент левый потомок
				right_repair(elem);
		}
		void	erase(node_pointer elem) {
			node_pointer src;
			if (elem->left != _nil && elem->right != _nil) // если два ребенка
			{
				src = tree_max(elem->left);
				swap_value(src, elem);
			}
			if (elem->right == _nil && elem->left == _nil) {
				if (elem->color == RED_LIST) //красный элемент без листьев
					delete_elem(elem);
				else {//  черный элемент без листьев
					repair_tree(elem);
					delete_elem(elem);
				}
			}
			else { // черный элемент с правым либо левым красным потомком
				if (elem->right != _nil) // !!!!!!!!!!!!! Потомок всегда правый если элем не корень
					src = elem->right;
				else
					src = elem->left;
				swap_value(src, elem);
				delete_elem(elem);
			}
			--_size;
			if (_size == 0)
				_root = NULL;
			_nil->parent = _root;
		}
		iterator	find(const value_type & val) {
			node_pointer temp = search(_root, val);
			if (temp)
				return iterator(temp);
			else
				return end();
		}
		const_iterator	find(const value_type & val) const {
			node_pointer temp = search(_root, val);
			if (temp)
				return const_iterator(temp);
			else
				return end();
		}
		size_type count(const value_type& val) const{
			return (find(val) != _nil);
		}
		node_pointer search(node_pointer ptr, const value_type& val) const {
			if (ptr == NULL || ptr == _nil)
				return NULL;
			if (_comp(*ptr->value, val))
				return search(ptr->right, val);
			if (_comp(val, *ptr->value))
				return search(ptr->left, val);
			return ptr;
		}
		node_pointer search_insert(node_pointer ptr, const value_type& val) {
			if (ptr == NULL || ptr == _nil)
				return NULL;
			if (_comp(*ptr->value, val)) {
				if (ptr->right != _nil)
					return search_insert(ptr->right, val);
				ptr->right = create_node(val, _nil, ptr);
				return ptr->right;
			}
			else  {
				if (ptr->left != _nil)
					return search_insert(ptr->left, val);
				ptr->left = create_node(val, _nil, ptr);
				return ptr->left;
			}
		}
		template <class InputIterator>
		void insert(typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last) {
			for (; first != last; ++first) {
				insert_node(*first);
				_nil->parent = _root;
			}
		}
		ft::pair<iterator, bool> insert(value_type const &val) {
			node_pointer new_node = search(_root, val);
			if (new_node)
				return ft::make_pair(iterator(new_node), false);
			new_node = insert_node(val);
			_nil->parent = _root;
			ft::pair<iterator, bool> res(iterator(new_node), true);
			return res;
		}
		node_pointer insert_node(const value_type& val) {
			if (_root == NULL) {
				_root = create_node(val, _nil, NULL);
				_root->color = BLACK_LIST;
				_nil->parent = _root;
				++_size;
				return _root;
			}
			else {
				node_pointer new_node = search_insert(_root, val);
				if (new_node != _root && new_node->parent != _root)
					fix_after_insert(new_node);
				++_size;
				_nil->parent = _root;
				return new_node;
			}
		}
		const_iterator lower_bound(const value_type& k) const{
//			if (ptr == NULL || ptr == _nil)
//				return NULL;
//			if (_comp(*ptr->value, val))
//				return search(ptr->right, val);
//			if (_comp(val, *ptr->value))
//				return search(ptr->left, val);
//
//
			node_pointer	start = _root;
			node_pointer	res = NULL;
			while (start != _nil) {
				if (_comp(k, *(start->value))) {
					res = start;
					start = start->left;
				}
				else if (_comp(*(start->value), k))
					start = start->right;
				else
					return start;
			}
			return res == NULL ? _nil : res;
		}
		iterator lower_bound(const value_type& k) {
			node_pointer	start = _root;
			node_pointer	res = NULL;
			while (start != NULL && start != _nil) {
				if (_comp(k, *(start->value))) {
					res = start;
					start = start->left;
				}
				else if (_comp(*(start->value), k))
					start = start->right;
				else
					return start;
			}
			return res == NULL ? _nil : res;
		}

		iterator upper_bound(const value_type& k) {
			node_pointer	start = _root;
			node_pointer	res = NULL;
			while (start != _nil) {
				if (_comp(k, *(start->value))) {
					res = start;
					start = start->left;
				}
				else if (_comp(*(start->value), k))
					start = start->right;
				else
				{
					if (start->right != _nil)
						res = tree_min(start->right);
					return (res == NULL ? _nil: res);
				}
			}
			return res == NULL ? _nil : res;
		}

		const_iterator upper_bound(const value_type& k) const {
			node_pointer	start = _root;
			node_pointer	res = NULL;
			while (start != _nil) {
				if (_comp(k, *(start->value))) {
					res = start;
					start = start->left;
				}
				else if (_comp(*(start->value), k))
					start = start->right;
				else
				{
					if (start->right != _nil)
						res = tree_min(start->right);
					return (res ? res : _nil);
				}
			}
			return res == NULL ? _nil : res;
		}
		ft::pair<iterator, iterator> equal_range(const value_type &k){
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}
		ft::pair<const_iterator, const_iterator> equal_range(const value_type &k) const {
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}
		void	swap(RBtree &x) {
			std::swap(this->_alloc, x._alloc);
			std::swap(this->_alloc_node, x._alloc_node);
			std::swap(this->_root, x._root);
			std::swap(this->_nil, x._nil);
			std::swap(this->_size, x._size);
			std::swap(this->_comp, x._comp);
		}

		bool			empty() const			{ return _size == 0; }
		node_pointer	get_root() const		{ return _root; }
		node_pointer	get_allocator() const	{ return _alloc; }
		node_pointer	get_nil() const			{ return _nil; }
		size_type		size() const			{ return _size; }
		size_type		max_size() const		{ return _alloc.max_size(); }
		value_compare	value_comp() const		{ return  _comp; }
	};
	template<class Value, class Compare, class Alloc>
	void swap(const  RBtree<Value, Compare, Alloc>& lhs, const  RBtree<Value, Compare, Alloc>& rhs){
		lhs.swap(rhs);
	}
}

#endif