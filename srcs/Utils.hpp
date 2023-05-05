#ifndef UTILS_HPP
# define UTILS_HPP

# include "Includes.hpp"

bool	isInt(std::string input);
size_t	toSizeType(std::string value);
void	removeZeros(std::string& str);

template <typename T>
std::string to_string(T value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template <typename T>
void    PrintVector(const std::vector<T> &v)
{
		std::cout << FC(GREEN, "VECTOR") << std::endl;
		for(typename std::vector<T>::const_iterator it(v.begin()); it != v.end(); it++)
		{
				std::cout << *it << std::endl;
		}
}

template <typename T>
void    PrintVectorPointer(const std::vector<T> &v)
{
		std::cout << FC(GREEN, "VECTOR") << std::endl;
		for(typename std::vector<T>::const_iterator it(v.begin()); it != v.end(); it++)
		{
				std::cout << *(*it) << std::endl;
		}
}



#endif // UTILS_HPP

