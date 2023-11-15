#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	int	i;

	std::ifstream				resFile;
	std::string					myline;
	std::string					word;
	std::vector<std::string>	row;

	resFile.open("data.csv");
	_database.clear();
	if (resFile.is_open())
	{
		i = 0;
		while (resFile)
		{
			row.clear();
			std::getline(resFile, myline);
			std::stringstream s(myline);
			while (std::getline(s, word, ','))
			{
				row.push_back(word);
			}
			if (i != 0)
				_database[convertDateAndtime(row[0])] = std::atof(row[1].c_str());
			i++;
		}
		resFile.close();
	}
	else
		throw std::runtime_error("Error: could not open database.");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &t) : _database(t._database)
{}

BitcoinExchange::~BitcoinExchange()
{}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &t)
{
	if (this != &t)
		_database = t._database;
	return (*this);
}

int	BitcoinExchange::convertDateAndtime(std::string &strDate)
{
	int					date = 0;
	std::vector<int>	time;
	std::string			word;
	std::stringstream	s(strDate);
	while (getline(s, word, '-'))
		time.push_back(std::atoi(word.c_str()));
	if (time.size() != 3)
		return (0);
	if (time[0] < 2000 || time[0] > 10000)
		return (0);
	if (time[1] > 12)
		return (0);
	if (time[2] > 31)
		return (0);
	if (time[2] == 31 && (time[1] == 4 or time[1] == 6 or time[1] == 9 or time[1] == 11))
		return (0);
	if (time[1] == 2)
	{
		if (time[2] > 29)
			return (0);
		if (time[2] == 29 && ((time[0] % 100) % 4 != 0))
			return (0);
	}
	date += time[2];
	date += 100 * time[1];
	date += 1000000 * time[0];
	return (date);
}

void	BitcoinExchange::handleLine(std::vector<std::string> &line)
{
	std::string								word;
	float									val;
	int										valDate;
	std::map<int, float>::iterator	itlow;

	if (line.size() != 0)
	{
		if (convertDateAndtime(line[0]))
		{
			if (line.size() != 2)
				std::cerr << "Error: bad row => " << line[0] << std::endl;
			else
			{
				val = std::atof(line[1].c_str());
				if (val < 0)
					std::cerr << "Error: not a positive number" << std::endl;
				else if (val > 1000)
					std::cerr << "Error: too large a number." << std::endl;
				else if ((line[1] == "0.0" || line[1] == "0") && val == 0)
					std::cout << line[0] << " => " << line[1] << " = 0.0" << std::endl;
				else if ((line[1] == "0.0" || line[1] == "0") && val != 0)
					std::cerr << "Error: bad input => " << line[1] << std::endl;
				else
				{
					valDate = convertDateAndtime(line[0]);
					itlow = _database.lower_bound(valDate);
					if (itlow->first == valDate)
						std::cout << line[0] << " => " << line[1] << " = " << (itlow->second * val) << std::endl;
					else
					{
						if (_database.begin() != itlow)
							--itlow;
						if (_database.begin() == itlow
							&& valDate != (itlow->first))
							std::cerr << "Error: bitcoin doesn't exist here" << std::endl;
						else
							std::cout << line[0] << " => " << line[1] << " = " << (itlow->second * val) << std::endl;
					}
				}
			}
		}
		else
			std::cerr << "Error: bad input => " << line[0] << std::endl;
	}
}

std::string	BitcoinExchange::stripSpacesFront(std::string &s)
{
	std::string res = "";
	bool		flag = false;

	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
			flag = true;
		if (flag)
			res += s[i];
	}
	return (res);
}

std::string	BitcoinExchange::stripSpaces(std::string &s)
{
	s = stripSpacesFront(s);
	for (size_t i = 0; i < s.size() / 2; i++)
	{
		char t = s[i];
		s[i] = s[s.size() - i - 1];
		s[s.size() - i - 1] = t;
	}
	s = stripSpacesFront(s);
	for (size_t i = 0; i < s.size() / 2; i++)
	{
		char t = s[i];
		s[i] = s[s.size() - i - 1];
		s[s.size() - i - 1] = t;
	}
	return (s);
}

void BitcoinExchange::processFile(const std::string &filePath)
{
	int	i;

	std::ifstream				resFile;
	std::string					myline;
	std::string					word;
	std::vector<std::string>	row;

	resFile.open(filePath.c_str());
	if (resFile.is_open())
	{
		i = 0;
		while (resFile)
		{
			row.clear();
			std::getline(resFile, myline);
			std::stringstream s(myline);
			while (getline(s, word, '|'))
				row.push_back(stripSpaces(word));
			if (i != 0)
				handleLine(row);
			i++;
		}
		resFile.close();
	}
	else
		throw std::runtime_error("Error: could not open file.");
}
