#include "commands.hpp"





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
        std::cout << "************ ERR_ERRONEUSNICKNAME (432) *****************" << std::endl;
        //"<client> <nick> :Erroneus nickname"
        return;
    }
    for(std::string::iterator it = nick.begin(); it != nick.end(); ++it)
        if (!isspecial(*it) && !isalnum(*it) && *it != '-')
        {
            std::cout << "************ ERR_ERRONEUSNICKNAME (432) *****************" << std::endl;
            //"<client> <nick> :Erroneus nickname"
            return;
        }


    //check si il existe
    for (std::map<int, user>::iterator itr = my_serv.get_usermap().begin(); itr != my_serv.get_usermap().end(); ++itr)
    {
        if (itr->second.get_nick() == nick)
        {
            std::cout << "************ ERROR : ERR_NICKNAMEINUSE (433) *****************" << std::endl;
            //"<client> <nick> :Nickname is already in use"
            return;
        }
    }
    client.second.set_nick(nick);
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		PASS(std::string input, std::pair<int, user> client, server & my_serv) 
{ 
    std::cout << "PASS called" << std::endl;
    
    (void)my_serv;
    std::cout << "input :[" << input << "]" << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

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

