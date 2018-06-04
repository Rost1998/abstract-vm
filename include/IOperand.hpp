//
// Created by Rostislav TULCHIY on 5/17/18.
//

#ifndef ABSTRACT_VM_IOPERAND_HPP
#define ABSTRACT_VM_IOPERAND_HPP

#include <string>

enum eOperandType
{
	t_int8,
	t_int16,
	t_int32,
	t_float,
	t_double
};

class IOperand
{
public:
	virtual int				getPrecision(void) const = 0; // Precision of the type of the instance
	virtual eOperandType	getType(void) const = 0; // Type of the instance

	virtual IOperand const * operator + (IOperand const & r) const = 0; // Sum
	virtual IOperand const * operator - (IOperand const & r) const = 0; // Difference
	virtual IOperand const * operator * (IOperand const & r) const = 0; // Product
	virtual IOperand const * operator / (IOperand const & r) const = 0; // Quotient
	virtual IOperand const * operator % (IOperand const & r) const = 0; // Modulo

	virtual std::string const &	toString(void) const = 0; // String representation of the instance

	virtual ~IOperand(void) {}
};

#endif //ABSTRACT_VM_IOPERAND_HPP
