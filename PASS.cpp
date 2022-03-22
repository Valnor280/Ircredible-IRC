#include "SERVER/server.hpp"

void	PASS(std::string input, std::pair<int, user> client, std::map<int, user> &user_map, char *_pswd);
{
	int i = 3;
	std::map<int, user>::iterator itr;
	input.erase(input.begin(), input.begin() + 4);
	while (input.at(i) == ' ')
		i++;
	if(input.at(i) == *(input.end()))
		send(client.first, ": * PASS :Not enough parameters\r\n", 512, 0);
	if (input.compare(_pswd) == 0 && user_map[client.first].get_auth() == 1)
	{
		user_map[client.first].set_auth(0);
	}
	else
	{
		if (user_map[client.first].get_auth() == 0)
			send(client.first, ":" + user_map[client.first].get_nick() ":You may not reregister\r\n", 512, 0);
		else
			send(client.first, ": Password incorrect\r\n", 512, 0);
		user_map[client.first].set_auth(1);
	}
}