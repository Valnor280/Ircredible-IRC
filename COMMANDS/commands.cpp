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
};


void		ADMIN(std::string input, int socket_client, server & my_serv) 
{
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
};

void		NICK(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "NICK called" << std::endl;
    
	std::cout << socket_client << std::endl;
	if(my_serv.get_usermap()[socket_client].get_auth() == 1)
	{
		std::cout << my_serv.get_usermap()[socket_client].get_auth() << std::endl;
		std::string tmp = ": User not authenticated\r\n";
		std::cout << tmp << std::endl;
		return;
	}
    size_t  begsub;
    size_t  endsub;
    if ((begsub = input.find(' ')) == std::string::npos)
        std::cout << "Error Nick function: no space" << std::endl;
    if ((endsub = input.find('\r')) == std::string::npos  && (endsub = input.find('\n')) == std::string::npos)
        std::cout << "Error Nick function: no \\r or \\n" << std::endl;

    //recup le nick
    std::string nick = input.substr(begsub + 1, endsub - begsub - 1);

    
    
    //check nick format
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
	if (my_serv.get_usermap()[socket_client].get_registration() == 3)
	{
		my_serv.get_regi_map().erase(my_serv.get_usermap()[socket_client].get_nick());
	}
    my_serv.get_usermap()[socket_client].set_nick(nick);

	// CHANGEMENT DE LA VALEUR DE _REGISTRATION DANS USER POUR SAVOIR OU ON EN EST DANS LA REGISTRATION
	if (my_serv.get_usermap()[socket_client].get_registration() == 0)
		my_serv.get_usermap()[socket_client].set_registration(1);
	else if (my_serv.get_usermap()[socket_client].get_registration() == 2)
	{
		my_serv.get_usermap()[socket_client].set_registration(3);
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
};

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
        std::cout << "Error Pass function: no \\r or \\n" << std::endl;
	}
	std::string pass = input.substr(begsub + 1, endsub - begsub - 1);
	if (pass.compare(my_serv.get_pswd()) == 0 && my_serv.get_usermap()[socket_client].get_auth() == 1)
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
		std::string tmp = ": User not authenticated\r\n";
		std::cout << tmp << std::endl;
		return;
	}
	if (my_serv.get_usermap()[socket_client].get_username().empty() == 0)
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
        std::cout << "Error User function: no \\r or \\n" << std::endl;
	}
	std::string realname = input.substr(begsub + 1, endsub - begsub - 1);
	if(username.length() > USERLEN)
		username.resize(USERLEN);
	my_serv.get_usermap()[socket_client].set_username(username);
	my_serv.get_usermap()[socket_client].set_real_name(realname);

	// CHANGEMENT DE LA VALEUR DE _REGISTRATION DANS USER POUR SAVOIR OU ON EN EST DANS LA REGISTRATION
	if (my_serv.get_usermap()[socket_client].get_registration() == 0)
		my_serv.get_usermap()[socket_client].set_registration(2);
	else if (my_serv.get_usermap()[socket_client].get_registration() == 1)
	{
		my_serv.get_usermap()[socket_client].set_registration(3);
		send_welcome(socket_client, my_serv);
		my_serv.get_regi_map().insert(std::make_pair(my_serv.get_usermap()[socket_client].get_nick(), *(&(my_serv.get_usermap()[socket_client]))));
	}

	std::cout << "username:" << username << " real name:" << realname << std::endl;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		DIE(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "DIEN called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		INFO(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "INFO called" << std::endl;
    std::string			ret;
	user				target = (my_serv.get_usermap())[socket_client];
	std::vector<std::string>	splitted = ft_split(input, ' ');

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
};

void		ISON(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "ISON called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		KILL(std::string input, int socket_client, server & my_serv) 
{
    std::cout << "KILL called" << std::endl;
	user				target = (my_serv.get_usermap())[socket_client];
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
};

void		LUSERS(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "LUSERS called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		MODE(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "MODE called" << std::endl;
    user				& target = (my_serv.get_usermap())[socket_client];
	user				& target_2 = (my_serv.get_regi_map())[target.get_nick()];
	std::string			tmp;

	std::vector<std::string>    temp = ft_split(input, '\n');
    std::vector<std::string>    temp_2 = ft_split(temp[0], '\r');
    std::vector<std::string>    args = ft_split(temp_2[0], ' ');
	if (args.size() < 3)
	{
		// ERRNEEDMOREPARAMS
		// tmp = send_reply("MODE", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
		// send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
       	tmp = send_reply("MODE", socket_client, my_serv, RPL_UMODEIS, "");
    	send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);

		std::cout << "ERR_NEEDMOREPARAMS" << std::endl; 
		return ;
	}
	else if (args[1] != target.get_nick()) // AJOUTER LA VERIFICATION DE NOM DE CHANNELS?
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
					std::cout << target.get_nick() << " for " << args[i][j] << " with mod " << mod << std::endl;
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
};

