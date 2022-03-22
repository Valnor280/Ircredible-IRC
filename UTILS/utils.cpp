#include "UTILS/utils.hpp"

bool    isspecial(char c)
{
    if (c != '[' && c != ']' && c != '\\' && c != '`' && c != '_' && c != '^' && c != '{' && c != '|' && c != '}')
        return (false);
    return (true);
}
