#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {
    template <typename T, typename Container = vector<T> >
    class stack {
	public:
        typedef T           value_type;
        typedef std::size_t size_type;
        typedef Container   container_type;
	protected:
        container_type _cont;
	public:
		//Конструкторы
		explicit stack (const container_type& cont = container_type()) : _cont(cont) {}
	    stack(const stack& cont) {
			*this = cont;
		}
		//Деструктор
	    ~stack() {};
	    //Реляционные операторы
	    stack   &operator=(const stack &other) {
			if (this != &other)
		    	_cont = other._cont;
		    return (*this);
	    }
	    template <typename A, typename cont>
	    friend  bool operator==(const stack<A, cont>& lhs, const stack<A, cont>& rhs);
		template <typename A, typename cont>
	    friend  bool operator>=(const stack<A, cont>& lhs, const stack<A, cont>& rhs);
		template <typename A, typename cont>
	    friend  bool operator<=(const stack<A, cont>& lhs, const stack<A, cont>& rhs);
		template <typename A, typename cont>
	    friend  bool operator!=(const stack<A, cont>& lhs, const stack<A, cont>& rhs);
		template <typename A, typename cont>
	    friend  bool operator>(const stack<A, cont>& lhs, const stack<A, cont>& rhs);
		template <typename A, typename cont>
	    friend  bool operator<(const stack<A, cont>& lhs, const stack<A, cont>& rhs);

		//Функции
		bool				empty()	const				{ return _cont.empty(); }
		size_type			size() const				{ return _cont.size(); }
		const value_type	&top() const				{ return _cont.back(); }
		value_type			&top() 						{ return _cont.back(); }
		void				push(const value_type& val)	{ _cont.push_back(val); }
		void				pop()						{ _cont.pop_back(); }

    };
	//Реляционные операторы
	template <typename T, typename Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return (lhs._cont == rhs._cont);
	}
	template <typename T, typename Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return (lhs._cont >= rhs._cont);
	}
	template <typename T, typename Container>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return (lhs._cont <= rhs._cont);
	}
	template <typename T, typename Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return (lhs._cont > rhs._cont);
	}
	template <typename T, typename Container>
	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return (lhs._cont < rhs._cont);
	}
	template <typename T, typename Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return (lhs._cont != rhs._cont);
	}
}

#endif