void		MOTD(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "MOTD called" << std::endl;
    std::vector<std::string>	splitted = ft_split(input, ' ');

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
};

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
};

 // l'option X est chelou
void		REHASH(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "REHASH called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};
 // a voir
void		STATS(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "STATS called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
   
	std::cout << "connected time -> " << (my_serv.get_usermap()[socket_client].get_connected_time() / 60000000) % 60 << "min "; 
    std::cout << (my_serv.get_usermap()[socket_client].get_connected_time() / 1000000) % 60;
    std::cout << "." << my_serv.get_usermap()[socket_client].get_connected_time() / 100000 << "s" << std::endl;
	std::cout << "oct_recv -> " << my_serv.get_usermap()[socket_client].get_oct_recv() << std::endl;
	std::cout << "oct_send -> " << my_serv.get_usermap()[socket_client].get_oct_send() << std::endl;
	std::cout << "mess_recv -> " << my_serv.get_usermap()[socket_client].get_mess_recv() << std::endl;
	std::cout << "mess_send -> " << my_serv.get_usermap()[socket_client].get_mess_send() << std::endl;
    std::cout << std::endl << std::endl;
};

void		SUMMON(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "SUMMON called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		TIME(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "TIME called" << std::endl;
    
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
};

void		USERHOST(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "USERHOST called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		USERS(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "USERS called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};
 // a voir
void		VERSION(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "VERSION called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};
 // a voir
void		WALLOPS(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "WALLOPS called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		WHO(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "WHO called" << std::endl;
    
	std::string			tmp;
	std::vector<std::string>    temp = ft_split(input, '\n');
    std::vector<std::string>    temp_2 = ft_split(temp[0], '\r');
    std::vector<std::string>    args = ft_split(temp_2[0], ' ');
	user						& target = (my_serv.get_usermap())[socket_client];

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
			if (check_name_match(target, (*it).second, args[1]))
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

			for (unsigned long i = 0; i < chan.get_user_list(my_serv.get_usermap()).size(); i++)
			{
				if (check_name_match(target, (chan.get_user_list(my_serv.get_usermap()))[i], args[1]))
				{
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
		}
	}
	else if (args.size() == 3 && args[1][0] != '#')
	{
		std::map<std::string, user>::iterator		it = my_serv.get_regi_map().begin();
		std::map<std::string, user>::iterator		ite = my_serv.get_regi_map().end();

		while (it != ite)
		{
			if (check_name_match(target, (*it).second, args[1]) && (*it).second.get_mode().find('o') != std::string::npos)
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
	else if (args.size() == 3 && args[1][0] != '#')
	{
		if ((my_serv.get_chan_map()).count(args[1]))
		{
			channel				& chan = (my_serv.get_chan_map())[args[1]];

			for (unsigned long i = 0; i < chan.get_user_list(my_serv.get_usermap()).size(); i++)
			{
				if (check_name_match(target, (chan.get_user_list(my_serv.get_usermap()))[i], args[1]) && (chan.get_user_list(my_serv.get_usermap()))[i].get_mode().find('o') != std::string::npos)
				{
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
		}
	}
	tmp = send_reply("WHO", socket_client, my_serv, RPL_ENDOFWHO, "");
	send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		WHOIS(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "WHOIS called" << std::endl;

    std::string			tmp;
	std::vector<std::string>    temp = ft_split(input, '\n');
    std::vector<std::string>    temp_2 = ft_split(temp[0], '\r');
    std::vector<std::string>    args = ft_split(temp_2[0], ' ');
	// user						& target = (my_serv.get_usermap())[socket_client];

	if (args.size() == 1)
	{
		//ERR_NONICKNAMEGIVEN
		tmp = send_reply("WHOIS", socket_client, my_serv, ERR_NONICKNAMEGIVEN, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else if (args.size() == 2 && args[1].find('#') != std::string::npos)
	{
		//ERR_NOSUCHNICK
		tmp = send_reply("WHOIS", socket_client, my_serv, ERR_NOSUCHNICK, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else if (args.size() == 2 && args[1].find('#') == std::string::npos)
	{
		// give info on all nicknames
		std::vector<std::string>	nicks = ft_split(args[1], ',');

		for (unsigned long i = 0; i < nicks.size(); i++)
		{
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
			}
			else
			{
				// ERR_NOSUCHNICK
				tmp = send_reply("WHOIS", socket_client, my_serv, ERR_NOSUCHNICK, "");
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
};

void		WHOWAS(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "WHOWAS called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void list_solo(std::string chan, int socket_client, server & my_serv)
{
	std::cout << "ICI4\n";
	std::string					tmp;
	chan.erase(std::remove(chan.begin(), chan.end(), '\n'), chan.end());
	chan.erase(std::remove(chan.begin(), chan.end(), '\r'), chan.end());
	tmp = send_reply("LIST", socket_client, my_serv, RPL_LIST, chan);
	send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
}

void		LIST(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "LIST called" << std::endl;
    
	std::vector<std::string>	splitted = ft_split(input, ' ');
	std::vector<std::string>	chan;
	std::string					tmp;
	int i = 0;
	std::map<std::string, channel> chan_map = my_serv.get_chan_map();

	if(splitted.size() > 2)
	{
		if (splitted[1].find(',') != std::string::npos)
		{
			std::cout << "ICI\n";
			chan = ft_split(splitted[1], ',');
		}
		else
		{
			std::cout << "ICI1\n";
			if(splitted[1].find_first_of('#') == 0)
				chan.push_back(splitted[1]);
		}
		std::cout << "ICI2\n";
		while (i != (int)chan.size())
		{
			
			if(chan[i].find_first_of('#') == 0)
				list_solo(chan[i], socket_client, my_serv);
			i++;
		}
		

	}
	else
	{
		std::cout << "ICI3\n";
		for(std::map<std::string, channel>::iterator itrmap = chan_map.begin(); itrmap != chan_map.end(); itrmap++)
		{
			tmp = send_reply("LIST", socket_client, my_serv, RPL_LIST, itrmap->first);
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		}
	}
	tmp = send_reply("LIST", socket_client, my_serv, RPL_LISTEND, "");
	send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
    std::cout << std::endl << std::endl;
};

void		PING(std::string input, int socket_client, server & my_serv)
{ 
    std::cout << "PING called" << std::endl;
    std::cout << "input '" << input << "'" << std::endl;

    std::string			        ret;
	user				        target = (my_serv.get_usermap())[socket_client];
	std::vector<std::string>	splitted = ft_split(input, ' ');

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
};

void		PONG(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "PONG called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		PART(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "PART called" << std::endl;
    std::string ret;
	std::string tmp;
	std::string msg_tmp;


    std::vector<std::string> av = ft_split(input, ' ');

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
            std::cout << std::endl << "ERR_NOSUCHCHANNEL " << *it_chan << std::endl << std::endl;

            ret = send_reply("PART", socket_client, my_serv, ERR_NOSUCHCHANNEL, *it_chan);
            send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);

            ++it_chan;
            continue;
        }
		std::cout << "list user :" << std::endl;
		std::vector<user> vect_user = my_serv.get_chan_map()[*it_chan].get_user_list(my_serv.get_usermap());
		for (std::vector<user>::iterator ituser = vect_user.begin(); ituser != vect_user.end(); ituser++)
		{
			std::cout << ituser->get_nick() << std::endl;
		}
		std::cout << "list op :" << std::endl;
		vect_user = my_serv.get_chan_map()[*it_chan].get_op_list(my_serv.get_usermap());
		for (std::vector<user>::iterator ituser = vect_user.begin(); ituser != vect_user.end(); ituser++)
		{
			std::cout << ituser->get_nick() << std::endl;
		}

        if (!find_user(my_serv.get_chan_map()[*it_chan].get_op_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]) \
        &&  !find_user(my_serv.get_chan_map()[*it_chan].get_user_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]))
        {
            std::cout << std::endl << my_serv.get_usermap()[socket_client].get_nick() << " ERR_NOTONCHANNEL" << *it_chan << std::endl << std::endl;
            ret = send_reply("PART", socket_client, my_serv, ERR_NOTONCHANNEL, *it_chan);
            send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
            
        }
        if (find_user(my_serv.get_chan_map()[*it_chan].get_user_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]))
        {
            std::cout << my_serv.get_usermap()[socket_client].get_nick() << " has been remove from " << *it_chan << " has user" << std::endl;
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
            std::cout << my_serv.get_usermap()[socket_client].get_nick() << " has been remove from " << *it_chan << " has operator" << std::endl;
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
};



// LISTE DE COMMANDES CHANNEL SIDE
void		INVITE(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "INVITE called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};



void		KICK(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "KICK called" << std::endl;
    std::vector<std::string>		splitted = ft_split(input, ' ');
	std::string tmp;
	std::string msg_tmp;
	std::string msg;

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
					tmp = send_reply("KICK", socket_client, my_serv, ERR_NOSUCHCHANNEL, chan[0]);
					send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
					return ;
				}
				if(find_user(my_serv.get_chan_map()[chan[0]].get_op_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]) == true)
				{
					for(std::vector<std::string>::iterator itr = user.begin(); itr != user.end(); itr++)
					{
						std::cout << "User :" << *itr << "kicked" << std::endl;
						itr->erase(std::remove(itr->begin(), itr->end(), '\n'), itr->end());
						itr->erase(std::remove(itr->begin(), itr->end(), '\r'), itr->end());
						msg = "PART " + chan[0] + " " + msg_tmp;
						std::cout << "kick msg :" << msg << std::endl;
						PART(msg, my_serv.get_regi_map()[*itr].get_socket(), my_serv);
						msg = ":" + my_serv.get_usermap()[socket_client].get_id() + " KICK " + chan[0] + " " + my_serv.get_regi_map()[*itr].get_nick() + " " + msg_tmp + "\r\n";
						send(my_serv.get_regi_map()[*itr].get_socket(), msg.c_str(), msg.length(), MSG_DONTWAIT);
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
						PART(msg, my_serv.get_regi_map()[user[i]].get_socket(), my_serv);
						msg = ":" + my_serv.get_usermap()[socket_client].get_id() + " KICK " + *itr + " " + my_serv.get_regi_map()[user[i]].get_nick() + " " + msg_tmp + "\r\n";
						send(my_serv.get_regi_map()[user[i]].get_socket(), msg.c_str(), msg.length(), MSG_DONTWAIT);
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
};

 // a voir

void		TOPIC(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "TOPIC called" << std::endl;

	std::vector<std::string>		splitted = ft_split(input, ' ');
	std::string				tmp;

	std::cout << "size :" << splitted.size() << std::endl;
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
		if(find_user(my_serv.get_chan_map()[splitted[1]].get_op_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]) == true)
		{	
			std::vector<user> list =  my_serv.get_chan_map()[splitted[1]].get_op_list(my_serv.get_usermap());
			std::string str;
			for(std::vector<std::string>::iterator itr = splitted.begin() + 2; itr != splitted.end(); itr++)
				str += *itr;
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
};


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
	if (cmd_pos == 0 && splitted.size() > 1)
	{
		unsigned long		first_dp_pos = input.find(':');
		unsigned long		delimiter = std::min(input.find('\r'), input.find('\n'));

		std::string			away_message = input.substr(first_dp_pos, delimiter - first_dp_pos);
		target.set_away_msg(away_message);
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
};


void		OPER(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "OPER called" << std::endl;
    
    user					& target = (my_serv.get_usermap())[socket_client];
	user					& target_2 = my_serv.get_regi_map()[target.get_nick()];
	std::vector<std::string>		splitted = ft_split(input, ' ');
	std::string				tmp;

	if (splitted.size() != 3)
	{
		// ERR_NEEDMOREPARAMS
		tmp = send_reply("OPER", socket_client, my_serv, ERR_NEEDMOREPARAMS, "");
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	// we can configure the server to not take any client as OPER and return ERR_NOOPERHOST all time
	else if (splitted[2].substr(0, splitted[2].size() - 2) != my_serv.get_admin_pswd())
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
};

void		PRIVMSG(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "PRIVMSG called" << std::endl;
    
    std::vector<std::string> splitted = ft_split(input, ' '); 
    std::map<int, user> usermap = my_serv.get_usermap();    
    std::map<int, user>::iterator it = usermap.begin();
    user sender = usermap[socket_client];
    std::string ret;

    size_t i = 2;

    if (splitted.size() < 2 || *splitted[1].begin() == ':')
    {
       ret = send_reply(input, socket_client, my_serv, ERR_NORECIPIENT, "");
    }
    else if (splitted.size() > 2 && *splitted[2].begin() != ':')
    {
       ret = send_reply(input, socket_client, my_serv, ERR_NOTEXTTOSEND, "");
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
        
        itchan = my_serv.get_chan_map().begin();
        if (itchan == my_serv.get_chan_map().end())//channel nexiste pas 
        {
            std::cout << "channel nexiste pas" << std::endl;
            // ret = ":" + my_serv.get_hostname() + " 401 " + sender.get_nick() + " :" + splitted[1] + " \r\n";
            ret = send_reply(input, socket_client, my_serv, ERR_NOSUCHCHANNEL, splitted[1]);
        }
        else if (find_user(itchan->second.get_ban_list(), sender))//sender est ban du channel
        {
            ret = send_reply(input, socket_client, my_serv, ERR_CANNOTSENDTOCHAN, splitted[1]);
        }
        else if (	!find_user(itchan->second.get_user_list(my_serv.get_usermap()), sender) 
        		&&	!find_user(itchan->second.get_user_list(my_serv.get_usermap()), sender) 
				&&	itchan->second.get_chan_mode().find('n') != std::string::npos)//mode n alors que sender n'est pas dans le channel
        {
            ret = send_reply(input, socket_client, my_serv, ERR_CANNOTSENDTOCHAN, splitted[1]);
        }
        else if (itchan->second.get_chan_mode().find('v') != std::string::npos && itchan->second.get_chan_mode().find('m') != std::string::npos)//mode v + m
        {
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
        if (it == usermap.end())
        {
            std::cout << "ERROR no nick !" << std::endl;
	    	ret = ":" + my_serv.get_hostname() + " 401 " + sender.get_nick() + " :" + splitted[1] + " \r\n";//bug chelou avec \r
        }
        else if (it->second.get_mode().find('a') != std::string::npos)
        {
            ret = send_reply(input, it->first, my_serv, RPL_AWAY, "");
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
        }

        std::cout << "ret '"<< ret << "'"<<std::endl;
        send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);
    
    }

    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		NOTICE(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "NOTICE called" << std::endl;
    
    std::vector<std::string> splitted = ft_split(input, ' '); 
    std::map<int, user> usermap = my_serv.get_usermap();    
    std::map<int, user>::iterator it = usermap.begin();
    user sender = usermap[socket_client];
    std::string ret;

    size_t i = 2;

    if (splitted.size() < 2 || *splitted[1].begin() == ':')//ne gere pas le multi target
    {
        return;
    }
    else if (splitted.size() > 2 && *splitted[2].begin() != ':')
    {
        return;
    }
    else
    {

        while (it != usermap.end())
        {
            if (it->second.get_nick() == splitted[1] /* || channel_name == spitted*/)// ne gere pas les channel
                break;
            ++it;
        }
        if (it == usermap.end())
        {
            return;
        }
        //else if ()// RPL_CANNOTSENDTOCHAN
        else 
        {
	    	ret = ":" + sender.get_id() + " " + sender.get_nick() + " ";
            while (i < splitted.size())
            {
                ret += splitted[i];
                if (i != splitted.size() - 1)
                    ret += " ";
                ++i;
            }
            socket_client = it->first;
        }

        if (splitted.size() >= 2)
            std::cout << "split 1'" <<splitted[1]<< "'" << std::endl;
        if (splitted.size() >= 3)
            std::cout << "split 2'" <<splitted[2]<< "'" << std::endl;

        std::cout << "ret '"<< ret << "'"<<std::endl;
        // ret.insert(ret.end() - 2, ' ');
/*  
        if (pas les permission du channel)
        {
	    	ret = ":" + sender.get_id() + " 403 " + sender.get_nick() + " :No such nick/channel\r\n";
            "<client> 403 <channel> :No such channel"
        }
*/
    }
    send(socket_client, ret.c_str(), ret.size(), MSG_DONTWAIT);

    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
}

void		QUIT(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "QUIT called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		SETNAME(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "SETNAME called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		USERIP(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "USERIP called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

