//
// Created by Rostislav TULCHIY on 5/17/18.
//

#ifndef ABSTRACT_VM_OPERAND_HPP
#define ABSTRACT_VM_OPERAND_HPP

#include "IOperand.hpp"

template <class T>
class Operand : public IOperand
{
private:
	T				_value;
	std::string		_str_value;
	eOperandType	_type;
	int				_prec;

public:
	Operand();
	Operand(T value, eOperandType type, int prec);
	Operand(Operand const &copy);
	~Operand();

		class mod_with_floating_point : public std::exception
		{
		public:
			const char *	what() const noexcept;
		};

		class division_by_zero : public std::exception
		{
		public:
			const char *	what() const noexcept;
		};

	int					getPrecision(void) const override;
	eOperandType		getType(void) const override;
	std::string const &	toString(void) const override;

	T const &			getValue(void) const;

	// overload
	Operand &	operator = (Operand const & r);
	IOperand const * operator + (IOperand const & r) const override; // Sum
	IOperand const * operator - (IOperand const & r) const override; // Difference
	IOperand const * operator * (IOperand const & r) const override; // Product
	IOperand const * operator / (IOperand const & r) const override; // Quotient
	IOperand const * operator % (IOperand const & r) const override; // Modulo
};

#include "../srcs/Operand.tpp"

#endif //ABSTRACT_VM_OPERAND_HPP
