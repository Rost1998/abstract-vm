//
// Created by Rostislav TULCHIY on 5/17/18.
//

#include <string>
#include "../include/Operand.hpp"

/////////////////////////// _______ Operand COPLIEN ______ ////////

template <class T>
Operand<T>::Operand()
{}

template <class T>
Operand<T>::Operand(T value, eOperandType type, int prec)
		: _value(value),
		  _type(type),
		  _prec(prec)
{ _str_value = std::to_string(value); }

template <class T>
Operand<T>::Operand(Operand<T> const &copy)
{ *this = copy; }

template <class T>
Operand<T>::~Operand()
{}

template <class T>
Operand<T> &	Operand<T>::operator = (Operand<T> const & r)
{
	_value = r.getValue();
	return *this;
}


/////////////////////////// _______ Operand EXCEPTIONS ______ ////////

template <class T>
const char *		Operand<T>::mod_with_floating_point::what() const noexcept
{ return "mod uses only with integers"; }

template <class T>
const char *		Operand<T>::division_by_zero::what() const noexcept
{ return "division by zero"; }


/////////////////////////// _______ Operand GENERAL ______ ////////

template <class T>
int					Operand<T>::getPrecision() const
{ return _prec; }

template <class T>
eOperandType		Operand<T>::getType() const
{ return _type; }

template <class T>
T const &			Operand<T>::getValue() const
{ return _value; }

template <class T>
std::string const &	Operand<T>::toString() const
{ return _str_value; }


/////////////////////////// _______ Operand OVERLOADS ______ ////////

template <class T>
IOperand const *	Operand<T>::operator + (IOperand const & r) const
{
	IOperand const *	result_elem;
	OperandFactory		factory;
	double				result;

	result = std::stod(toString()) + std::stod(r.toString());
	if (getType() > r.getType())
		result_elem = factory.createOperand(getType(), std::to_string(result));
	else
		result_elem = factory.createOperand(r.getType(), std::to_string(result));
	return result_elem;
}

template <class T>
IOperand const *	Operand<T>::operator - (IOperand const & r) const
{
	IOperand const *	result_elem;
	OperandFactory		factory;
	double				result;

	result = std::stod(toString()) - std::stod(r.toString());
	if (getType() > r.getType())
		result_elem = factory.createOperand(getType(), std::to_string(result));
	else
		result_elem = factory.createOperand(r.getType(), std::to_string(result));
	return result_elem;
}

template <class T>
IOperand const *	Operand<T>::operator * (IOperand const & r) const
{
	IOperand const *	result_elem;
	OperandFactory		factory;
	double				result;

	result = std::stod(toString()) * std::stod(r.toString());
	if (getType() > r.getType())
		result_elem = factory.createOperand(getType(), std::to_string(result));
	else
		result_elem = factory.createOperand(r.getType(), std::to_string(result));
	return result_elem;
}

template <class T>
IOperand const *	Operand<T>::operator / (IOperand const & r) const
{
	IOperand const *	result_elem;
	OperandFactory		factory;
	double				result;

	if (!std::stod(r.toString()))
		throw Operand<T>::division_by_zero();

	result = std::stod(toString()) / std::stod(r.toString());
	if (getType() > r.getType())
		result_elem = factory.createOperand(getType(), std::to_string(result));
	else
		result_elem = factory.createOperand(r.getType(), std::to_string(result));
	return result_elem;
}

template <class T>
IOperand const *	Operand<T>::operator % (IOperand const & r) const
{
	IOperand const *	result_elem;
	OperandFactory		factory;
	intmax_t			result;

	if (getType() == t_float || getType() == t_double
			|| r.getType() == t_float || r.getType() == t_double)
		throw Operand<T>::mod_with_floating_point();
	if (!std::stod(r.toString()))
		throw Operand<T>::division_by_zero();

	result = std::stoll(toString()) % std::stoll(r.toString());
	if (getType() > r.getType())
		result_elem = factory.createOperand(getType(), std::to_string(result));
	else
		result_elem = factory.createOperand(r.getType(), std::to_string(result));
	return result_elem;
}
