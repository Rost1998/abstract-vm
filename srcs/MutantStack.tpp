//
// Created by Rostislav TULCHIY on 5/17/18.
//

#include "../include/MutantStack.hpp"

/////////////////////////// _______ MutantStack COPLIEN ______ ////////

template <class T>
MutantStack<T>::MutantStack()
{}

template <class T>
MutantStack<T>::MutantStack(MutantStack<T> const &copy)
{ *this = copy; }

template <class T>
MutantStack<T>::~MutantStack()
{}

template <class T>
MutantStack<T> &	MutantStack<T>::operator = (MutantStack<T> const & r)
{ this->c = r.c; return *this; }


/////////////////////////// _______ MutantStack::iterator COPLIEN ______ ////////

template <class T>
MutantStack<T>::iterator::iterator()
{}

template <class T>
MutantStack<T>::iterator::iterator(iterator const &copy)
{ *this = copy; }

template <class T>
MutantStack<T>::iterator::~iterator()
{}

template <class T>
typename MutantStack<T>::iterator &	MutantStack<T>::iterator::operator = (typename MutantStack<T>::iterator const & r)
{
	std::deque<T>::iterator::operator=(r);
	return *this;
}

// addition overload = for copy from c.begin()
template <class T>
typename MutantStack<T>::iterator &	MutantStack<T>::iterator::operator = (typename std::deque<T>::iterator const & r)
{
	std::deque<T>::iterator::operator=(r);
	return *this;
}


/////////////////////////// _______ MutantStack::iterator GENERAL ______ ////////

template <class T>
typename MutantStack<T>::iterator	MutantStack<T>::begin()
{
	MutantStack<T>::iterator	it;

	it = this->c.begin();
	return it;
}

template <class T>
typename MutantStack<T>::iterator	MutantStack<T>::end()
{
	MutantStack<T>::iterator	it;

	it = this->c.end();
	return it;
}
