#include<iostream>
#include<vector>
#include <bits/stdc++.h>

using namespace std;

bool isMatch(string str, string pattern) 
{
	bool bool_array [str.size()+1] [pattern.size()+1];

	//initialize boolean array to false.
	for (int i = 0; i <= str.size(); ++i)
	{
		for (int j = 0; j <= pattern.size(); ++j)
		{
			bool_array[i][j] = 0;
		}
	}

	// base case
	bool_array[0][0] = true;


	for (int i = 0; i <= str.size(); i++)
	{
		for (int j = 1; j <= pattern.size(); j++)
		{
			if (str[i-1] == pattern[j-1] || pattern[j-1] == '?')
				bool_array[i][j] = bool_array[i-1][j-1];

			else if (pattern[j-1] == '*')
				bool_array[i][j] = bool_array[i][j-1] || bool_array[i-1][j];
			// else if (pattern[j] == '*')
			// 	bool_array[i][j] = bool_array[i][j-1] || bool_array[i-1][j];
		}
	}

	return bool_array[str.size()][pattern.size()];
}

bool strmatch(char str[], char pattern[], int n, int m)
{
    // empty pattern can only match with
    // empty string
    if (m == 0)
        return (n == 0);
 
    // lookup table for storing results of
    // subproblems
    bool lookup[n + 1][m + 1];
 
    // initialize lookup table to false
    memset(lookup, false, sizeof(lookup));
 
    // empty pattern can match with empty string
    lookup[0][0] = true;
 
    // Only '*' can match with empty string
    for (int j = 1; j <= m; j++)
        if (pattern[j - 1] == '*')
            lookup[0][j] = lookup[0][j - 1];
 
    // fill the table in bottom-up fashion
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // Two cases if we see a '*'
            // a) We ignore ‘*’ character and move
            //    to next  character in the pattern,
            //     i.e., ‘*’ indicates an empty sequence.
            // b) '*' character matches with ith
            //     character in input
            if (pattern[j - 1] == '*')
                lookup[i][j]
                    = lookup[i][j - 1] || lookup[i - 1][j];
 
            // Current characters are considered as
            // matching in two cases
            // (a) current character of pattern is '?'
            // (b) characters actually match
            else if (pattern[j - 1] == '?'
                     || str[i - 1] == pattern[j - 1])
                lookup[i][j] = lookup[i - 1][j - 1];
 
            // If characters don't match
            else
                lookup[i][j] = false;
        }
    }
 
    return lookup[n][m];
}

int main()
{
	char i[4] = "bob";
	char y[2] = "*";
	std::cout << strmatch(i, y, 4, 2) << std::endl;
}