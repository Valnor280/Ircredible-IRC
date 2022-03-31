#include <string>
#include <iostream>
#include <cstring>
#include <algorithm>
bool						star_name_checker(std::string str, std::string pattern) // https://www.prodevelopertutorial.com/wildcard-matching-in-c/ //RIP minishell, petit ange parti trop tot
{
	bool bool_array [str.size()+1] [pattern.size()+1];

	//initialize boolean array to false.
	for (unsigned long i = 0; i <= str.size(); ++i)
	{
		for (unsigned long j = 0; j <= pattern.size(); ++j)
		{
			bool_array[i][j] = 0;
		}
	}

	// base case
	bool_array[0][0] = true;


	for (unsigned long i = 1; i <= str.size(); i++)
	{
		for (unsigned long j = 1; j <= pattern.size(); j++)
		{
			if (str[i-1] == pattern[j-1] || pattern[j-1] == '?')
				bool_array[i][j] = bool_array[i-1][j-1];

			else if (pattern[j-1] == '*')
				bool_array[i][j] = bool_array[i][j-1] || bool_array[i-1][j];
		}
	}

	return bool_array[str.size()][pattern.size()];
}

int main()
{
	std::cout << star_name_checker("patrick!~patrick@", "p*!*@*") << std::endl;
}