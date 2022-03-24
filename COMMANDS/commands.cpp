#include "commands.hpp"
#include "../SERVER/server.hpp"




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
		std::string tmp = send_reply("ADMIN", socket_client, my_serv, ERR_NOSUCHSERVER);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else
	{
		std::string tmp = send_reply("ADMIN", socket_client, my_serv, RPL_ADMINME);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("ADMIN", socket_client, my_serv, RPL_ADMINLOC1);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("ADMIN", socket_client, my_serv, RPL_ADMINLOC2);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("ADMIN", socket_client, my_serv, RPL_ADMINEMAIL);
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
        std::string tmp = send_reply("NICK", socket_client, my_serv, ERR_ERRONEUSNICKNAME);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
        //"<client> <nick> :Erroneus nickname"
        return;
    }
    for(std::string::iterator it = nick.begin(); it != nick.end(); ++it)
        if (!isspecial(*it) && !isalnum(*it) && *it != '-')
        {
            std::string tmp = send_reply("NICK", socket_client, my_serv, ERR_ERRONEUSNICKNAME);
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
            //"<client> <nick> :Erroneus nickname"
            return;
        }


    //check si il existe
    for (std::map<int, user>::iterator itr = my_serv.get_usermap().begin(); itr != my_serv.get_usermap().end(); ++itr)
    {
        if (itr->second.get_nick() == nick)
        {
            std::string tmp = send_reply(nick, socket_client, my_serv, ERR_NICKNAMEINUSE);
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
            //"<client> <nick> :Nickname is already in use"
            return;
        }
    }
    my_serv.get_usermap()[socket_client].set_nick(nick);

	// CHANGEMENT DE LA VALEUR DE _REGISTRATION DANS USER POUR SAVOIR OU ON EN EST DANS LA REGISTRATION
	if (my_serv.get_usermap()[socket_client].get_registration() == 0)
		my_serv.get_usermap()[socket_client].set_registration(1);
	else if (my_serv.get_usermap()[socket_client].get_registration() == 2)
	{
		my_serv.get_usermap()[socket_client].set_registration(3);
		send_welcome(socket_client, my_serv);
		my_serv.get_regi_map().insert(std::make_pair(my_serv.get_usermap()[socket_client].get_nick(), my_serv.get_usermap()[socket_client]));
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
        std::string tmp = send_reply("PASS", socket_client, my_serv, ERR_NEEDMOREPARAMS);
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
			std::string tmp = send_reply("PASS", socket_client, my_serv, ERR_ALREADYREGISTRED);
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		}
		else
		{
			std::string tmp = send_reply("PASS", socket_client, my_serv, ERR_PASSWDMISMATCH);
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
		std::string tmp = send_reply("USER", socket_client, my_serv, ERR_ALREADYREGISTRED);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		return;
	}
	size_t  begsub;
    size_t  endsub;
    if ((begsub = input.find(' ')) == std::string::npos)
	{
        std::string tmp = send_reply("USER", socket_client, my_serv, ERR_NEEDMOREPARAMS);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		return;
	}
	else if ((endsub = input.find(' ', begsub + 1)) == std::string::npos)
	{
		std::string tmp = send_reply("USER", socket_client, my_serv, ERR_NEEDMOREPARAMS);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		return;
	}
	std::string username = "~" + input.substr(begsub + 1, endsub - begsub - 1);
	std::cout << username << "TEST\n";
	if ((endsub = input.find(' ', endsub + 1)) == std::string::npos)
	{
       std::string tmp =  send_reply("USER", socket_client, my_serv, ERR_NEEDMOREPARAMS);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		return;
	}
	if ((endsub = input.find(' ', endsub + 1)) == std::string::npos)
	{
        std::string tmp = send_reply("USER", socket_client, my_serv, ERR_NEEDMOREPARAMS);
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
		my_serv.get_regi_map().insert(std::make_pair(my_serv.get_usermap()[socket_client].get_nick(), my_serv.get_usermap()[socket_client]));
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

void		HELP(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "HELP called" << std::endl;
    
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
		std::string tmp = send_reply("INFO", socket_client, my_serv, ERR_NOSUCHSERVER);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else
	{
		std::string tmp = send_reply("||-||General information||-||", socket_client, my_serv, RPL_INFO);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply(my_serv.get_servername(), socket_client, my_serv, RPL_INFO);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("Version " + my_serv.get_version(), socket_client, my_serv, RPL_INFO);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("Don't hesitate to contact us at = addubois@student.42.fr, admadene@student.42.fr, fsacquin@student.42.fr ", socket_client, my_serv, RPL_INFO);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	// SENDING the END_OF_INFO reply to signify we have sent everything needed
	std::string tmp = send_reply("INFO", socket_client, my_serv, RPL_ENDOFINFO);
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
		std::string tmp = send_reply("KILL", socket_client, my_serv, ERR_NOPRIVILEGES);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else
	{
		std::vector<std::string>	splitted = ft_split(input, ' ');
		if (splitted.size() < 3)
		{
			std::string tmp = send_reply("KILL", socket_client, my_serv, ERR_NEEDMOREPARAMS);
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
    user				target = (my_serv.get_usermap())[socket_client];

	std::vector<std::string>	args = ft_split(input, ' ');
	if (args.size() < 3)
	{
		// ERRNEEDMOREPARAMS
	}
	else if (args[1] != target.get_nick()) // AJOUTER LA VERIFICATION DE NOM DE CHANNELS?
	{
		// ERR_USERSDONTMATCH
	}
	else
	{
		unsigned long		i = 2;

		while (i < args.size())
		{
			if (check_mode_input(args[i]))
			{
				//ERR_UMODEUNKNOWNFLAG
			}

			i++;
		}
	}


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
		std::string tmp = send_reply("MOTD", socket_client, my_serv, ERR_NOSUCHSERVER);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else if (my_serv.get_motd().empty() == 0)
	{
		std::string tmp = send_reply("MOTD", socket_client, my_serv, RPL_MOTDSTART);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("MOTD", socket_client, my_serv, RPL_MOTD);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("MOTD", socket_client, my_serv, RPL_ENDOFMOTD);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else
	{
		std::string tmp = send_reply("MOTD", socket_client, my_serv, ERR_NOMOTD);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}

    std::cout << std::endl << std::endl;
};

void		NAMES(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "NAMES called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
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
		std::string tmp = send_reply("INFO", socket_client, my_serv, ERR_NOSUCHSERVER);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
	else
	{
		time_t t; // t passed as argument in function time()
		struct tm * tt; // decalring variable for localtime()
		time (&t); //passing argument to time()
		tt = localtime(&t);
		std::string timer = "Current Day, Date and Time is = " + std::string(asctime(tt));
		std::string tmp = send_reply(timer, socket_client, my_serv, RPL_TIME);
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
    std::cout << "WHON called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		WHOIS(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "WHOIS called" << std::endl;
    
    (void)my_serv;
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

void		LIST(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "LIST called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		PING(std::string input, int socket_client, server & my_serv)
{ 
    std::cout << "PING called" << std::endl;
    
    (void)my_serv;
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
    
    (void)my_serv;
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

void		JOIN(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "JOIN called" << std::endl;
    
	std::vector<std::string>	splitted = ft_split(input, ' ');

	if (splitted[1].find(',') > 0)
	{
		std::vector<std::string>	chan = ft_split(splitted[1], ',');
	}
	if (splitted.size() > 2)
	{
		std::vector<std::string>	key;
		if(splitted[2].find(',') > 0)
			key = ft_split(splitted[2], ',');
		else
			key.push_back(splitted[2]);
	}

    std::cout << std::endl << std::endl;
};

void		KICK(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "KICK called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		KNOCK(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "KNOCK called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};
 // a voir
void		TOPIC(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "TOPIC called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};


// LISTE DE COMMANDES USER SIDE
void		AWAY(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "AWAY called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		NOTICE(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "NOTICE called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		OPER(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "OPER called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

void		PRIVMSG(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "PRIVMSG called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << socket_client << std::endl;
    my_serv.get_usermap()[socket_client].print_user();
    std::cout << std::endl << std::endl;
};

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

