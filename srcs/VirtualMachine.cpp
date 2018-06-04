//
// Created by Rostislav TULCHIY on 5/31/18.
//

#include <iostream>
#include <fstream>
#include "../include/VirtualMachine.hpp"
#include "../include/OperandFactory.hpp"

/////////////////////////// _______ VirtualMachine COPLIEN ______ ////////

VirtualMachine::VirtualMachine()
		: _cmd({
			{"\\s*push\\s*(int(8|16|32)|float|double)\\s*\\(\\s*(-?\\d+.?\\d*)\\s*\\)\\s*(;.*|)", &VirtualMachine::_push},
			{"\\s*pop\\s*(;.*|)", &VirtualMachine::_pop},
			{"\\s*dump\\s*(;.*|)", &VirtualMachine::_dump},
			{"\\s*assert\\s*(int(8|16|32)|float|double)\\s*\\(\\s*(-?\\d+.?\\d*)\\s*\\)\\s*(;.*|)", &VirtualMachine::_assert},
			{"\\s*add\\s*(;.*|)", &VirtualMachine::_add},
			{"\\s*sub\\s*(;.*|)", &VirtualMachine::_sub},
			{"\\s*mul\\s*(;.*|)", &VirtualMachine::_mul},
			{"\\s*div\\s*(;.*|)", &VirtualMachine::_div},
			{"\\s*mod\\s*(;.*|)", &VirtualMachine::_mod},
			{"\\s*print\\s*(;.*|)", &VirtualMachine::_print},
			{"\\s*exit\\s*(;.*|)", &VirtualMachine::_exit}
			   })
{}

VirtualMachine::VirtualMachine(VirtualMachine const &copy)
{ *this = copy; }

VirtualMachine::~VirtualMachine()
{ for (IOperand const * elem : _stack) delete elem; }

VirtualMachine &	VirtualMachine::operator = (VirtualMachine const & r)
{
	_stack = r._stack;
	_queue = r._queue;
	_cmd = r._cmd;
	return *this;
}

//////////////////////////////////// ___ EXCEPTIONS ____ ////////////////////////
/////////////////////////// _______ VirtualMachine::file_not_open ______ ////////

const char *	VirtualMachine::file_not_open::what() const noexcept
{ return "file not open"; }

/////////////////////////// _______ VirtualMachine::uknown_cmd ______ ////////

VirtualMachine::unknown_cmd::unknown_cmd() : _line(0)
{}

VirtualMachine::unknown_cmd::unknown_cmd(int line) : _line(line)
{}

VirtualMachine::unknown_cmd::unknown_cmd(VirtualMachine::unknown_cmd const & copy)
{ *this = copy; }

VirtualMachine::unknown_cmd::~unknown_cmd()
{}

VirtualMachine::unknown_cmd &	VirtualMachine::unknown_cmd::operator = (VirtualMachine::unknown_cmd const & r)
{ _line = r._line; return *this; }

const char *	VirtualMachine::unknown_cmd::what() const noexcept
{ return "unknown command"; }

int 			VirtualMachine::unknown_cmd::getLine() const
{ return _line; }

/////////////////////////// _______ VirtualMachine::assert_false ______ ////////

VirtualMachine::assert_false::assert_false() : _line(0)
{}

VirtualMachine::assert_false::assert_false(int line) : _line(line)
{}

VirtualMachine::assert_false::assert_false(VirtualMachine::assert_false const & copy)
{ *this = copy; }

VirtualMachine::assert_false::~assert_false()
{}

VirtualMachine::assert_false &	VirtualMachine::assert_false::operator = (VirtualMachine::assert_false const & r)
{ _line = r._line; return *this; }

const char *	VirtualMachine::assert_false::what() const noexcept
{ return "assert false"; }

int 			VirtualMachine::assert_false::getLine() const
{ return _line; }

/////////////////////////// _______ VirtualMachine::not_enough_operands ______ ////////

VirtualMachine::not_enough_operands::not_enough_operands() : _line(0)
{}

VirtualMachine::not_enough_operands::not_enough_operands(int line) : _line(line)
{}

VirtualMachine::not_enough_operands::not_enough_operands(VirtualMachine::not_enough_operands const & copy)
{ *this = copy; }

