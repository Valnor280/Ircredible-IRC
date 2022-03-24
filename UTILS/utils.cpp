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
	if (i == buffer.length() && ret.empty())
	{
		ret.push_back(buffer);
	}
	return ret;
}

std::string		ft_to_string(size_t value)
{
	std::string output;
	std::string sign;
	char		nb[2];

	if (value < 0)
	{
		sign + "-";
		value = -value;
	}
	nb[1] = '\0';
	while (output.empty() || (value > 0))
	{
		nb[0] = value % 10 + '0';
		output.insert(0, std::string(nb));
		value /= 10;
	}

	return (sign + output);
}

std::string						ft_toupper(std::string input)
{
	for (unsigned long i = 0; i < input.size(); i++)
	{
		input[i] = toupper(input[i]);
	}
	return input;
}

void							send_welcome(int socket_client, server & my_serv)
{
	send(socket_client, send_reply("test", socket_client, my_serv, 1).c_str(), send_reply("test", socket_client, my_serv, 1).length(), MSG_DONTWAIT);
	send(socket_client, send_reply("test", socket_client, my_serv, 2).c_str(), send_reply("test", socket_client, my_serv, 2).length(), MSG_DONTWAIT);
	send(socket_client, send_reply("test", socket_client, my_serv, 3).c_str(), send_reply("test", socket_client, my_serv, 3).length(), MSG_DONTWAIT);
	send(socket_client, send_reply("test", socket_client, my_serv, 4).c_str(), send_reply("test", socket_client, my_serv, 4).length(), MSG_DONTWAIT);
}

std::string send_reply(std::string input, int socket_client, server & my_serv, int code)
{
	(void)input;
	std::string true_code = ft_to_string(code);
	if (code < 10)
		true_code = std::string(2, '0').append(ft_to_string(code));
	else if (code < 100)
		true_code = std::string(1, '0').append(ft_to_string(code));
	std::string ret = ":" + my_serv.get_hostname() + " " + true_code + " " + my_serv.get_usermap()[socket_client].get_nick() + " ";

	switch (code)
	{
	case 1:
			return ret += ":Welcome to the Ircredible Network, " + my_serv.get_usermap()[socket_client].get_id() + "\n\r";
	case 2:
			return ret += ":Your host is " + my_serv.get_servername() + ", running version " + my_serv.get_version() + "\r\n";
	case 3:
			return ret += ":This server was created " + my_serv.get_date() + "\r\n";
	case 4: 
			return ret += ":" + my_serv.get_servername() + " " + my_serv.get_version() + " " + my_serv.get_usermap()[socket_client].get_mode() + "\r\n";
	}
	return(std::string("no rpl"));
}
