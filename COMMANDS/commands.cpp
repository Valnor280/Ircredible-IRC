#include "commands.hpp"
#include "../SERVER/server.hpp"




// LISTE DE COMMANDES SERVER SIDE
void		CAP(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "CAP function called" << std::endl;

    client.second.set_status("capped");

(void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};


void		ADMIN(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "ADMIN called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		NICK(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "NICK called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		server::PASS(std::string input, std::pair<int, user> client, std::map<int, user> &user_map) 
{ 
    std::cout << "PASS called" << std::endl;
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
		{
			std::string tmp = ":" + user_map[client.first].get_nick() + ":You may not reregister\r\n";
			send(client.first, &tmp, 512, 0);
		}
		else
			send(client.first,": Password incorrect\r\n", 512, 0);
		user_map[client.first].set_auth(1);
	}
}
void		USER(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "USER called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		DIE(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "DIEN called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		HELP(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "HELP called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		INFO(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "INFO called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		ISON(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "ISON called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		KILL(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "KILL called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		LUSERS(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "LUSERS called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};
 // a voir
void		MODE(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "MODE called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		MOTD(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "MOTD called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		NAMES(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "NAMES called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};
 // l'option X est chelou
void		REHASH(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "REHASH called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};
 // a voir
void		STATS(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "STATS called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		SUMMON(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "SUMMON called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		TIME(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "TIME called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		USERHOST(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "USERHOST called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		USERS(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "USERS called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};
 // a voir
void		VERSION(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "VERSION called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};
 // a voir
void		WALLOPS(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "WALLOPS called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		WHO(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "WHON called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		WHOIS(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "WHOIS called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		WHOWAS(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "WHOWAS called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		LIST(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "LIST called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		PING(std::string input, std::pair<int, user> client, server & my_serv)
{ 
    std::cout << "PING called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		PONG(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "PONG called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		PART(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "PART called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};



// LISTE DE COMMANDES CHANNEL SIDE
void		INVITE(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "INVITE called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		JOIN(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "JOIN called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		KICK(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "KICK called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		KNOCK(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "KNOCK called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};
 // a voir
void		TOPIC(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "TOPIC called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};


// LISTE DE COMMANDES USER SIDE
void		AWAY(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "AWAY called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		NOTICE(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "NOTICE called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		OPER(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "OPER called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		PRIVMSG(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "PRIVMSG called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		QUIT(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "QUIT called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		SETNAME(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "SETNAME called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		USERIP(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "USERIP called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

