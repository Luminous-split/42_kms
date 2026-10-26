#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_rates;

		static std::string	trim(const std::string &s);
		static bool			isValidDate(const std::string &date);
		static bool			parseNumber(const std::string &s, double &out);
		bool				getRate(const std::string &date, double &rate) const;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void	loadDatabase(const std::string &filename);
		void	processInput(const std::string &filename) const;
};

#endif