VirtualMachine::not_enough_operands::~not_enough_operands()
{}

VirtualMachine::not_enough_operands &	VirtualMachine::not_enough_operands::operator = (VirtualMachine::not_enough_operands const & r)
{ _line = r._line; return *this; }

const char *	VirtualMachine::not_enough_operands::what() const noexcept
{ return "not enough operands"; }

int 			VirtualMachine::not_enough_operands::getLine() const
{ return _line; }

/////////////////////////// _______ VirtualMachine::execution_impossible ______ ////////

VirtualMachine::execution_impossible::execution_impossible() : _line(0)
{}

VirtualMachine::execution_impossible::execution_impossible(int line) : _line(line)
{}

VirtualMachine::execution_impossible::execution_impossible(VirtualMachine::execution_impossible const & copy)
{ *this = copy; }

VirtualMachine::execution_impossible::~execution_impossible()
{}

VirtualMachine::execution_impossible &	VirtualMachine::execution_impossible::operator = (VirtualMachine::execution_impossible const & r)
{ _line = r._line; return *this; }

const char *	VirtualMachine::execution_impossible::what() const noexcept
{ return "execution of command impossible"; }

int 			VirtualMachine::execution_impossible::getLine() const
{ return _line; }

/////////////////////////// _______ VirtualMachine::unexpected_eof ______ ////////

VirtualMachine::unexpected_eof::unexpected_eof() : _line(0)
{}

VirtualMachine::unexpected_eof::unexpected_eof(int line) : _line(line)
{}

VirtualMachine::unexpected_eof::unexpected_eof(VirtualMachine::unexpected_eof const & copy)
{ *this = copy; }

VirtualMachine::unexpected_eof::~unexpected_eof()
{}

VirtualMachine::unexpected_eof &	VirtualMachine::unexpected_eof::operator = (VirtualMachine::unexpected_eof const & r)
{ _line = r._line; return *this; }

const char *	VirtualMachine::unexpected_eof::what() const noexcept
{ return "unexpected eof"; }

int 			VirtualMachine::unexpected_eof::getLine() const
{ return _line; }


/////////////////////////// _______ VirtualMachine GENERAL ______ ////////

void			VirtualMachine::_del_elem()
{ delete _stack.top(); _stack.pop(); }

#define NUM_OF_TYPES 5

eOperandType	VirtualMachine::_str_to_type(std::string str, int line)
{
	std::string		types[NUM_OF_TYPES] = {"int8", "int16", "int32", "float", "double"};

	for (int i = 0; i < NUM_OF_TYPES; ++i)
		if (str == types[i])
			return static_cast<eOperandType>(i);
	throw VirtualMachine::unknown_cmd(line);
}

void			VirtualMachine::_recursivePrint(std::deque<IOperand const *>::iterator it)
{
	if (it == _stack.end())
		return;
	_recursivePrint(it + 1);
	std::cout << (*it)->toString() << std::endl;
}

/////////////////////////// _______ VirtualMachine COMMANDS ______ ////////

void			VirtualMachine::_push(cmd_parsed parsed, int line)
{ _stack.push(OperandFactory().createOperand(_str_to_type(parsed.first, line), parsed.second)); }

void			VirtualMachine::_pop(cmd_parsed parsed, int line)
{
	static_cast<void>(parsed);
	if (_stack.empty()) throw VirtualMachine::execution_impossible(line);
	_stack.pop();
}

void			VirtualMachine::_dump(cmd_parsed parsed, int line)
{
	static_cast<void>(parsed);
	static_cast<void>(line);
	_recursivePrint(_stack.begin());
}

void			VirtualMachine::_assert(cmd_parsed parsed, int line)
{
	if (_str_to_type(parsed.first, line) != _stack.top()->getType())
		throw VirtualMachine::assert_false(line);

	bool	assert;

	switch (_stack.top()->getType())
	{
		case t_float:
			assert = std::stof(parsed.second) != std::stof(_stack.top()->toString());
			break ;
		case t_double:
			assert = std::stod(parsed.second) != std::stod(_stack.top()->toString());
			break ;
		default:
			assert = std::stoi(parsed.second) != std::stoi(_stack.top()->toString());
			break ;
	}
	if (assert)
		throw VirtualMachine::assert_false(line);
}

