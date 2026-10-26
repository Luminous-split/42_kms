#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <cctype>
#include <stdexcept>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _rates(other._rates) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_rates = other._rates;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::trim(const std::string &s)
{
	std::string::size_type	start = s.find_first_not_of(" \t\r\n");
	std::string::size_type	end = s.find_last_not_of(" \t\r\n");

	if (start == std::string::npos)
		return ("");
	return (s.substr(start, end - start + 1));
}

// Expects strict YYYY-MM-DD and checks the day exists (leap years included)
bool BitcoinExchange::isValidDate(const std::string &date)
{
	static const int	daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int					year;
	int					month;
	int					day;
	int					maxDay;

	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);
	for (std::string::size_type i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue ;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return (false);
	}
	year = std::atoi(date.substr(0, 4).c_str());
	month = std::atoi(date.substr(5, 2).c_str());
	day = std::atoi(date.substr(8, 2).c_str());
	if (year < 1 || month < 1 || month > 12 || day < 1)
		return (false);
	maxDay = daysInMonth[month - 1];
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		maxDay = 29;
	return (day <= maxDay);
}

bool BitcoinExchange::parseNumber(const std::string &s, double &out)
{
	char	*end;

	if (s.empty())
		return (false);
	for (std::string::size_type i = 0; i < s.size(); ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(s[i]))
			&& s[i] != '.' && s[i] != '-' && s[i] != '+')
			return (false);
	}
	errno = 0;
	out = std::strtod(s.c_str(), &end);
	if (*end != '\0' || end == s.c_str() || errno == ERANGE)
		return (false);
	return (true);
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream	file(filename.c_str());
	std::string		line;
	double			rate;

	if (!file.is_open())
		throw std::runtime_error("Error: could not open database file.");
	if (!std::getline(file, line))
		throw std::runtime_error("Error: empty database file.");
	while (std::getline(file, line))
	{
		std::string::size_type	comma = line.find(',');

		if (trim(line).empty())
			continue ;
		if (comma == std::string::npos)
			throw std::runtime_error("Error: bad database line => " + line);
		std::string	date = trim(line.substr(0, comma));
		std::string	value = trim(line.substr(comma + 1));
		if (!isValidDate(date) || !parseNumber(value, rate) || rate < 0)
			throw std::runtime_error("Error: bad database line => " + line);
		_rates[date] = rate;
	}
	if (_rates.empty())
		throw std::runtime_error("Error: empty database file.");
}

// Uses the closest date lower than or equal to the requested one
bool BitcoinExchange::getRate(const std::string &date, double &rate) const
{
	std::map<std::string, double>::const_iterator	it = _rates.upper_bound(date);

	if (it == _rates.begin())
		return (false);
	--it;
	rate = it->second;
	return (true);
}

void BitcoinExchange::processInput(const std::string &filename) const
{
	std::ifstream	file(filename.c_str());
	std::string		line;
	bool			first = true;
	double			value;
	double			rate;

	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return ;
	}
	while (std::getline(file, line))
	{
		if (first)
		{
			first = false;
			if (trim(line) == "date | value")
				continue ;
		}
		if (trim(line).empty())
			continue ;

		std::string::size_type	sep = line.find(" | ");
		if (sep == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue ;
		}
		std::string	date = trim(line.substr(0, sep));
		std::string	valueStr = trim(line.substr(sep + 3));
		if (!isValidDate(date) || !parseNumber(valueStr, value))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue ;
		}
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue ;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue ;
		}
		if (!getRate(date, rate))
		{
			std::cerr << "Error: no data available for date => " << date << std::endl;
			continue ;
		}
		std::cout << date << " => " << valueStr << " = " << value * rate << std::endl;
	}
}
