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
		if (buffer[i] == sep && i != start_index)
		{
			end_index = i;
			std::string		sub_str = buffer.substr(start_index, end_index - start_index);
			ret.push_back(sub_str);
			start_index = end_index + 1;
		}
		else if ( i == buffer.length() - 1 && i != start_index)
		{
			end_index = i + 1;
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

bool							check_user_mode_input( std::string arg)
{
	unsigned long		i = 1;
	std::string			signs = "+-";
	std::string			modes = "aiwroOs"; //RFS user modes list
	std::string			cool_modes = "aBdDHIioOpqrRSTVWwxZz"; //Wiki user modes list

	if (arg.length() < 2)
	{
		std::cout << "lol_1" << std::endl;
		return false;
	}
	if (signs.find(arg[0]) == std::string::npos)
	{
		std::cout << "lol_2" << std::endl;
		return false;
	}
	while (i < arg.size())
	{
		if (arg[i] == '\r' || arg[i] == '\n')
			return true;
		if (modes.find(arg[i]) == std::string::npos)
		{
			std::cout << "lol_3" << std::endl;
			return false;
		}
		i++;
	}
	return true;
}

bool							modif_mode_user(user & us, char c, int u)
{
	if (u == -1)
	{
		if (c == 'o' || c == 'O' || c == 'a')
			return false;
		else if (us.get_mode().find(c) == std::string::npos)
		{
			us.set_mode(us.get_mode() + c);
			std::cout << "what? avec '" << us.get_mode() << "'" << std::endl;
		}
	}
	else if (u == 1)
	{
		if (c == 'r' || c == 'a')
			return false;
		else if (us.get_mode().find(c) != std::string::npos)
			us.set_mode(us.get_mode().erase(us.get_mode().find(c), 1));
	}
	else if (u == 2) // AWAY status or OPER status
	{
		if (us.get_mode().find(c) == std::string::npos)
			us.set_mode(us.get_mode() + c);
		else
			return false;
	}
	else if (u == 3) // UNAWAY status
	{
		if (us.get_mode().find(c) != std::string::npos)
			us.set_mode(us.get_mode().erase(us.get_mode().find(c), 1));
		else
			return false;
	}
	return true;
}

void							send_welcome(int socket_client, server & my_serv)
{
	send(socket_client, send_reply("test", socket_client, my_serv, 1, "").c_str(), send_reply("test", socket_client, my_serv, 1, "").length(), MSG_DONTWAIT);
	send(socket_client, send_reply("test", socket_client, my_serv, 2, "").c_str(), send_reply("test", socket_client, my_serv, 2, "").length(), MSG_DONTWAIT);
	send(socket_client, send_reply("test", socket_client, my_serv, 3, "").c_str(), send_reply("test", socket_client, my_serv, 3, "").length(), MSG_DONTWAIT);
	send(socket_client, send_reply("test", socket_client, my_serv, 4, "").c_str(), send_reply("test", socket_client, my_serv, 4, "").length(), MSG_DONTWAIT);
}

std::string						vector_user_to_string(std::vector<user> vect)
{
	std::vector<user>::iterator itr;
	std::string ret;
	for(itr = vect.begin(); itr != vect.end(); itr++)
	{
		ret += itr->get_nick() + " ";
	}
	return(ret);
}

std::string						user_list(std::vector<user> op, std::vector<user> us)
{
	std::vector<user>::iterator itr;
	std::string ret;
	std::cout << "COUCOU5\n";
	for(itr = op.begin(); itr != op.end(); itr++)
	{
		std::string md = itr->get_mode();
		std::cout << "MODE : " << md << std::endl;
		if(md.find('i') == std::string::npos)
		{
			std::cout << "kiou" << std::endl;
			ret +=  "@" + itr->get_nick() + " ";
		}	
	}
	for(itr = us.begin(); itr != us.end(); itr++)
	{
		std::string md = itr->get_mode();
		if(md.find('i') == std::string::npos)
		{
			ret += itr->get_nick() + " ";
		}
	}
	if(*ret.end() == ' ')
		ret.resize(ret.length() - 1);
	return(ret);
}


bool find_user(std::vector<user> vect, user usr)
{
	for(std::vector<user>::iterator itr = vect.begin(); itr != vect.end(); itr++)
	{
		if(*itr == usr)
			return true;
	}
	return false;
}

bool							check_name_match(user & target, user & member , std::string pattern)
{
	(void)target;
	if (member.get_mode().find('i') != std::string::npos)
		return false;
	else if (star_name_checker(member.get_nick(), pattern))
		return true;
	else if (star_name_checker(member.get_hostname(), pattern))
		return true;
	else if (star_name_checker(member.get_username(), pattern))
		return true;
	else
		return false;
}

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

std::string send_reply(std::string input, int socket_client, server & my_serv, int code, std::string chan)
{
	std::string true_code = ft_to_string(code);
	if (code < 10)
		true_code = std::string(2, '0').append(ft_to_string(code));
	else if (code < 100)
		true_code = std::string(1, '0').append(ft_to_string(code));
	std::string ret;
	if (my_serv.get_usermap()[socket_client].get_nick().empty())
		ret = std::string(":" + my_serv.get_hostname() + " " + true_code + " * ");
	else
		ret = ":" + my_serv.get_hostname() + " " + true_code + " " + my_serv.get_usermap()[socket_client].get_nick() + " ";
	switch (code)
	{
	case 1:
			return ret += ":Welcome to the Ircredible Network, " + my_serv.get_usermap()[socket_client].get_id() + "\r\n";
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
	case 313:
			return ret += my_serv.get_usermap()[socket_client].get_nick() + " :is an IRC operator\r\n";
	case 314:
			return ret += my_serv.get_usermap()[socket_client].get_nick() + " " + my_serv.get_usermap()[socket_client].get_username()+ " " + my_serv.get_hostname() + " * " + ":" + my_serv.get_usermap()[socket_client].get_real_name() + "\r\n";
	case 315:
			return ret += input + " :End of WHO list\r\n"; // need <name>
	//case 317:
			//return ret += my_serv.get_usermap()[socket_client].get_nick() + " " + my_serv.get_usermap()[socket_client].get_time_idle() + " :seconds idle\r\n";
	case 318:
			return ret += my_serv.get_usermap()[socket_client].get_nick() + " :End of WHOIS list\r\n";
	//case 319:
		//	return ret += my_serv.get_usermap()[socket_client].get_nick() + ":*( ( "@" / "+" ) <channel> " " )\r\n";
	case 322:
			return ret += "<channel> <# visible> :<topic>\r\n";
	case 323:
			return ret += ":End of LIST\r\n";
	case 324:
			return ret += "<channel> <mode> <mode params>\r\n";
	case 331:
			return ret += chan + " :No topic is set\r\n";
	case 332:
			return ret += chan +  " :" + my_serv.get_chan_map()[chan].get_topic() + "\r\n";
	case 341:
			return ret += "<channel> <nick>\r\n";
	case 351:
			return ret += "<version>.<debuglevel> <server> :<comments>\r\n"; // maybe no use for us
	case 352:
			return ret += "* " + (my_serv.get_usermap())[socket_client].get_nick() + " " + (my_serv.get_usermap())[socket_client].get_hostname() + " " + my_serv.get_servername() + " " + (my_serv.get_usermap())[socket_client].get_nick();
	case 353:
			return ret += chan + " :" + user_list(my_serv.get_chan_map()[chan].get_op_list(my_serv.get_usermap()), my_serv.get_chan_map()[chan].get_user_list(my_serv.get_usermap())) + "\r\n";
	case 366:
			return ret += chan + ":End of NAMES list\r\n";
	case 367:
			return ret += "<channel> <banmask>\r\n";
	case 368:
			return ret += chan + " :End of channel ban list\r\n";
	case 369:
			return ret +=  my_serv.get_usermap()[socket_client].get_nick() + " :End of WHOWAS\r\n";
	case 371:
			return ret += ":" + input + "\r\n"; // <string>
	case 372:
			return ret += ":- " + my_serv.get_motd() + "\r\n";
	case 374:
			return ret += ":End of INFO list\r\n";
	case 375:
			return ret += ":- " + my_serv.get_servername() + " Message of the day - \r\n";
	case 376:
			return ret += ":End of MOTD command\r\n";
	case 381:
			return ret += ":You are now an IRC operator\r\n";
	case 382:
			return ret += "<config file> :Rehashing\r\n";
	case 391:
			return ret +=  my_serv.get_servername() + " : " + input + "\r\n"; // <string showing server's local time>
	case 401:
			return ret += input + " :No such nick/channel\r\n"; // nickname
	case 402:
			return ret += input + " :No such server\r\n"; // <server name>
	case 403:
			return ret += chan + " :No such channel\r\n"; // <channel name> :No such channel
	case 404:
			return ret += chan + " :Cannot send to channel\r\n"; // <channel name> 
	case 405:
			return ret += chan + " :You have joined too many channels\r\n"; // ''
	case 406:
			return ret += input + " :There was no such nickname\r\n";
	case 409:
			return ret += ":No origin specified\r\n";
	case 411:
			return ret += ":No recipient given " + input + "\r\n"; //<command>
	case 412:
			return ret += ":No text to send\r\n";
	case 421:
			return ret += input + " :Unknown command\r\n"; //<command>
	case 422:
			return ret += ":MOTD File is missing\r\n";
	case 423:
			return ret += my_serv.get_servername() + " :No administrative info available\r\n";
	case 431:
			return ret += ":No nickname given\r\n";
	case 432:
			return ret += input + " :Erroneous nickname\r\n"; // nick
	case 433:
			return ret += input + " :Nickname is already in use\r\n"; // nick
	case 441:
			return ret += input + "<channel> :They aren't on that channel\r\n"; //nick
	case 442:
			return ret += chan + " :You're not on that channel\r\n"; // channel
	case 443:
			return ret += my_serv.get_usermap()[socket_client].get_username() + "<channel> :is already on channel\r\n";
	case 451:
			return ret += ":You have not registered\r\n";
	case 461:
			return ret += input + " :Not enough parameters\r\n";
	case 462:
			return ret += ":Unauthorized command (already registered)\r\n";
	case 464:
			return ret += ":Password incorrect\r\n";
	case 471:
			return ret += input + " :Cannot join channel (+l)\r\n";
	case 472:
			return ret += input + " :is unknown mode char to me for <channel>\r\n";
	case 473:
			return ret += input + " :Cannot join channel (+i)\r\n";
	case 474:
			return ret += input + " :Cannot join channel (+b)\r\n";
	case 475:
			return ret += chan + " :Cannot join channel (+k)\r\n";
	case 476:
			return ret += input + " :Bad Channel Mask\r\n";
	case 481:
			return ret += ":Permission Denied- You're not an IRC operator\r\n";
	case 482:
			return ret += chan + " :You're not channel operator\r\n";
	case 483:
			return ret += ":You can't kill a server!\r\n";
	case 491:
			return ret += ":No O-lines for your host\r\n";
	case 501:
			return ret += ":Unknown MODE flag\r\n";
	case 502:
			return ret += ":Cannot change mode for other users\r\n";
	default:
			return ret += " ";
	}


	return(std::string("no rpl"));
}
