#include <iostream>
#include <sstream>
#include "../include/VirtualMachine.hpp"

int		main(int argc, char **argv)
{
	VirtualMachine		vm;

	try
	{
		if (argc > 1)
			vm.readCmds(argv[1]);
		else
			vm.readCmds();
		vm.run();
	}
	catch (VirtualMachine::unknown_cmd & ex)
	{ std::cout << "line " << ex.getLine() << ": " << ex.what() << std::endl; }
	catch (VirtualMachine::assert_false & ex)
	{ std::cout << "line " << ex.getLine() << ": " << ex.what() << std::endl; }
	catch (VirtualMachine::not_enough_operands & ex)
	{ std::cout << "line " << ex.getLine() << ": " << ex.what() << std::endl; }
	catch (VirtualMachine::execution_impossible & ex)
	{ std::cout << "line " << ex.getLine() << ": " << ex.what() << std::endl; }
	catch (VirtualMachine::unexpected_eof & ex)
	{ std::cout << "line " << ex.getLine() << ": " << ex.what() << std::endl; }
	catch (std::exception & ex)
	{ std::cout << ex.what() << std::endl; }
	return 0;
}
