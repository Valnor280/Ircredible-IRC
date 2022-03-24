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
	std::string ret;
	if (my_serv.get_usermap()[socket_client].get_nick().empty())
		ret = std::string(":" + my_serv.get_hostname() + " " + true_code + " * ");
	else if (code == 691)
		ret = std::string(":" + my_serv.get_hostname() + " " + true_code + " ");
	else
		ret = ":" + my_serv.get_hostname() + " " + true_code + " " + my_serv.get_usermap()[socket_client].get_nick() + " ";
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
	case 5:
			return ret += "Try server <Another 42 IRC project, port whatever they want \r\n";
	case 221:
			return ret += my_serv.get_usermap()[socket_client].get_mode() + "\r\n";
	case 256:
			return ret += my_serv.get_servername() + ":Administrative info\r\n";
	case 257:
			return ret += ":Hello and welcome to the Ircredible IRC server located in Paris, France.\r\n";
	case 258:
			return ret += ":The server is currently hosted inside the 42 school cluster server.\r\n";
	case 259:
			return ret += ":addubois@student.42.fr, admadene@student.42.fr, fsacquin@student.42.fr\r\n";
	case 301:
			return ret += my_serv.get_usermap()[socket_client].get_nick() + ":" + my_serv.get_usermap()[socket_client].get_away_msg() + "\r\n";
	case 302:
			return ret += input + "\r\n";  //<réponse> ::= <pseudo>['*'] '=' <'+'|'-'><hôte>
	case 303:
			return ret += input + "\r\n"; // ISON CMD NEED TO SEND THE USER LIST
	case 305:
			return ret += ":You are no longer marked as being away\r\n";
	case 306:
			return ret += ":You have been marked as being away\r\n";
	case 311:
			return ret += my_serv.get_usermap()[socket_client].get_nick() + " " + my_serv.get_usermap()[socket_client].get_username() + " " + my_serv.get_hostname() + " * " + ":" + my_serv.get_usermap()[socket_client].get_real_name() + "\r\n";
	case 312:
			return ret += my_serv.get_usermap()[socket_client].get_nick() + " " + my_serv.get_servername() + " : \r\n"; // This one not sure if we have to use it
	case 312:
			return ret +=
	case 312:
			return ret +=
	case 312:
			return ret +=
	}


	return(std::string("no rpl"));
}
