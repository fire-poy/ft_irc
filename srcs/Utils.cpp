#include "Utils.hpp"

bool	isInt(std::string input)
{
	size_t	digit = 0;
	std::string::iterator it = input.begin();
	while (it != input.end() && std::isdigit(*it))
	{
		digit++;
		it++;
	}
	if (digit != input.size())
		return false;
	else if (digit >= 1 && digit < 4)
		return true;
	else
		std::cerr << "User limit exceeded" << std::endl;
	return false;
}

size_t	toSizeType(std::string value)
{
    std::stringstream ss;
	size_t ret;
    ss << value;
	ss >> ret; 
    return ret;
}

void	removeZeros(std::string& str)
{
    std::string newStr;
    for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] != 0)
		{
            newStr += str[i];
        }
    }
    str = newStr;
}


