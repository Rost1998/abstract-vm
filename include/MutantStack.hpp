//
// Created by Rostislav TULCHIY on 5/17/18.
//

#ifndef ABSTRACT_VM_MUTANTSTACK_HPP
#define ABSTRACT_VM_MUTANTSTACK_HPP

#include <stack>

//
// class for standard container stack with iterator
//

template <class T>
class MutantStack : public std::stack<T>
{
public:
	MutantStack();
	MutantStack(MutantStack const &copy);
	~MutantStack();

		class iterator : public std::deque<T>::iterator
		{
		public:
			iterator();
			iterator(iterator const & copy);
			~iterator();

			// overloads
			iterator &	operator = (iterator const & r);
			// addition overload = for copy from c.begin()
			iterator &	operator = (typename std::deque<T>::iterator const & r);
		};

	// for iterator
	iterator	begin();
	iterator	end();

	// overload
	MutantStack &	operator = (MutantStack const & r);
};

#include "../srcs/MutantStack.tpp"

#endif //ABSTRACT_VM_MUTANTSTACK_HPP
