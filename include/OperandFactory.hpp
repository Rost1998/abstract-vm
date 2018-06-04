//
// Created by Rostislav TULCHIY on 5/18/18.
//

#ifndef ABSTRACT_VM_OPERANDFACTORY_HPP
#define ABSTRACT_VM_OPERANDFACTORY_HPP

#include <vector>
#include "IOperand.hpp"

class OperandFactory;
typedef IOperand const *	(OperandFactory::*factoryMethod)(std::string const &) const;

class OperandFactory
{
private:
	std::vector<factoryMethod>	methods;

	IOperand const *	createInt8(std::string const & value) const;
	IOperand const *	createInt16(std::string const & value) const;
	IOperand const *	createInt32(std::string const & value) const;
	IOperand const *	createFloat(std::string const & value) const;
	IOperand const *	createDouble(std::string const & value) const;

public:
	OperandFactory();
	OperandFactory(OperandFactory const &copy);
	~OperandFactory();

	// EXCEPTIONS
	class overflow : public std::out_of_range
	{
	public:
		overflow();
		const char *	what() const noexcept override;
	};

	IOperand const *	createOperand(eOperandType type, std::string const & value) const;

	// overload
	OperandFactory &	operator = (OperandFactory const & r);
};

#endif //ABSTRACT_VM_OPERANDFACTORY_HPP