void			VirtualMachine::_add(cmd_parsed parsed, int line)
{
	static_cast<void>(parsed);
	if (_stack.size() < 2)
		throw VirtualMachine::not_enough_operands(line);

	IOperand const *	new_elem;

	new_elem = **(_stack.end() - 2) + **(_stack.end() - 1);
	_del_elem();
	_del_elem();
	_stack.push(new_elem);
}

void			VirtualMachine::_sub(cmd_parsed parsed, int line)
{
	static_cast<void>(parsed);
	if (_stack.size() < 2)
		throw VirtualMachine::not_enough_operands(line);

	IOperand const *	new_elem;

	new_elem = **(_stack.end() - 2) - **(_stack.end() - 1);
	_del_elem();
	_del_elem();
	_stack.push(new_elem);
}

void			VirtualMachine::_mul(cmd_parsed parsed, int line)
{
	static_cast<void>(parsed);
	if (_stack.size() < 2)
		throw VirtualMachine::not_enough_operands(line);

	IOperand const *	new_elem;

	new_elem = **(_stack.end() - 2) * **(_stack.end() - 1);
	_del_elem();
	_del_elem();
	_stack.push(new_elem);
}

void			VirtualMachine::_div(cmd_parsed parsed, int line)
{
	static_cast<void>(parsed);
	if (_stack.size() < 2)
		throw VirtualMachine::not_enough_operands(line);

	IOperand const *	new_elem;

	new_elem = **(_stack.end() - 2) / **(_stack.end() - 1);
	_del_elem();
	_del_elem();
	_stack.push(new_elem);
}

void			VirtualMachine::_mod(cmd_parsed parsed, int line)
{
	static_cast<void>(parsed);
	if (_stack.size() < 2)
		throw VirtualMachine::not_enough_operands(line);

	IOperand const *	new_elem;

	new_elem = **(_stack.end() - 2) % **(_stack.end() - 1);
	_del_elem();
	_del_elem();
	_stack.push(new_elem);
}

void			VirtualMachine::_print(cmd_parsed parsed, int line)
{
	static_cast<void>(parsed);
	if (_stack.top()->getType() != t_int8)
		throw VirtualMachine::assert_false(line);
	std::cout << static_cast<char>(std::stoi(_stack.top()->toString())) << std::endl;
}

void			VirtualMachine::_exit(cmd_parsed parsed, int line)
{ static_cast<void>(parsed); static_cast<void>(line); VirtualMachine::~VirtualMachine(); exit(0); }

/////////////////////////// _______ VirtualMachine COMMANDS END ______ ////////


/*
 * cmd example: push int16(42)
 *
 * parsed[1] == "int16" // full type
 * parsed[2] == "16" // type size
 * parsed[3] == "42" // value
*/

bool			VirtualMachine::_findCmd(std::string input)
{
	std::cmatch		parsed;

	for (std::pair<std::string,cmd> pair : _cmd)
		if (std::regex_match(input.c_str(), parsed, std::regex(pair.first)))
		{
			_queue.push_back(std::make_pair(pair.second, std::make_pair(parsed[1], parsed[3])));
			return true;
		}
	return false;
}

void			VirtualMachine::readCmds()
{
	std::string	input;
	int			line = 0;

	do
	{
		if (std::cin.eof())
			throw VirtualMachine::unexpected_eof(line);
		++line;
		std::getline(std::cin, input);
		if (!_findCmd(input) && !std::cin.eof() && input[0] != ';')
			throw VirtualMachine::unknown_cmd(line);
	} while (input != ";;");
}

void			VirtualMachine::readCmds(std::string filename)
{
	std::ifstream	file(filename);
	std::string		input;
	int				line = 0;

	if (!file.is_open())
		throw VirtualMachine::file_not_open();
	do
	{
		if (file.eof())
			throw VirtualMachine::unexpected_eof(line);
		++line;
		std::getline(file, input);
		if (!_findCmd(input) && !file.eof() && input[0] != ';')
			throw VirtualMachine::unknown_cmd(line);
	} while (input != "exit");
}

void			VirtualMachine::run()
{
	int		line = 0;

	for (std::pair<cmd,cmd_parsed> p : _queue)
	{
		++line;
		(this->*p.first)(p.second, line);
	}
}
