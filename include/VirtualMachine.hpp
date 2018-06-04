//
// Created by Rostislav TULCHIY on 5/31/18.
//

#ifndef ABSTRACT_VM_VIRTUALMACHINE_HPP
#define ABSTRACT_VM_VIRTUALMACHINE_HPP

#include <map>
#include <regex>
#include "IOperand.hpp"
#include "MutantStack.hpp"

typedef std::pair<std::string,std::string> cmd_parsed; // first - type; second - value

class VirtualMachine;
typedef void (VirtualMachine::*cmd)(cmd_parsed, int);

class VirtualMachine
{
private:
	MutantStack<IOperand const *>			_stack;
	std::map<std::string, cmd>				_cmd;
	std::deque<std::pair<cmd, cmd_parsed>>	_queue;

	void			_del_elem();
	eOperandType	_str_to_type(std::string, int line);
	bool			_findCmd(std::string input);
	void			_recursivePrint(std::deque<IOperand const *>::iterator it);

	void			_push(cmd_parsed parsed, int line);
	void			_pop(cmd_parsed parsed, int line);
	void			_dump(cmd_parsed parsed, int line);
	void			_assert(cmd_parsed parsed, int line);
	void			_add(cmd_parsed parsed, int line);
	void			_sub(cmd_parsed parsed, int line);
	void			_mul(cmd_parsed parsed, int line);
	void			_div(cmd_parsed parsed, int line);
	void			_mod(cmd_parsed parsed, int line);
	void			_print(cmd_parsed parsed, int line);
	void			_exit(cmd_parsed parsed, int line);

public:
	VirtualMachine();
	VirtualMachine(VirtualMachine const & copy);
	~VirtualMachine();

		// __________ EXCEPTIONS _________
		class file_not_open : public std::exception
		{
		public:
			const char *	what() const noexcept override;
		};

		class unknown_cmd : public std::exception
		{
		private:
			int 	_line;
		public:
			unknown_cmd();
			unknown_cmd(int line);
			unknown_cmd(unknown_cmd const & copy);
			~unknown_cmd();
			const char *	what() const noexcept override;
			int 			getLine() const;
			unknown_cmd &	operator = (unknown_cmd const & r);
		};

		class assert_false : public std::exception
		{
		private:
			int 	_line;
		public:
			assert_false();
			assert_false(int line);
			assert_false(assert_false const & copy);
			~assert_false();
			const char *	what() const noexcept override;
			int 			getLine() const;
			assert_false &	operator = (assert_false const & r);
		};

		class not_enough_operands : public std::exception
		{
		private:
			int 	_line;
		public:
			not_enough_operands();
			not_enough_operands(int line);
			not_enough_operands(not_enough_operands const & copy);
			~not_enough_operands();
			const char *			what() const noexcept override;
			int 					getLine() const;
			not_enough_operands &	operator = (not_enough_operands const & r);
		};

		class execution_impossible : public std::exception
		{
		private:
			int 	_line;
		public:
			execution_impossible();
			execution_impossible(int line);
			execution_impossible(execution_impossible const & copy);
			~execution_impossible();
			const char *			what() const noexcept override;
			int 					getLine() const;
			execution_impossible &	operator = (execution_impossible const & r);
		};

		class unexpected_eof : public std::exception
		{
		private:
			int 	_line;
		public:
			unexpected_eof();
			unexpected_eof(int line);
			unexpected_eof(unexpected_eof const & copy);
			~unexpected_eof();
			const char *		what() const noexcept override;
			int 				getLine() const;
			unexpected_eof &	operator = (unexpected_eof const & r);
		};

	void				readCmds(); // from stdin
	void				readCmds(std::string filename); // from file
	void				run();

	// overload
	VirtualMachine &	operator = (VirtualMachine const & r);
};

#endif //ABSTRACT_VM_VIRTUALMACHINE_HPP
