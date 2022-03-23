#include "UTILS/utils.hpp"

bool    isspecial(char c)
{
    if (c != '[' && c != ']' && c != '\\' && c != '`' && c != '_' && c != '^' && c != '{' && c != '|' && c != '}')
        return (false);
    return (true);
}

std::vector<std::string>		ft_split(std::string buffer, char sep)
{
	std::vector<std::string>				ret;
	std::vector<std::string>::size_type		i = 0;
	unsigned long							start_index = 0;
	unsigned long							end_index = 0;

	while (i < buffer.length())
	{
		if ((buffer[i] == sep || i == buffer.length()) && i != start_index)
		{
			end_index = i;
			std::string		sub_str = buffer.substr(start_index, end_index - start_index);
			ret.push_back(sub_str);
			start_index = end_index + 1;
		}
		i++;
	}
	return ret;
}
