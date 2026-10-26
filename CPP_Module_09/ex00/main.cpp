#include "BitcoinExchange.hpp"
#include <iostream>
#include <exception>

int	main(int argc, char **argv)
{
	BitcoinExchange	btc;

	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
	try
	{
		btc.loadDatabase("data.csv");
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	btc.processInput(argv[1]);
	return (0);
}
