#include "commands.hpp"
#include "../SERVER/server.hpp"
#include "../CHANNEL/channel.hpp"




// LISTE DE COMMANDES SERVER SIDE
void		CAP(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "CAP function called" << std::endl;

    my_serv.get_usermap()[socket_client].set_status("capped");

(void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}


void		ADMIN(std::string input, int socket_client, server & my_serv) 
{
	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		////std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

    std::cout << "ADMIN called" << std::endl;
	std::string			ret;
	user				target = (my_serv.get_usermap())[socket_client];
	std::vector<std::string>	splitted = ft_split(input, ' ');

	if (splitted.size() > 1 && splitted[1] !=  my_serv.get_servername())
	{
		std::string tmp = send_reply("ADMIN", socket_client, my_serv, ERR_NOSUCHSERVER, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else
	{
		std::string tmp = send_reply("ADMIN", socket_client, my_serv, RPL_ADMINME, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("ADMIN", socket_client, my_serv, RPL_ADMINLOC1, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("ADMIN", socket_client, my_serv, RPL_ADMINLOC2, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("ADMIN", socket_client, my_serv, RPL_ADMINEMAIL, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
    // std::cout << "input :[" << input << "]" << std::endl;
    // std::cout << "socket :" << socket_client << std::endl;
    // my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}

void		NICK(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "NICK called" << std::endl;
    
	std::cout << socket_client << std::endl;
	if(my_serv.get_usermap()[socket_client].get_auth() == 1)
	{
		////std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}
    size_t  begsub;
    size_t  endsub;
    if ((begsub = input.find(' ')) == std::string::npos)
        std::cout << "Error Nick function: no space" << std::endl;
    if ((endsub = input.find('\r')) == std::string::npos  && (endsub = input.find('\n')) == std::string::npos)
        std::cout << "coucou" << std::endl;

    //recup le nick
    std::string nick = input.substr(begsub + 1, endsub - begsub - 1);

    
    
    //check nick format
	std::cout << nick << std::endl;
	if(nick == "NICK")
	{
		std::string tmp = send_reply("NICK", socket_client, my_serv, ERR_NONICKNAMEGIVEN, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		return;
	}
    if ((!isspecial(nick[0]) && !isalpha(nick[0])) || nick.size() > 9)
    {
        std::string tmp = send_reply("NICK", socket_client, my_serv, ERR_ERRONEUSNICKNAME, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
        //"<client> <nick> :Erroneus nickname"
        return;
    }
    for(std::string::iterator it = nick.begin(); it != nick.end(); ++it)
        if (!isspecial(*it) && !isalnum(*it) && *it != '-')
        {
            std::string tmp = send_reply("NICK", socket_client, my_serv, ERR_ERRONEUSNICKNAME, "");
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
            //"<client> <nick> :Erroneus nickname"
            return;
        }


    //check si il existe
    for (std::map<int, user>::iterator itr = my_serv.get_usermap().begin(); itr != my_serv.get_usermap().end(); ++itr)
    {
        if (itr->second.get_nick() == nick)
        {
            std::string tmp = send_reply(nick, socket_client, my_serv, ERR_NICKNAMEINUSE, "");
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
            //"<client> <nick> :Nickname is already in use"
            return;
        }
    }
	//std::cout << "On passe juste avnt le bon if a cet endroit la" << std::endl;
	//std::cout << "registration du peon = " << (my_serv.get_usermap()[socket_client]).get_registration() << std::endl;
	if ((my_serv.get_usermap()[socket_client]).get_registration() == 3)
	{
		//std::cout << "YOOOOOOOOOOOOOOOOOOOOOOO" << std::endl;
		my_serv.get_regi_map().erase(my_serv.get_usermap()[socket_client].get_nick());
	}
    my_serv.get_usermap()[socket_client].set_nick(nick);
	my_serv.get_regi_map()[nick] = my_serv.get_usermap()[socket_client];

	// CHANGEMENT DE LA VALEUR DE _REGISTRATION DANS USER POUR SAVOIR OU ON EN EST DANS LA REGISTRATION
	if (my_serv.get_usermap()[socket_client].get_registration() == 0)
		my_serv.get_usermap()[socket_client].set_registration(1);
	else if (my_serv.get_usermap()[socket_client].get_registration() == 2)
	{
		//std::cout << "ON FINIT LA REGISTRATION DANS NICK" << std::endl;
		(my_serv.get_usermap()[socket_client]).set_registration(3);
		send_welcome(socket_client, my_serv);
		my_serv.get_regi_map().insert(std::make_pair(my_serv.get_usermap()[socket_client].get_nick(), *(&(my_serv.get_usermap()[socket_client]))));
	}
	else
	{
		my_serv.get_regi_map().insert(std::make_pair(my_serv.get_usermap()[socket_client].get_nick(), *(&(my_serv.get_usermap()[socket_client]))));
	}

    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}

void		PASS(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "PASS called" << std::endl;

  	size_t  begsub;
    size_t  endsub;
    if ((begsub = input.find(' ')) == std::string::npos)
	{
        std::string tmp = send_reply("PASS", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		return;
	}
    if ((endsub = input.find('\r')) == std::string::npos  && (endsub = input.find('\n')) == std::string::npos)
	{
        std::cout << "coucou" << std::endl;
	}
	std::string pass = input.substr(begsub + 1, endsub - begsub - 1);
	if (pass.compare(my_serv.get_pswd()) == 0 && my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		my_serv.get_usermap()[socket_client].set_auth(0);
		return;
	}
	else
	{
		if (my_serv.get_usermap()[socket_client].get_auth() == 0)
		{
			std::string tmp = send_reply("PASS", socket_client, my_serv, ERR_ALREADYREGISTRED, "");
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		}
		else
		{
			std::string tmp = send_reply("PASS", socket_client, my_serv, ERR_PASSWDMISMATCH, "");
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		}
		my_serv.get_usermap()[socket_client].set_auth(1);
		return;
	}
}


void		USER(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "USER called" << std::endl;
    
	if(my_serv.get_usermap()[socket_client].get_auth() == 1)
	{
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}
	if (my_serv.get_usermap()[socket_client].get_username().empty() == false)
	{
		std::string tmp = send_reply("USER", socket_client, my_serv, ERR_ALREADYREGISTRED, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		return;
	}
	size_t  begsub;
    size_t  endsub;
    if ((begsub = input.find(' ')) == std::string::npos)
	{
        std::string tmp = send_reply("USER", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		return;
	}
	else if ((endsub = input.find(' ', begsub + 1)) == std::string::npos)
	{
		std::string tmp = send_reply("USER", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		return;
	}
	std::string username = "~" + input.substr(begsub + 1, endsub - begsub - 1);
	std::cout << username << "TEST\n";
	if ((endsub = input.find(' ', endsub + 1)) == std::string::npos)
	{
       std::string tmp =  send_reply("USER", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		return;
	}
	if ((endsub = input.find(' ', endsub + 1)) == std::string::npos)
	{
        std::string tmp = send_reply("USER", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		return;
	}
	begsub = endsub + 1;
    if ((endsub = input.find('\r')) == std::string::npos  && (endsub = input.find('\n')) == std::string::npos)
	{
        std::cout << "coucou" << std::endl;
	}
	std::string realname = input.substr(begsub + 1, endsub - begsub - 1);
	if(username.length() > USERLEN)
		username.resize(USERLEN);
	// int i = 0;
	// std::string tmp_username;
	// for(std::map<int, user>::iterator itr = my_serv.get_usermap().begin(); itr != my_serv.get_usermap().end(); itr++)
	// {
	// 	if(itr->second.get_username() == username)
	// 	{
	// 		tmp_username = username + ft_to_string(i);
	// 		i++;
	// 	}
	// }
	// username = tmp_username;
	// std::string tmp = "username already taken and was changed to : " + username + "\r\n";
	//send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	for(std::string::iterator i = username.begin(); i != username.end(); i++)
	{
		if(isforbidenuser(*i))
			*i = '$';
	}
	my_serv.get_usermap()[socket_client].set_username(username);
	my_serv.get_usermap()[socket_client].set_real_name(realname);

	// CHANGEMENT DE LA VALEUR DE _REGISTRATION DANS USER POUR SAVOIR OU ON EN EST DANS LA REGISTRATION
	if (my_serv.get_usermap()[socket_client].get_registration() == 0)
		my_serv.get_usermap()[socket_client].set_registration(2);
	else if (my_serv.get_usermap()[socket_client].get_registration() == 1)
	{
		//std::cout << "ON FINIT LA REGISTRATION DANS USER" << std::endl;
		(my_serv.get_usermap()[socket_client]).set_registration(3);
		send_welcome(socket_client, my_serv);
		my_serv.get_regi_map().insert(std::make_pair(my_serv.get_usermap()[socket_client].get_nick(), *(&(my_serv.get_usermap()[socket_client]))));
	}


	std::cout << "username:" << username << " real name:" << realname << std::endl;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}

void		DIE(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "DIE called" << std::endl;
	std::string tmp;
	(void)input;

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		////std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}
	if(my_serv.get_usermap()[socket_client].get_mode().find('o') != std::string::npos)
	{
		std::map<int, user> tmp_map = std::map<int, user>(my_serv.get_usermap());
		for(std::map<int, user>::iterator itr = tmp_map.begin(); itr != tmp_map.end(); itr++)
		{
			QUIT("QUIT server shutdown", itr->first, my_serv);
		}
		my_serv.set_shutdown(true);
	}
	else
	{
		tmp = send_reply("DIE", socket_client, my_serv, ERR_NOPRIVILEGES, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		std::cout << "WHAT WERE YOU TRYING TO DO YOU IGNORANT FOOL !" << std::endl;
	}
    std::cout << std::endl << std::endl;
}

void		INFO(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "INFO called" << std::endl;
    std::string			ret;
	user				target = (my_serv.get_usermap())[socket_client];
	std::vector<std::string>	splitted = ft_split(input, ' ');
	
	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		////std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}
	if (splitted.size() > 1 && splitted[1] !=  my_serv.get_servername())
	{
		std::string tmp = send_reply("INFO", socket_client, my_serv, ERR_NOSUCHSERVER, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else
	{
		std::string tmp = send_reply("||-||General information||-||", socket_client, my_serv, RPL_INFO, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply(my_serv.get_servername(), socket_client, my_serv, RPL_INFO, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("Version " + my_serv.get_version(), socket_client, my_serv, RPL_INFO, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("Don't hesitate to contact us at = addubois@student.42.fr, admadene@student.42.fr, fsacquin@student.42.fr ", socket_client, my_serv, RPL_INFO, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	// SENDING the END_OF_INFO reply to signify we have sent everything needed
	std::string tmp = send_reply("INFO", socket_client, my_serv, RPL_ENDOFINFO, "");
	send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	// std::cout << "input :[" << input << "]" << std::endl;
    // std::cout << "socket :" << socket_client << std::endl;
    // my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}

void		KILL(std::string input, int socket_client, server & my_serv) 
{
    std::cout << "KILL called" << std::endl;
	user				target = (my_serv.get_usermap())[socket_client];
	
	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		////std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}
	if (target.get_mode().find('o') == std::string::npos)
	{
		std::string tmp = send_reply("KILL", socket_client, my_serv, ERR_NOPRIVILEGES, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else
	{
		std::vector<std::string>	splitted = ft_split(input, ' ');
		if (splitted.size() < 3)
		{
			std::string tmp = send_reply("KILL", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		}

	}
    // std::cout << "input :[" << input << "]" << std::endl;
    // std::cout << "socket :" << socket_client << std::endl;
    // my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}

void		MODE(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "MODE called" << std::endl;
    user				& target = (my_serv.get_usermap())[socket_client];
	user				& target_2 = (my_serv.get_regi_map())[target.get_nick()];
	std::string			tmp;

	std::vector<std::string>    temp = ft_split(input, '\n');
    std::vector<std::string>    temp_2 = ft_split(temp[0], '\r');
    std::vector<std::string>    args = ft_split(temp_2[0], ' ');
	
	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

	for (unsigned long i = 0; i < temp_2.size(); i++)
	{
		std::cout << "temp_2[" << i << "] = '" << temp_2[i] << "'" << std::endl;
	}
	for (unsigned long i = 0; i < args.size(); i++)
	{
		std::cout << "args[" << i << "] = '" << args[i] << "'" << std::endl;
	}

	if (args.size() < 3)
	{
		// ERRNEEDMOREPARAMS
		tmp = send_reply("MODE", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
       	// tmp = send_reply("MODE", socket_client, my_serv, RPL_UMODEIS, "");
    	// send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);

		std::cout << "ERR_NEEDMOREPARAMS" << std::endl; 
		return ;
	}
	else if (args[1][0] == '#')
	{
		if (my_serv.get_chan_map().count(args[1]))
		{
			channel						& chan = (my_serv.get_chan_map())[args[1]];

			if (find_user(chan.get_user_list(my_serv.get_usermap()), target) == false && find_user(chan.get_op_list(my_serv.get_usermap()), target) == false)
			{
				// ERR_NOTONCHANNEL
				tmp = send_reply("MODE", socket_client, my_serv, ERR_NOTONCHANNEL, chan.get_name());
				send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
				return ;
			}
			else if (find_user(chan.get_op_list(my_serv.get_usermap()), target) == false)
			{
				//CHANOPRIVSNEEDED
				tmp = send_reply("MODE", socket_client, my_serv, ERR_CHANOPRIVSNEEDED, chan.get_name());
				send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
				return ;
			}
			unsigned long		i = 2;

			while (i < args.size())
			{
				//std::cout << "args[i] a l'entree = " << args[i] << std::endl;
				if (!(check_channel_mode_input(args[i])))
				{
					tmp = send_reply("MODE", socket_client, my_serv, ERR_UNKNOWNMODE, "");
					send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
					return ;
				}
				int				mod = args[i][0] - 44;
				unsigned long	j = 1;
				while (j < args[i].length())
				{
					//std::cout << "[2] args[i] a l'entree = " << args[i][j]<< std::endl;
					if (!(args[i][j] == '\r' || args[i][j] == '\n'))
					{
						//std::cout << target.get_nick() << " for " << args[i][j] << " with mod " << mod << std::endl;
						if (args[i][j] == 'o')
						{
							unsigned long		k = i;
							if (k == args.size() - 1)
							{
								tmp = send_reply("MODE", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
								send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
								return ;
							}
							while (k < args.size())
							{
								if (args[k][0] != '-' && args[k][0] != '+' && !(isdigit(args[k][0])))
								{
									modif_mode_channel(target, args[i][j], mod, chan, args[k], my_serv);
									args.erase(args.begin() + k);
								}
								k++;
							}
						}
						else if (args[i][j] == 'l' && mod == -1)
						{
							unsigned long		k = i;
							if (k == args.size() - 1)
							{
								tmp = send_reply("MODE", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
								send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
								return ;
							}
							while (k < args.size())
							{
								//std::cout << "[3] args[k] = " << args[k] << std::endl;
								if (isdigit(args[k][0]))
								{
									//std::cout << "jusqu'ici c'est bon avec mod = " << mod << " et la lettre = " << args[i][j] << std::endl;
									modif_mode_channel(target, args[i][j], mod, chan, args[k], my_serv);
									args.erase(args.begin() + k);
								}
								k++;
							}
							// std::cout << "args[k]: " << args[k] << std::endl;
						}
						else if (args[i][j] == 'v')
						{
							if (chan.get_chan_mode().find('m') != std::string::npos)
							{
								unsigned long		k = i;
								if (k == args.size() - 1)
								{
									tmp = send_reply("MODE", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
									send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
									return ;
								}
								while (k < args.size())
								{
									if (args[k][0] != '-' && args[k][0] != '+')
									{
										modif_mode_channel(target, args[i][j], mod, chan, args[k], my_serv);
										args.erase(args.begin() + k);
									}
									k++;
								}
							}
						}
						else if (args[i][j] == 'k' && mod == -1)
						{
							//std::cout << "nous voici" << std::endl;
							if (chan.get_key() != "")
							{
								//ERR_KEY_SET
								tmp = send_reply("MODE", socket_client, my_serv, ERR_KEYSET, chan.get_name());
								send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
								return ;
							}
							else
							{
								unsigned long		k = i;
								if (k == args.size() - 1)
								{
									tmp = send_reply("MODE", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
									send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
									return ;
								}
								while (k < args.size())
								{
									if (args[k][0] != '-' && args[k][0] != '+')
									{
										modif_mode_channel(target, args[i][j], mod, chan, args[k], my_serv);
										args.erase(args.begin() + k);
									}
									k++;
								}
							}
						}
						else if (args[i][j] == 'b')
						{
							unsigned long		k = i;
							if (k == args.size() - 1 && mod == -1)
							{
								unsigned long	s = 0;
								while (s < chan.get_ban_list().size())
								{
									tmp = send_reply((chan.get_ban_list())[s], socket_client, my_serv, RPL_BANLIST, chan.get_name());
									send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
									s++;
								}
								tmp = send_reply("MODE", socket_client, my_serv, RPL_ENDOFBANLIST, chan.get_name());
								send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
							}
							else if (k == args.size() - 1)
							{
								tmp = send_reply("MODE", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
								send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
								return ;
							}
							else
							{
								while (k < args.size())
								{
									//std::cout << "[3] args[k] = " << args[k] << std::endl;
									if (args[k][0] != '-' && args[k][0] != '+')
									{
										if (args[i][0] == '+')
										{
											unsigned long	s = 0;
											while (s < chan.get_ban_list().size())
											{
												if ((chan.get_ban_list())[s] == args[k])
													return ;
												s++;
											}
										}
										//std::cout << "jusqu'ici c'est bon avec mod = " << mod << " et la lettre = " << args[i][j] << std::endl;
										modif_mode_channel(target, args[i][j], mod, chan, args[k], my_serv);
										args.erase(args.begin() + k);
									}
									k++;
								}
							}
						}
						else
							modif_mode_channel(target, args[i][j], mod, chan, "", my_serv);
					}
					j++;
				}
				i++;
			}
			tmp = send_reply("MODE", socket_client, my_serv, RPL_CHANNELMODEIS, chan.get_name());
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			return ;
		}
		else
		{
			//ERR_NOSUCHCHANNEL
			tmp = send_reply("MODE", socket_client, my_serv, ERR_NOSUCHCHANNEL, args[1]);
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			return ;
		}
	}
	else if (args[1] != target.get_nick())
	{
		// ERR_USERSDONTMATCH
		tmp = send_reply("MODE", socket_client, my_serv, ERR_USERSDONTMATCH, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		std::cout << "ERR_USERSDONTMATCH" << std::endl;
        return ;
	}
	else
	{
		unsigned long		i = 2;

		while (i < args.size())
		{
			if (!(check_user_mode_input(args[i])))
			{
				tmp = send_reply("MODE", socket_client, my_serv, ERR_UMODEUNKNOWNFLAG, "");
				send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
				return ;
			}
			int				mod = args[i][0] - 44;
			unsigned long	j = 1;
			while (j < args[i].length())
			{
				if (!(args[i][j] == '\r' || args[i][j] == '\n'))
				{
					//std::cout << target.get_nick() << " for " << args[i][j] << " with mod " << mod << std::endl;
					modif_mode_user(target, args[i][j], mod);
					modif_mode_user(target_2, args[i][j], mod);
				}
				j++;
			}
			i++;
		}
	}
	tmp = send_reply("MODE", socket_client, my_serv, RPL_UMODEIS, "");
	send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);

	tmp = send_reply(my_serv.get_servername(), socket_client, my_serv, RPL_INFO, "");
	send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);

    std::cout << "ret :[" << tmp << "]" << std::endl;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}

//maybe has to be oper ?
void		MOTD(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "MOTD called" << std::endl;
    std::vector<std::string>	splitted = ft_split(input, ' ');

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

	if (splitted.size() > 1 && splitted[1] !=  my_serv.get_servername())
	{
		std::string tmp = send_reply("MOTD", socket_client, my_serv, ERR_NOSUCHSERVER, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else if (my_serv.get_motd().empty() == 0)
	{
		std::string tmp = send_reply("MOTD", socket_client, my_serv, RPL_MOTDSTART, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("MOTD", socket_client, my_serv, RPL_MOTD, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("MOTD", socket_client, my_serv, RPL_ENDOFMOTD, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else
	{
		std::string tmp = send_reply("MOTD", socket_client, my_serv, ERR_NOMOTD, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}

    std::cout << std::endl << std::endl;
}

void name_solo(int socket_client, server & my_serv, std::string chan)
{
	std::string tmp;
	std::string ret;
	chan.erase(std::remove(chan.begin(), chan.end(), '\n'), chan.end());
	chan.erase(std::remove(chan.begin(), chan.end(), '\r'), chan.end());
	tmp = send_reply("NAMES", socket_client, my_serv, RPL_NAMREPLY, chan);
	std::cout << "CIUIJN" << tmp << chan << std::endl;
	send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
}

void		NAMES(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "NAMES called" << std::endl;
    
	std::vector<std::string>	splitted = ft_split(input, ' ');
	std::vector<std::string>	chan;
	std::string					tmp;

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

	if (splitted.size() == 1)
	{
		std::cout << "COUCOU\n";
		return;
	}
	if (splitted[1].find(',') != std::string::npos)
	{
		std::cout << "COUCOU1\n";
		chan = ft_split(splitted[1], ',');
	}
	else if(splitted[1].find_first_of('#') == 0)
	{
		std::cout << "COUCOU2\n";
		chan.push_back(splitted[1]);
	}

	if(chan.size() > 1)
	{
		std::cout << "COUCOU3\n";
		int i = 0;
		while(i != (int)chan.size())
		{
			name_solo(socket_client, my_serv, chan[i]);
			i++;
		}
	}
	else
	{
		std::cout << "COUCOU4\n";
		name_solo(socket_client, my_serv, chan[0]);
	}
	tmp = send_reply("NAMES", socket_client, my_serv, RPL_ENDOFNAMES, " "); // maybe 
	send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
    std::cout << std::endl << std::endl;
}

// void		STATS(std::string input, int socket_client, server & my_serv) 
// { 
//     std::cout << "STATS called" << std::endl;

// 	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
// 	{
// 		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
// 		std::string tmp = ": User not authentificated\r\n";
// 		std::cout << tmp << std::endl;
// 		return;
// 	}

//     (void)my_serv;
//     std::cout << "input :[" << input << "]" << std::endl;
//     std::cout << "socket :" << socket_client << std::endl;
//     my_serv.get_usermap()[socket_client].print_user();
   
// 	std::cout << "connected time -> " << (my_serv.get_usermap()[socket_client].get_connected_time() / 60000000) % 60 << "min "; 
//     std::cout << (my_serv.get_usermap()[socket_client].get_connected_time() / 1000000) % 60;
//     std::cout << "." << my_serv.get_usermap()[socket_client].get_connected_time() / 100000 << "s" << std::endl;
// 	std::cout << "oct_recv -> " << my_serv.get_usermap()[socket_client].get_oct_recv() << std::endl;
// 	std::cout << "oct_send -> " << my_serv.get_usermap()[socket_client].get_oct_send() << std::endl;
// 	std::cout << "mess_recv -> " << my_serv.get_usermap()[socket_client].get_mess_recv() << std::endl;
// 	std::cout << "mess_send -> " << my_serv.get_usermap()[socket_client].get_mess_send() << std::endl;
//     std::cout << std::endl << std::endl;
// }

void		TIME(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "TIME called" << std::endl;

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

	std::vector<std::string>	splitted = ft_split(input, ' ');

	if (splitted.size() > 1 && splitted[1] !=  my_serv.get_servername())
	{
		std::string tmp = send_reply("INFO", socket_client, my_serv, ERR_NOSUCHSERVER, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else
	{
		time_t t; // t passed as argument in function time()
		struct tm * tt; // decalring variable for localtime()
		time (&t); //passing argument to time()
		tt = localtime(&t);
		std::string timer = "Current Day, Date and Time is = " + std::string(asctime(tt));
		std::string tmp = send_reply(timer, socket_client, my_serv, RPL_TIME, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
    std::cout << std::endl << std::endl;
}

void		VERSION(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "VERSION called" << std::endl;
    
	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

	std::vector<std::string>	splitted = ft_split(input, ' ');

	if (splitted.size() > 1 && splitted[1] !=  my_serv.get_servername())
	{
		std::string tmp = send_reply("VERSIOn", socket_client, my_serv, ERR_NOSUCHSERVER, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else
	{
    	std::string tmp;

		tmp = send_reply("VERSION", socket_client, my_serv, RPL_VERSION, " ");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}

void		WHO(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "WHO called" << std::endl;
    
	std::string			tmp;
	std::vector<std::string>    temp = ft_split(input, '\n');
    std::vector<std::string>    temp_2 = ft_split(temp[0], '\r');
    std::vector<std::string>    args = ft_split(temp_2[0], ' ');
	user						& target = (my_serv.get_usermap())[socket_client];

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

	// std::cout << "b user mode is : '" << (my_serv.get_regi_map()[target.get_nick()]).get_nick() << "'" << std::endl;
	if (args.size() == 1)
	{
		// tout afficher???
	}
	else if (args.size() == 2 && args[1][0] != '#')
	{
		std::map<std::string, user>::iterator		it = my_serv.get_regi_map().begin();
		std::map<std::string, user>::iterator		ite = my_serv.get_regi_map().end();

		while (it != ite)
		{
			if (check_name_match(target, (*it).second, args[1]) && (*it).second.get_mode().find('i') == std::string::npos)
			{
				tmp = send_reply("WHO", (*it).second.get_socket(), my_serv, RPL_WHOREPLY, "");
				if ((my_serv.get_regi_map())[(*it).second.get_nick()].get_mode().find('a') == std::string::npos)
					tmp += " H";
				else
					tmp += " G";
				if ((my_serv.get_regi_map())[(*it).second.get_nick()].get_mode().find('o') != std::string::npos)
					tmp += "* ";
				else
					tmp += " ";
				tmp += ":0 " + (*it).second.get_real_name() + "\r\n";
				send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			}
			it++;
		}
	}
	else if (args.size() == 2 && args[1][0] == '#')
	{
		if ((my_serv.get_chan_map()).count(args[1]))
		{
			channel				& chan = (my_serv.get_chan_map())[args[1]];

			if ((!(find_user(chan.get_user_list(my_serv.get_usermap()), target) || find_user(chan.get_op_list(my_serv.get_usermap()), target))) && (chan.get_chan_mode().find('s') != std::string::npos || chan.get_chan_mode().find('p') != std::string::npos)) //is user part of the channel
			{
				// do nothing
			}
			else
			{
				std::cout << "on a passe la securite" << std::endl;
				for (unsigned long i = 0; i < chan.get_user_list(my_serv.get_usermap()).size(); i++)
				{
					std::cout << "[1] on est dans la boucle avec i = " << i << std::endl;
					if ((chan.get_user_list(my_serv.get_usermap())[i]).get_mode().find('i') == std::string::npos)
					{
						std::cout << "dans le if" << std::endl;
						tmp = send_reply("WHO", (chan.get_user_list(my_serv.get_usermap()))[i].get_socket(), my_serv, RPL_WHOREPLY, "");
						if ((chan.get_user_list(my_serv.get_usermap()))[i].get_mode().find('a') == std::string::npos)
							tmp += " H";
						else
							tmp += " G";
						if ((chan.get_user_list(my_serv.get_usermap()))[i].get_mode().find('o') != std::string::npos)
							tmp += "* ";
						else
							tmp += " ";
						tmp += ":0 " + (my_serv.get_usermap())[socket_client].get_real_name() + "\r\n";
						send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
					}
				}
				for (unsigned long i = 0; i < chan.get_op_list(my_serv.get_usermap()).size(); i++)
				{
					std::cout << "[2] on est dans la boucle avec i = " << i << std::endl;
					if ((chan.get_op_list(my_serv.get_usermap())[i]).get_mode().find('i') == std::string::npos)
					{
						std::cout << "dans le if" << std::endl;
						tmp = send_reply("WHO", (chan.get_op_list(my_serv.get_usermap()))[i].get_socket(), my_serv, RPL_WHOREPLY, "");
						if ((chan.get_op_list(my_serv.get_usermap()))[i].get_mode().find('a') == std::string::npos)
							tmp += " H";
						else
							tmp += " G";
						tmp += "* ";
						tmp += ":0 " + (my_serv.get_usermap())[socket_client].get_real_name() + "\r\n";
						send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
					}
				}
			}
		}
	}
	else if (args.size() == 3 && args[1][0] != '#')
	{
		std::map<std::string, user>::iterator		it = my_serv.get_regi_map().begin();
		std::map<std::string, user>::iterator		ite = my_serv.get_regi_map().end();

		while (it != ite)
		{
			if (check_name_match(target, (*it).second, args[1]) && (*it).second.get_mode().find('o') != std::string::npos && (*it).second.get_mode().find('i') == std::string::npos)
			{
				tmp = send_reply("WHO", (*it).second.get_socket(), my_serv, RPL_WHOREPLY, "");
				if ((*it).second.get_mode().find('a') == std::string::npos)
					tmp += " H";
				else
					tmp += " G";
				if ((*it).second.get_mode().find('o') != std::string::npos)
					tmp += "* ";
				else
					tmp += " ";
				tmp += ":0 " + (*it).second.get_real_name() + "\r\n";
				send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			}
			it++;
		}
	}
	else if (args.size() == 3 && args[1][0] == '#')
	{
		if ((my_serv.get_chan_map()).count(args[1]))
		{
			channel				& chan = (my_serv.get_chan_map())[args[1]];

			if ((!(find_user(chan.get_user_list(my_serv.get_usermap()), target) || find_user(chan.get_op_list(my_serv.get_usermap()), target))) && (chan.get_chan_mode().find('s') != std::string::npos || chan.get_chan_mode().find('p') != std::string::npos)) //if user not member of channel AND channel has mode p or s
			{
				// do nothing;
			}
			else
			{
				std::cout << "on a passe la securite" << std::endl;
				for (unsigned long i = 0; i < chan.get_op_list(my_serv.get_usermap()).size(); i++)
				{
					std::cout << "[3] on est dans la boucle avec i = " << i << std::endl;
					if ((chan.get_op_list(my_serv.get_usermap())[i]).get_mode().find('i') == std::string::npos)
					{
						std::cout << "dans le if" << std::endl;
						tmp = send_reply("WHO", (chan.get_op_list(my_serv.get_usermap()))[i].get_socket(), my_serv, RPL_WHOREPLY, "");
						if ((chan.get_op_list(my_serv.get_usermap()))[i].get_mode().find('a') == std::string::npos)
							tmp += " H";
						else
							tmp += " G";
						if ((chan.get_op_list(my_serv.get_usermap()))[i].get_mode().find('o') != std::string::npos)
							tmp += "* ";
						else
							tmp += " ";
						tmp += ":0 " + (my_serv.get_usermap())[socket_client].get_real_name() + "\r\n";
						send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
					}
				}
			}
		}
	}
	tmp = send_reply("WHO", socket_client, my_serv, RPL_ENDOFWHO, "");
	send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}


void		WHOWAS(std::string input, int socket_client, server & my_serv)
{
    std::cout << "WHOWAS called" << std::endl;
    std::cout << "WHOWAS wiil always return nosuchnick error !" << std::endl;
	(void)input;
	std::string tmp = send_reply("WHOIS", socket_client, my_serv, ERR_NOSUCHNICK, "");
	send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);

} 

void		WHOIS(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "WHOIS called" << std::endl;

    std::string			tmp;
	std::vector<std::string>    temp = ft_split(input, '\n');
    std::vector<std::string>    temp_2 = ft_split(temp[0], '\r');
    std::vector<std::string>    args = ft_split(temp_2[0], ' ');
	// user						& target = (my_serv.get_usermap())[socket_client];

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

	//std::cout << "args size :" << args.size() << std::endl;
	//std::cout << "args(1) :" << args[1] << std::endl;
	//std::cout << "find(',') == npos :" << (args[1].find(',') == std::string::npos) << std::endl;
	if (args.size() == 1)
	{
		//ERR_NONICKNAMEGIVEN
		tmp = send_reply("WHOIS", socket_client, my_serv, ERR_NONICKNAMEGIVEN, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	
	}
	else if (args.size() == 2 
	&& my_serv.get_regi_map().find(args[1]) == my_serv.get_regi_map().end() \
	&& args[1].find(',') == std::string::npos)
	{
		//ERR_NOSUCHNICK
		std::cout << "ERROR NOSUCHNICK" << std::endl;
		tmp = send_reply(args[1], socket_client, my_serv, ERR_NOSUCHNICK, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else if (args.size() == 2 && args[1].find('#') == std::string::npos)
	{
		// give info on all nicknames
		std::vector<std::string>	nicks = ft_split(args[1], ',');

		for (unsigned long i = 0; i < nicks.size(); i++)
		{
			//std::cout << "nick = " << nicks[i] << std::endl;
			if (my_serv.get_regi_map().count(nicks[i]))
			{
				user		& source = my_serv.get_regi_map()[nicks[i]];

				tmp = send_reply("WHOIS", source.get_socket(), my_serv, RPL_WHOISUSER, "");
				send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
				tmp = send_reply("WHOIS", source.get_socket(), my_serv, RPL_WHOISSERVER, "");
				send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
				if (source.get_mode().find('o') != std::string::npos)
				{
					tmp = send_reply("WHOIS", source.get_socket(), my_serv, RPL_WHOISOPERATOR, "");
					send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
				}
				for (std::map<std::string, channel>::iterator it = my_serv.get_chan_map().begin(); it != my_serv.get_chan_map().end(); it++)
				{
					if ((*it).second.get_chan_mode().find('s') == std::string::npos)
					{
						if (find_user((*it).second.get_user_list(my_serv.get_usermap()), source))
						{
							if ((*it).second.get_chan_mode().find('m') != std::string::npos && (!(find_user((*it).second.get_mute_list(my_serv.get_usermap()), source))))
								tmp = send_reply("+", source.get_socket(), my_serv, RPL_WHOISCHANNELS, (*it).second.get_name());
							else
								tmp = send_reply("", source.get_socket(), my_serv, RPL_WHOISCHANNELS, (*it).second.get_name());
							send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
						}
						else if(find_user((*it).second.get_op_list(my_serv.get_usermap()), source))
						{
							if ((*it).second.get_chan_mode().find('m') != std::string::npos)
								tmp = send_reply("@+", source.get_socket(), my_serv, RPL_WHOISCHANNELS, (*it).second.get_name());
							else
								tmp = send_reply("@", source.get_socket(), my_serv, RPL_WHOISCHANNELS, (*it).second.get_name());
							send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
						}
					}
				}
			}
			else
			{
				// ERR_NOSUCHNICK
				tmp = send_reply(args[1], socket_client, my_serv, ERR_NOSUCHNICK, "");
				send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
				
				break ;
			}
		}
		tmp = send_reply("WHOIS", socket_client, my_serv, RPL_ENDOFWHOIS, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else if (args.size() == 3 && args[2] != my_serv.get_servername())
	{
		// ERR_NOSUCHSERVER
		tmp = send_reply("WHOIS", socket_client, my_serv, ERR_NOSUCHSERVER, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}

void list_solo(std::string chan, int socket_client, server & my_serv)
{
	std::cout << "ICI4\n";
	std::string					tmp;

	chan.erase(std::remove(chan.begin(), chan.end(), '\n'), chan.end());
	chan.erase(std::remove(chan.begin(), chan.end(), '\r'), chan.end());
	if(my_serv.get_chan_map()[chan].get_chan_mode().find('s') == std::string::npos)
	{
		tmp = send_reply("LIST", socket_client, my_serv, RPL_LIST, chan);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
}

void		LIST(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "LIST called" << std::endl;
    
	std::vector<std::string>	splitted = ft_split(input, ' ');
	std::vector<std::string>	chan;
	std::string					tmp;
	int i = 0;
	std::map<std::string, channel> chan_map = my_serv.get_chan_map();

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

	if(splitted.size() > 2)
	{
		std::string tmp = send_reply("LIST", socket_client, my_serv, ERR_NOSUCHSERVER, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		return;
	}
	if(splitted.size() == 2)
	{
		if (splitted[1].find(',') != std::string::npos)
		{
			std::cout << "ICI\n";
			chan = ft_split(splitted[1], ',');
			while (i != (int)chan.size())
			{
			
				if(chan[i].find_first_of('#') == 0)
					list_solo(chan[i], socket_client, my_serv);
				i++;
			}
		}
		else
		{
			std::cout << "ICI1\n";
			if(splitted[1].find_first_of('#') == 0)
				chan.push_back(splitted[1]);
			if(chan.empty() != true)
				list_solo(chan[0], socket_client, my_serv);
		}
		std::cout << "ICI2\n";
	
	}
	else
	{
		std::cout << "ICI3\n";
		for(std::map<std::string, channel>::iterator itrmap = chan_map.begin(); itrmap != chan_map.end(); itrmap++)
		{
			if(my_serv.get_chan_map()[itrmap->first].get_chan_mode().find('s') == std::string::npos)
			{
				tmp = send_reply("LIST", socket_client, my_serv, RPL_LIST, itrmap->first);
				send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			}
		}
	}
	tmp = send_reply("LIST", socket_client, my_serv, RPL_LISTEND, "");
	send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
    std::cout << std::endl << std::endl;
}

void		PING(std::string input, int socket_client, server & my_serv)
{ 
    std::cout << "PING called" << std::endl;
    std::cout << "input '" << input << "'" << std::endl;

    std::string			        ret;
	user				        target = (my_serv.get_usermap())[socket_client];
	std::vector<std::string>	splitted = ft_split(input, ' ');

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

    if (splitted.size() < 2)
    {
        ret = send_reply("PING", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
    }
    else
    {
        ret = ":" + target.get_hostname() + target.get_nick() + " PONG " + ":"  + splitted[1] + " \r\n";
    }
    send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
    
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    
    std::cout << std::endl << std::endl;
}

void		PONG(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "PONG called" << std::endl;
    
	std::cout << "input '" << input << "'" << std::endl;

    std::string			        ret;
	user				        target = (my_serv.get_usermap())[socket_client];
	std::vector<std::string>	splitted = ft_split(input, ' ');

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

    if (splitted.size() < 2)
    {
        ret = send_reply("PONG", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
    }
    else
    {
        ret = ":" + target.get_hostname() + target.get_nick() + " PING " + ":"  + splitted[1] + " \r\n";
    }
    send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
    
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    
    std::cout << std::endl << std::endl;
}

void		PART(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "PART called" << std::endl;
    std::string ret;
	std::string tmp;
	std::string msg_tmp;


    std::vector<std::string> av = ft_split(input, ' ');

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

    if (av.size() < 2)
    {
        std::cout << std::endl << "ERR_NEEDMOREPARAMS" << std::endl << std::endl;
        
        ret = send_reply("PART", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
        send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
        return;
    }
	if(av.size() >= 2)
	{
		int i = 2;
		while(i < (int)av.size())
		{
			msg_tmp += av[i] + " ";
			i++;
		}
	}
	else
	{
		msg_tmp = my_serv.get_usermap()[socket_client].get_nick() + " Left the chat";
	}
	std::cout << "MSG : " << msg_tmp << std::endl;
    std::vector<std::string> av_chan = ft_split(av[1], ',');
    std::vector<std::string>::iterator it_chan = av_chan.begin();

	

    while (it_chan != av_chan.end())
    {
        while (*(it_chan->end() - 1) == '\n' || *(it_chan->end() - 1) == '\r')
            it_chan->erase(it_chan->end() - 1);

        std::cout << "salut" << std::endl;
        if (my_serv.get_chan_map().find(*it_chan) == my_serv.get_chan_map().end() && *it_chan != my_serv.get_chan_map().begin()->first)
        {
            std::cout << std::endl << "ERR_NOSUCHCHANNEL " << std::endl << std::endl;

            ret = send_reply("PART", socket_client, my_serv, ERR_NOSUCHCHANNEL, *it_chan);
            send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);

            ++it_chan;
            continue;
        }
		std::cout << "list user :" << std::endl;
		std::vector<user> vect_user = my_serv.get_chan_map()[*it_chan].get_user_list(my_serv.get_usermap());
		for (std::vector<user>::iterator ituser = vect_user.begin(); ituser != vect_user.end(); ituser++)
		{
			std::cout << "test" << std::endl;
		}
		std::cout << "list op :" << std::endl;
		vect_user = my_serv.get_chan_map()[*it_chan].get_op_list(my_serv.get_usermap());
		for (std::vector<user>::iterator ituser = vect_user.begin(); ituser != vect_user.end(); ituser++)
		{
			std::cout << "test" << std::endl;
		}

        if (!find_user(my_serv.get_chan_map()[*it_chan].get_op_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]) \
        &&  !find_user(my_serv.get_chan_map()[*it_chan].get_user_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]))
        {
            //std::cout << std::endl << my_serv.get_usermap()[socket_client].get_nick() << " ERR_NOTONCHANNEL" << *it_chan << std::endl << std::endl;
            ret = send_reply("PART", socket_client, my_serv, ERR_NOTONCHANNEL, *it_chan);
            send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
            
        }
        if (find_user(my_serv.get_chan_map()[*it_chan].get_user_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]))
        {
            //std::cout << my_serv.get_usermap()[socket_client].get_nick() << " has been remove from " << *it_chan << " has user" << std::endl;
            my_serv.get_chan_map()[*it_chan].remove_user(my_serv.get_usermap()[socket_client]);
			std::vector<user> list = my_serv.get_chan_map()[*it_chan].get_user_list(my_serv.get_usermap());
			tmp = ":" + my_serv.get_usermap()[socket_client].get_id() + " PART " + *it_chan + "\r\n";
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			tmp = ":" + my_serv.get_usermap()[socket_client].get_id() + " PART " + *it_chan + msg_tmp + "\r\n";
			for(std::vector<user>::iterator itr = list.begin(); itr != list.end(); ++itr)
			{
				int socket = itr->get_socket();
				send(socket, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			}
			list = my_serv.get_chan_map()[*it_chan].get_op_list(my_serv.get_usermap());
			for(std::vector<user>::iterator itr = list.begin(); itr != list.end(); ++itr)
			{
				int socket = itr->get_socket();
				send(socket, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			}
        }
        if (find_user(my_serv.get_chan_map()[*it_chan].get_op_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]))
        {
           // std::cout << my_serv.get_usermap()[socket_client].get_nick() << " has been remove from " << *it_chan << " has operator" << std::endl;
            my_serv.get_chan_map()[*it_chan].remove_op_user(my_serv.get_usermap()[socket_client]);
			tmp = ":" + my_serv.get_usermap()[socket_client].get_id() + " PART " + *it_chan + "\r\n";
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			tmp = ":" + my_serv.get_usermap()[socket_client].get_id() + " PART " + *it_chan + msg_tmp + "\r\n";
			std::vector<user> list = my_serv.get_chan_map()[*it_chan].get_user_list(my_serv.get_usermap());
			for(std::vector<user>::iterator itr = list.begin(); itr != list.end(); ++itr)
			{
				int socket = itr->get_socket();
				send(socket, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			}
			list = my_serv.get_chan_map()[*it_chan].get_op_list(my_serv.get_usermap());
			for(std::vector<user>::iterator itr = list.begin(); itr != list.end(); ++itr)
			{
				int socket = itr->get_socket();
				send(socket, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			}
        }
        ++it_chan;
    }




    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}



// LISTE DE COMMANDES CHANNEL SIDE
void		INVITE(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "INVITE called" << std::endl;
    std::string ret;
	std::vector<std::string> splitted = ft_split(input, ' ');

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

	if (splitted.size() > 3)
		return;

	if (splitted.size() < 3)
	{
	    
		std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
		ret = send_reply("INVITE", socket_client, my_serv, ERR_NEEDMOREPARAMS, splitted[2]);
        send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
		return;
	}
	if (my_serv.get_regi_map().find(splitted[1]) == my_serv.get_regi_map().end() && my_serv.get_regi_map().find(splitted[1]) != my_serv.get_regi_map().begin())
	{
		std::cout << "ERR_NOSUCHNICK" << std::endl;
	    ret = send_reply(splitted[1], socket_client, my_serv, ERR_NOSUCHNICK, splitted[2]);
        unsigned long t = send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
		std::cout << "NOSUCHNICK A ETE ENVOYE POUR t = " << t << std::endl;
		return;
	}
	while (*(splitted[2].end() - 1) == '\n' || *(splitted[2].end() - 1) == '\r')// enleve les \r \n
	{
		splitted[2].erase(splitted[2].end() - 1);
	}

	if (my_serv.get_chan_map().find(splitted[2]) == my_serv.get_chan_map().end() && my_serv.get_chan_map().find(splitted[2]) != my_serv.get_chan_map().begin())
	{
		//le channel n'existe pas
		std::cout << "ERROR CHANNEL NOT FOUND" << std::endl;
		ret = send_reply(splitted[2], socket_client, my_serv, ERR_NOSUCHCHANNEL, splitted[2]);
        send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
		return;
	}

	std::cout << "channel ->" << splitted[2] << std::endl;
	if (find_user(my_serv.get_chan_map()[splitted[2]].get_op_list(my_serv.get_usermap()), my_serv.get_regi_map()[splitted[1]]) \
	||	find_user(my_serv.get_chan_map()[splitted[2]].get_user_list(my_serv.get_usermap()), my_serv.get_regi_map()[splitted[1]]))
	{
		std::cout << "ERR_USERONCHANNEL" << std::endl;
 		ret = send_reply(splitted[1], socket_client, my_serv, ERR_USERONCHANNEL, splitted[2]);
        send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
		return;
	}
	if (!find_user(my_serv.get_chan_map()[splitted[2]].get_op_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]) \
	&&	!find_user(my_serv.get_chan_map()[splitted[2]].get_user_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]))
	{
		std::cout << "ERR_NOTONCHANNEL" << std::endl;
 		ret = send_reply(splitted[1], socket_client, my_serv, ERR_NOTONCHANNEL, splitted[2]);
        send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
		return;
	}
	if (!find_user(my_serv.get_chan_map()[splitted[2]].get_op_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]))
	{
		std::cout << "ERR_CHANOPRIVSNEEDED" << std::endl;
 		ret = send_reply(splitted[1], socket_client, my_serv, ERR_CHANOPRIVSNEEDED, splitted[2]);
        send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
		return;

	}
	if (my_serv.get_regi_map()[splitted[1]].get_mode().find('a') != std::string::npos)
	{
		std::cout << "RPL_AWAY" << std::endl;
		ret = send_reply(splitted[1], socket_client, my_serv, RPL_AWAY, splitted[2]);
        send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
		return;
	}
	std::cout << "invitation envoye !" << std::endl;

	ret = send_reply(splitted[1], socket_client, my_serv, RPL_INVITING, splitted[2]);
    send(my_serv.get_regi_map()[splitted[1]].get_socket(), ret.c_str(), ret.size(), MSG_DONTWAIT);
	if (!(find_user(my_serv.get_chan_map()[splitted[2]].get_invite_list(my_serv.get_usermap()), my_serv.get_regi_map()[splitted[1]])))
		my_serv.get_chan_map()[splitted[2]].add_invite(my_serv.get_regi_map()[splitted[1]]);


    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}



void		KICK(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "KICK called" << std::endl;
    std::vector<std::string>		splitted = ft_split(input, ' ');
	std::string tmp;
	std::string msg_tmp;
	std::string msg;

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

	if(splitted.size() >= 3)
	{
		std::vector<std::string> chan = ft_split(splitted[1], ',');
		std::vector<std::string> user = ft_split(splitted[2], ',');
		if(chan.size() > 1 && user.size() != chan.size())
		{
			tmp = send_reply("KICK", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			return ;
		}
		else
		{
			if (splitted.size() >= 3)
			{
				int i = 3;
				while(i < (int)splitted.size())
				{
					msg_tmp += splitted[i] + " ";
					i++;
				}
			}
			else
			{
				msg_tmp = "Kicked from chan";
			}
			if(chan.size() == 1)
			{
				chan[0].erase(std::remove(chan[0].begin(), chan[0].end(), '\n'), chan[0].end());
				chan[0].erase(std::remove(chan[0].begin(), chan[0].end(), '\r'), chan[0].end());
				if(my_serv.get_chan_map()[chan[0]].get_op_list(my_serv.get_usermap()).empty() == true && my_serv.get_chan_map()[chan[0]].get_user_list(my_serv.get_usermap()).empty() == true)
				{
					//std::cout << "Absolutely mental" << std::endl;
					tmp = send_reply("KICK", socket_client, my_serv, ERR_NOSUCHCHANNEL, chan[0]);
					send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
					return ;
				}
				if(find_user(my_serv.get_chan_map()[chan[0]].get_op_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]) == true)
				{
					for(std::vector<std::string>::iterator itr = user.begin(); itr != user.end(); itr++)
					{
						//std::cout << "User :" << *itr << "kicked" << std::endl;
						itr->erase(std::remove(itr->begin(), itr->end(), '\n'), itr->end());
						itr->erase(std::remove(itr->begin(), itr->end(), '\r'), itr->end());
						msg = "PART " + chan[0] + " " + msg_tmp;
						std::cout << "kick msg :" << msg << std::endl;
						if(find_user(my_serv.get_chan_map()[chan[0]].get_op_list(my_serv.get_usermap()), my_serv.get_regi_map()[*itr]) == false && find_user(my_serv.get_chan_map()[chan[0]].get_user_list(my_serv.get_usermap()), my_serv.get_regi_map()[*itr]))
						{
							PART(msg, my_serv.get_regi_map()[*itr].get_socket(), my_serv);
							msg = ":" + my_serv.get_usermap()[socket_client].get_id() + " KICK " + chan[0] + " " + my_serv.get_regi_map()[*itr].get_nick() + " " + msg_tmp + "\r\n";
							send(my_serv.get_regi_map()[*itr].get_socket(), msg.c_str(), msg.length(), MSG_DONTWAIT);
						}
						else if (!(find_user(my_serv.get_chan_map()[chan[0]].get_user_list(my_serv.get_usermap()), my_serv.get_regi_map()[*itr])))
						{
							//ERR_USERNOTONCHANNEL
							msg = send_reply((my_serv.get_regi_map()[*itr]).get_nick(), socket_client, my_serv, ERR_USERNOTINCHANNEL, chan[0]);
							send(socket_client, msg.c_str(), msg.length(), MSG_DONTWAIT);
						}
					}
				}
				else
				{
					tmp = send_reply("KICK", socket_client, my_serv, ERR_CHANOPRIVSNEEDED, chan[0]);
					send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
					return ;
				}
			}
			else
			{
				int i = 0;
				for(std::vector<std::string>::iterator itr = chan.begin(); itr != chan.end(); itr++)
				{
					itr->erase(std::remove(itr->begin(), itr->end(), '\n'), itr->end());
					itr->erase(std::remove(itr->begin(), itr->end(), '\r'), itr->end());
					if(my_serv.get_chan_map()[*itr].get_op_list(my_serv.get_usermap()).empty() == true && my_serv.get_chan_map()[*itr].get_user_list(my_serv.get_usermap()).empty() == true)
					{
						tmp = send_reply("KICK", socket_client, my_serv, ERR_NOSUCHCHANNEL, *itr);
						send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
						return ;
					}
					if(find_user(my_serv.get_chan_map()[*itr].get_op_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]) == true)
					{	
						std::cout << "Chan :" << *itr << std::endl;

						user[i].erase(std::remove(user[i].begin(), user[i].end(), '\n'), user[i].end());
						user[i].erase(std::remove(user[i].begin(), user[i].end(), '\r'), user[i].end());
						std::cout << "User : " << user[i] << " kicked" << std::endl;
						msg = "PART " + *itr + " " + msg_tmp;
						if(find_user(my_serv.get_chan_map()[chan[0]].get_op_list(my_serv.get_usermap()), my_serv.get_regi_map()[*itr]) == false && find_user(my_serv.get_chan_map()[chan[0]].get_user_list(my_serv.get_usermap()), my_serv.get_regi_map()[*itr]))
						{
							PART(msg, my_serv.get_regi_map()[user[i]].get_socket(), my_serv);
							msg = ":" + my_serv.get_usermap()[socket_client].get_id() + " KICK " + *itr + " " + my_serv.get_regi_map()[user[i]].get_nick() + " " + msg_tmp + "\r\n";
							send(my_serv.get_regi_map()[user[i]].get_socket(), msg.c_str(), msg.length(), MSG_DONTWAIT);
						}
						else if (!(find_user(my_serv.get_chan_map()[chan[0]].get_user_list(my_serv.get_usermap()), my_serv.get_regi_map()[*itr])))
						{
							//ERR_USERNOTONCHANNEL
							msg = send_reply((my_serv.get_regi_map()[*itr]).get_nick(), socket_client, my_serv, ERR_USERNOTINCHANNEL, chan[0]);
							send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
						}
						i++;
					}
					else
					{
						tmp = send_reply("KICK", socket_client, my_serv, ERR_CHANOPRIVSNEEDED, *itr);
						send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
						return ;
					}

				}
			}
		}
	}
	else
	{
		tmp = send_reply("KICK", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		return ;
	}

    std::cout << std::endl << std::endl;
}

 // a voir

void		TOPIC(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "TOPIC called" << std::endl;

	std::vector<std::string>		splitted = ft_split(input, ' ');
	std::string				tmp;

	std::cout << "size :" << splitted.size() << std::endl;

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

	if(splitted.size() < 1)
	{
		tmp = send_reply("TOPIC", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else if(splitted.size() == 2)
	{
		tmp = send_reply("TOPIC", socket_client, my_serv, RPL_TOPIC, splitted[1]);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else
	{
		if(find_user(my_serv.get_chan_map()[splitted[1]].get_op_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]) == true || my_serv.get_chan_map()[splitted[1]].get_chan_mode().find('t') == std::string::npos)
		{	
			std::vector<user> list =  my_serv.get_chan_map()[splitted[1]].get_op_list(my_serv.get_usermap());
			std::string str;
			for(std::vector<std::string>::iterator itr = splitted.begin() + 2; itr != splitted.end(); itr++)
				str += *itr + " ";
			str.erase(0, 1);
			std::cout << str << std::endl;
			my_serv.get_chan_map()[splitted[1]].set_topic(str);
			for(std::vector<user>::iterator itr = list.begin(); itr != list.end(); ++itr)
			{
				std::cout << "test\n";
				int socket = itr->get_socket();
				tmp = send_reply("TOPIC", socket, my_serv, RPL_TOPIC, splitted[1]);
				send(socket, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			}
			list =  my_serv.get_chan_map()[splitted[1]].get_user_list(my_serv.get_usermap());
			for(std::vector<user>::iterator itr = list.begin(); itr != list.end(); ++itr)
			{
				std::cout << "test\n";
				int socket = itr->get_socket();
				tmp = send_reply("TOPIC", socket, my_serv, RPL_TOPIC, splitted[1]);
				send(socket, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			}
		}
		else if(find_user(my_serv.get_chan_map()[splitted[1]].get_user_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]) == true)
		{
			tmp = send_reply("TOPIC", socket_client, my_serv, ERR_CHANOPRIVSNEEDED, splitted[1]);
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		}
		else
		{
			tmp = send_reply("TOPIC", socket_client, my_serv, ERR_NOTONCHANNEL, splitted[1]);
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		}
	}
    std::cout << std::endl << std::endl;
}


// LISTE DE COMMANDES USER SIDE
void		AWAY(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "AWAY called" << std::endl;
    
    user					& target = (my_serv.get_usermap())[socket_client];
	user					& target_2 = (my_serv.get_regi_map())[target.get_nick()];
	std::vector<std::string>		splitted = ft_split(input, ' ');
	std::string				tmp;

	std::cout << "input :[" << input << "]" << std::endl;
	unsigned long			cmd_pos = input.find("AWAY");

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

	if (cmd_pos == 0 && splitted.size() > 1)
	{
		unsigned long		first_dp_pos = input.find(':');
		unsigned long		delimiter = std::min(input.find('\r'), input.find('\n'));

		std::string			away_message = input.substr(first_dp_pos + 1, delimiter - first_dp_pos - 1);//a revoir...
		target.set_away_msg(away_message);
		//std::cout << "|" << target.get_away_msg() << "|" << std::endl;
		modif_mode_user(target, 'a', 2);
		modif_mode_user(target_2, 'a', 2);
		tmp = send_reply("AWAY", socket_client, my_serv, RPL_NOWAWAY, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else
	{
		modif_mode_user(target, 'a', 3);
		modif_mode_user(target_2, 'a', 3);
		tmp = send_reply("UNAWAY", socket_client, my_serv, RPL_UNAWAY, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}


void		OPER(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "OPER called" << std::endl;
    
    user					& target = (my_serv.get_usermap())[socket_client];
	user					& target_2 = my_serv.get_regi_map()[target.get_nick()];
	std::vector<std::string>		splitted = ft_split(input, ' ');
	std::string				tmp;

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

	if (splitted.size() != 3)
	{
		// ERR_NEEDMOREPARAMS
		tmp = send_reply("OPER", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	// we can configure the server to not take any client as OPER and return ERR_NOOPERHOST all time
	else if (splitted[2] != my_serv.get_admin_pswd())
	{
		//ERR_PASSWDMISMATCH
		tmp = send_reply("OPER", socket_client, my_serv, ERR_PASSWDMISMATCH, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else
	{
		if (modif_mode_user(target, 'o', 2))
			target.set_op_name(splitted[1]);
		if (modif_mode_user(target_2, 'o', 2))
			target_2.set_op_name(splitted[1]);
		tmp = send_reply("OPER", socket_client, my_serv, RPL_YOUREOPER, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}

void		PRIVMSG(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "PRIVMSG called" << std::endl;
    
    std::vector<std::string> splitted = ft_split(input, ' '); 
    std::map<int, user> usermap = my_serv.get_usermap();    
    std::map<int, user>::iterator it = usermap.begin();
    user sender = usermap[socket_client];
    std::string ret;

    size_t i = 2;

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

    if (splitted.size() < 2 || *splitted[1].begin() == ':')
    {
       ret = send_reply(input, socket_client, my_serv, ERR_NORECIPIENT, "");
    }
    else if (splitted.size() > 2 && *splitted[2].begin() != ':')
    {
       ret = send_reply(input, socket_client, my_serv, ERR_NOTEXTTOSEND, "");
    }
	else if (splitted[1].find('*') != std::string::npos || splitted[1].find('?') != std::string::npos)
	{
		if(my_serv.get_usermap()[socket_client].get_mode().find('o') == std::string::npos)
		{
			std::string tmpm = send_reply("PRIVMSG", socket_client, my_serv, ERR_NOPRIVILEGES, "");
			send(socket_client, tmpm.c_str(), tmpm.length(), MSG_DONTWAIT);
			return;
		}
		else if (splitted[1].find('.') == std::string::npos)
		{
			std::string tmpm = "Permission Denied- WHAT WERE YOU TRYING TO DO YOU FUCKING BABOON\r\n";
			send(socket_client, tmpm.c_str(), tmpm.length(), MSG_DONTWAIT);
			return;
		}
		else if(splitted[1].find('.') != std::string::npos && std::find(splitted[1].begin() + splitted[1].find_last_of('.'), splitted[1].end(), '*') == splitted[1].end() && std::find(splitted[1].begin() + splitted[1].find_last_of('.'), splitted[1].end(), '?') == splitted[1].end())
		{
			std::map<std::string, channel>::iterator itchan = my_serv.get_chan_map().begin();
			std::string tmp_input = std::string(input);
			unsigned long tut = input.find_first_of(':');
			//ndex;
			std::cout << "PAR ICI\n";
			while (itchan != my_serv.get_chan_map().end())
			{
				if(star_name_checker(itchan->first.c_str(), splitted[1].c_str(), (int)itchan->first.length(), (int)splitted[1].length()))
				{
					/*if(tmp_input.find(splitted[1]) != std::string::npos) //for the location where mask is found
					{   
						index = tmp_input.find(splitted[1]);
      					tmp_input.replace(index, itchan->first.length(), itchan->first + ' '); //remove and replace from that position
					}*/
					tmp_input = "PRIVMSG " + itchan->first + " " + input.substr(tut, input.length() - tut);
					PRIVMSG(tmp_input, socket_client, my_serv);
					//tmp_input = input;
				}
				itchan++;
			}
			return;
		}
		else
		{
			std::string tmpm = "Permission Denied- WHAT WERE YOU TRYING TO DO YOU FUCKING BABOON\r\n";
			send(socket_client, tmpm.c_str(), tmpm.length(), MSG_DONTWAIT);
			return;
		}
	}
    else if (*splitted[1].begin() == '#')//channel  !
    {
        std::cout << "message for channel -> " << splitted[1] << std::endl;
        
        std::map<std::string, channel>::iterator itchan = my_serv.get_chan_map().begin();

        while (itchan != my_serv.get_chan_map().end())
        {
            std::cout << itchan->first << std::endl;
            ++itchan;
        }
        
        itchan = my_serv.get_chan_map().find(splitted[1]);
        if (itchan == my_serv.get_chan_map().end())//channel nexiste pas 
        {
            std::cout << "channel nexiste pas" << std::endl;
            // ret = ":" + my_serv.get_hostname() + " 401 " + sender.get_nick() + " :" + splitted[1] + " \r\n";
            ret = send_reply(input, socket_client, my_serv, ERR_NOSUCHCHANNEL, splitted[1]);
       		send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
			return;
	    }
        else if (find_ban_user(itchan->second.get_ban_list(), sender.get_id()) == true)//sender est ban du channel
        {
			std::cout << "ICI1" << std::endl;
            ret = send_reply(input, socket_client, my_serv, ERR_CANNOTSENDTOCHAN, splitted[1]);
        }
        else if (	!find_user(itchan->second.get_user_list(my_serv.get_usermap()), sender) 
        		&&	!find_user(itchan->second.get_user_list(my_serv.get_usermap()), sender) 
				&&	itchan->second.get_chan_mode().find('n') != std::string::npos)//mode n alors que sender n'est pas dans le channel
        {
			std::cout << "ICI2" << std::endl;
            ret = send_reply(input, socket_client, my_serv, ERR_CANNOTSENDTOCHAN, splitted[1]);
        }
        else if (itchan->second.get_chan_mode().find('m') != std::string::npos && find_user(itchan->second.get_mute_list(my_serv.get_usermap()), sender) == true)//mode v + m
        {
			std::cout << "ICI3" << std::endl;
            ret = send_reply(input, socket_client, my_serv, ERR_CANNOTSENDTOCHAN, splitted[1]);
        }
        else//tout va bien ou envoie tout sur le channel
        {
            std::cout << "tout est ok !" << std::endl;
          
            std::vector<user> vect_user = itchan->second.get_user_list(my_serv.get_usermap());
			std::vector<user> vect_op = itchan->second.get_op_list(my_serv.get_usermap());
            std::vector<user>::iterator ituser = vect_user.begin();
			std::vector<user>::iterator itop = vect_op.begin();
           
            ret = ":" + sender.get_id() + " PRIVMSG " + itchan->first + " ";
            while (i < splitted.size())
            {
                ret += splitted[i];
                if (i != splitted.size() - 1)
                    ret += " ";
                ++i;
            }
           
           ret += "\r\n";
            while (ituser != vect_user.end())
            {
                std::cout << "user -> " << ituser->get_nick() << std::endl;
                ++ituser;
            }
            
            ituser = vect_user.begin();

            while (ituser != vect_user.end())
            {
                
                std::cout << "ret '"<< ret << "'"<< std::endl;
                std::cout << "send to socket ->" << ituser->get_socket() << std::endl;

				int sendret = 0;
				if(*ituser != sender)
                	sendret = send(ituser->get_socket(), ret.c_str(), ret.size(), 0);
                
                std::cout << "sendret :" << sendret << std::endl <<std::endl;
                ++ituser;
            }
			while (itop != vect_op.end())
            {
                
                std::cout << "ret '"<< ret << "'"<< std::endl;
                std::cout << "send to socket ->" << itop->get_socket() << std::endl;

				int sendret = 0;
				if(*itop != sender)
                	sendret = send(itop->get_socket(), ret.c_str(), ret.size(), 0);
                
                std::cout << "sendret :" << sendret << std::endl <<std::endl;
                ++itop;
            }
            return;
        }
        std::cout << "ret '"<< ret << "'"<<std::endl;

        send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
    }
    else
    {
        std::cout << "message for user -> " << splitted[1] << std::endl;
        
        while (it != usermap.end())
        {
            if (it->second.get_nick() == splitted[1] /* || channel_name == spitted*/)// ne gere pas les channel
                break;
            ++it;
        }
        if (it == usermap.end() || 
		(my_serv.get_regi_map().find(splitted[1]) == my_serv.get_regi_map().end() && my_serv.get_regi_map().find(splitted[1]) != my_serv.get_regi_map().begin()))
        {
            std::cout << "ERROR no nick !" << std::endl;
	    	ret = ":" + my_serv.get_hostname() + " 401 " + sender.get_nick() + " :" + splitted[1] + " \r\n";//bug chelou avec \r
        }
        else if (it->second.get_mode().find('a') != std::string::npos)
        {
            ret = send_reply(splitted[1], it->first, my_serv, RPL_AWAY, "");
        }
        else 
        {


	    	ret = ":" + sender.get_id() + " PRIVMSG " + sender.get_nick() + " ";
            while (i < splitted.size())
            {
                ret += splitted[i];
                if (i != splitted.size() - 1)
                    ret += " ";
                ++i;
            }
            socket_client = it->first;
			ret += "\r\n";
        }

        std::cout << "ret '"<< ret << "'"<<std::endl;
        send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
    
    }

    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}

void		NOTICE(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "NOTICE called" << std::endl;
    
 	    std::vector<std::string> splitted = ft_split(input, ' '); 
    std::map<int, user> usermap = my_serv.get_usermap();    
    std::map<int, user>::iterator it = usermap.begin();
    user sender = usermap[socket_client];
    std::string ret;

    size_t i = 2;

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

    if (splitted.size() < 2 || *splitted[1].begin() == ':')
    {
       std::cout << "NO RECIPIENT\n";
	   return;
    }
    else if (splitted.size() > 2 && *splitted[2].begin() != ':')
    {
       std::cout << "NO TEXT TO SEND\n";
	   return;
    }
	else if (splitted[1].find('*') != std::string::npos || splitted[1].find('?') != std::string::npos)
	{
		if(my_serv.get_usermap()[socket_client].get_mode().find('o') == std::string::npos)
		{
			std::string tmpm = send_reply("NOTICE", socket_client, my_serv, ERR_NOPRIVILEGES, "");
			send(socket_client, tmpm.c_str(), tmpm.length(), MSG_DONTWAIT);
			return;
		}
		else if (splitted[1].find('.') == std::string::npos)
		{
			std::string tmpm = "Permission Denied- WHAT WERE YOU TRYING TO DO YOU IGNORANT FOOL\r\n";
			std::cout << tmpm;
			return;
		}
		else if(splitted[1].find('.') != std::string::npos && std::find(splitted[1].begin() + splitted[1].find_last_of('.'), splitted[1].end(), '*') == splitted[1].end() && std::find(splitted[1].begin() + splitted[1].find_last_of('.'), splitted[1].end(), '?') == splitted[1].end())
		{
			std::map<std::string, channel>::iterator itchan = my_serv.get_chan_map().begin();
			std::string tmp_input = std::string(input);
			unsigned long tut = input.find_first_of(':');
			//ndex;
			std::cout << "PAR ICI\n";
			while (itchan != my_serv.get_chan_map().end())
			{
				if(star_name_checker(itchan->first.c_str(), splitted[1].c_str(), (int)itchan->first.length(), (int)splitted[1].length()))
				{
					/*if(tmp_input.find(splitted[1]) != std::string::npos) //for the location where mask is found
					{   
						index = tmp_input.find(splitted[1]);
      					tmp_input.replace(index, itchan->first.length(), itchan->first + ' '); //remove and replace from that position
					}*/
					tmp_input = "NOTICE " + itchan->first + " " + input.substr(tut, input.length() - tut);
					NOTICE(tmp_input, socket_client, my_serv);
					//tmp_input = input;
				}
				itchan++;
			}
			return;
		}
		else
		{
			std::string tmpm = "Permission Denied- WHAT WERE YOU TRYING TO DO YOU IGNORANT FOOL\n";
			std::cout << tmpm;
			return;
		}
	}
    else if (*splitted[1].begin() == '#')//channel  !
    {
        std::cout << "message for channel -> " << splitted[1] << std::endl;
        
        std::map<std::string, channel>::iterator itchan = my_serv.get_chan_map().begin();

        while (itchan != my_serv.get_chan_map().end())
        {
            std::cout << itchan->first << std::endl;
            ++itchan;
        }
        
        itchan = my_serv.get_chan_map().find(splitted[1]);
		//std::cout << "ban :" << find_ban_user(itchan->second.get_ban_list(), sender.get_id()) << std::endl;
        if (itchan == my_serv.get_chan_map().end())//channel nexiste pas 
        {
            std::cout << "channel nexiste pas" << std::endl;
			return;
	    }
        else if (find_ban_user(itchan->second.get_ban_list(), sender.get_id()) == true)//sender est ban du channel
        {
			std::cout << "cannot send to chan b" << std::endl;
			return;
        }
        else if (	!find_user(itchan->second.get_user_list(my_serv.get_usermap()), sender) 
        		&&	!find_user(itchan->second.get_user_list(my_serv.get_usermap()), sender) 
				&&	itchan->second.get_chan_mode().find('n') != std::string::npos)//mode n alors que sender n'est pas dans le channel
        {
			std::cout << "Cannot end to chan n" << std::endl;
			return;
        }
        else if (itchan->second.get_chan_mode().find('m') != std::string::npos && find_user(itchan->second.get_mute_list(my_serv.get_usermap()), sender) == true)//mode v + m
        {
			std::cout << "Cannot send to chan v + m" << std::endl;
			return;
        }
        else//tout va bien ou envoie tout sur le channel
        {
            std::cout << "tout est ok !" << std::endl;
          
            std::vector<user> vect_user = itchan->second.get_user_list(my_serv.get_usermap());
			std::vector<user> vect_op = itchan->second.get_op_list(my_serv.get_usermap());
            std::vector<user>::iterator ituser = vect_user.begin();
			std::vector<user>::iterator itop = vect_op.begin();
           
            ret = ":" + sender.get_id() + " NOTICE " + itchan->first + " ";
            while (i < splitted.size())
            {
                ret += splitted[i];
                if (i != splitted.size() - 1)
                    ret += " ";
                ++i;
            }
           
           ret += "\r\n";
            while (ituser != vect_user.end())
            {
                //std::cout << "user -> " << ituser->get_nick() << std::endl;
                ++ituser;
            }
            
            ituser = vect_user.begin();

            while (ituser != vect_user.end())
            {
                
                std::cout << "ret '"<< ret << "'"<< std::endl;
                std::cout << "send to socket ->" << ituser->get_socket() << std::endl;

				int sendret = 0;
				if(*ituser != sender)
                	sendret = send(ituser->get_socket(), ret.c_str(), ret.size(), 0);
                
                std::cout << "sendret :" << sendret << std::endl <<std::endl;
                ++ituser;
            }
			while (itop != vect_op.end())
            {
                
                std::cout << "ret '"<< ret << "'"<< std::endl;
                std::cout << "send to socket ->" << itop->get_socket() << std::endl;

				int sendret = 0;
				if(*itop != sender)
                	sendret = send(itop->get_socket(), ret.c_str(), ret.size(), 0);
                
                std::cout << "sendret :" << sendret << std::endl <<std::endl;
                ++itop;
            }
            return;
        }
        std::cout << "ret '"<< ret << "'"<<std::endl;

        send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
    }
    else
    {
        std::cout << "message for user -> " << splitted[1] << std::endl;
        
        while (it != usermap.end())
        {
            if (it->second.get_nick() == splitted[1] /* || channel_name == spitted*/)// ne gere pas les channel
                break;
            ++it;
        }
        if (it == usermap.end() || 
		(my_serv.get_regi_map().find(splitted[1]) == my_serv.get_regi_map().end() && my_serv.get_regi_map().find(splitted[1]) != my_serv.get_regi_map().begin()))
        {
            std::cout << "ERROR no nick !" << std::endl;
        }
        else if (it->second.get_mode().find('a') != std::string::npos)
        {
            std::cout << "AWAY\n";
        }
        else 
        {


	    	ret = ":" + sender.get_id() + " NOTICE " + sender.get_nick() + " ";
            while (i < splitted.size())
            {
                ret += splitted[i];
                if (i != splitted.size() - 1)
                    ret += " ";
                ++i;
            }
            socket_client = it->first;
			ret += "\r\n";
        }

        std::cout << "ret '"<< ret << "'"<<std::endl;
        send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
    
    }

    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}

void		QUIT(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "QUIT called" << std::endl;
    
    std::string tmp;
	std::string quit_msg;
	std::string msg;
	std::vector<std::string> splitted = ft_split(input, ' ');
	user user_quit =  my_serv.get_usermap()[socket_client];

	if(my_serv.get_usermap()[socket_client].get_registration()  != 3)
	{
		//std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authentificated\r\n";
		std::cout << tmp << std::endl;
		return;
	}

	if (splitted.size() > 1)
	{
		int i = 1;
		while(i < (int)splitted.size())
		{
			quit_msg += splitted[i] + " ";
			i++;
		}
	}
	else
		quit_msg = "left";

	tmp = ":" + my_serv.get_usermap()[socket_client].get_id() + " QUIT " + quit_msg + "\r\n";
	send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	for(std::map<std::string, channel>::iterator itr_chan = my_serv.get_chan_map().begin(); itr_chan != my_serv.get_chan_map().end(); itr_chan++)
	{
		if(find_user(itr_chan->second.get_user_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]) == true)
		{
			msg = ":" + my_serv.get_usermap()[socket_client].get_id() + " PART " + itr_chan->first + " " + quit_msg + "\r\n";
			std::cout << "quit msg :" << msg << std::endl;
			itr_chan->second.remove_user(user_quit);
			tmp = ":" + my_serv.get_usermap()[socket_client].get_id() + " QUIT " + quit_msg + "\r\n";
			std::cout << "msg : " << msg << std::endl;
			std::vector<user> list = my_serv.get_chan_map()[itr_chan->first].get_user_list(my_serv.get_usermap());
			for(std::vector<user>::iterator itr = list.begin(); itr != list.end(); ++itr)
			{
				int socket = itr->get_socket();
				send(socket, msg.c_str(), msg.length(), MSG_DONTWAIT);
				send(socket, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			}
			list = my_serv.get_chan_map()[itr_chan->first].get_op_list(my_serv.get_usermap());
			for(std::vector<user>::iterator itr = list.begin(); itr != list.end(); ++itr)
			{
				int socket = itr->get_socket();
				send(socket, msg.c_str(), msg.length(), MSG_DONTWAIT);
				send(socket, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			}
		}
		else if(find_user(itr_chan->second.get_op_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]) == true)
		{
			msg = ":" + my_serv.get_usermap()[socket_client].get_id() + " PART " + itr_chan->first + " " + quit_msg + "\r\n";
			itr_chan->second.remove_op_user(user_quit);
			tmp = ":" + my_serv.get_usermap()[socket_client].get_id() + " QUIT " + quit_msg + "\r\n";
			std::cout << "msg : " << msg << std::endl;
			std::vector<user> list = my_serv.get_chan_map()[itr_chan->first].get_user_list(my_serv.get_usermap());
			for(std::vector<user>::iterator itr = list.begin(); itr != list.end(); ++itr)
			{
				int socket = itr->get_socket();
				send(socket, msg.c_str(), msg.length(), MSG_DONTWAIT);
				send(socket, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			}
			list = my_serv.get_chan_map()[itr_chan->first].get_op_list(my_serv.get_usermap());
			for(std::vector<user>::iterator itr = list.begin(); itr != list.end(); ++itr)
			{
				int socket = itr->get_socket();
				send(socket, msg.c_str(), msg.length(), MSG_DONTWAIT);
				send(socket, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			}

		}

		if(find_ban_user(itr_chan->second.get_ban_list(), (my_serv.get_usermap()[socket_client]).get_id()) == true)
			itr_chan->second.remove_ban(user_quit.get_id());
		if(find_user(itr_chan->second.get_mute_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]) == true)
			itr_chan->second.remove_mute(user_quit);
		if(find_user(itr_chan->second.get_invite_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]) == true)
			itr_chan->second.remove_invite(user_quit);
	}
	my_serv.get_usermap()[socket_client].set_quit(true);
	close(socket_client);
	my_serv.fd_erase(socket_client);
	my_serv.get_regi_map().erase((my_serv.get_usermap()[socket_client]).get_nick());
	my_serv.get_usermap().erase(socket_client);
    std::cout << std::endl << std::endl;
}