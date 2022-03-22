#include "SERVER/server.hpp"

void		server::PASS(std::string input, std::pair<int, user> pair)
{
	int i;
	std::map<int, user>::iterator itr;
	for ( i = 0; i < 4, i++;)
		input.erase(i);
	while (input.at(i) == ' ')
		i++;
	if(input.at(i) == *(input.end()))
		send(pair.first, ERR_NEEDMOREPARAMS("*", PASS_CMD), 512, 0);
	if (input.compare(_pswd) == 0 && user_map[pair.first].get_auth() == 1)
	{
		user_map[pair.first].set_auth(0);
	}
	else
	{
		if (user_map[pair.first].get_auth() == 0)
			send(pair.first, ERR_ALREADYREGISTRED(user_map[pair.first].get_nick()), 512, 0);
		else
			send(pair.first, ERR_PASSWDMISMATCH, 512, 0);
		user_map[pair.first].set_auth(1);
	}
}