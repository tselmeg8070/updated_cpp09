#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP
# include <map>
# include <vector>
# include <sstream>
# include <string>
# include <iostream>
# include <fstream>
# include <cstdlib>
# include <stdexcept>

class BitcoinExchange
{
	private:
		std::map<int, float> _database;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &t);
		~BitcoinExchange();
		BitcoinExchange &operator=(const BitcoinExchange &t);

		std::string	stripSpaces(std::string &s);
		int			convertDateAndtime(std::string &strDate);
		void		processFile(const std::string &filePath);
		void		handleLine(std::vector<std::string> &line);
		std::string	stripSpacesFront(std::string &s);
};

#endif
