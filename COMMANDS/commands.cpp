#include "commands.hpp"





// LISTE DE COMMANDES SERVER SIDE
void		CAP(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "CAP function called" << std::endl;
    std::cout << "command :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};


void		ADMIN(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "ADMIN called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		NICK(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "NICK called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		PASS(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "PASS called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		USER(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "USER called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		DIE(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "DIEN called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		HELP(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "HELP called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		INFO(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "INFO called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		ISON(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "ISON called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		KILL(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "KILL called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		LUSERS(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "LUSERS called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};
 // a voir
void		MODE(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "MODE called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		MOTD(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "MOTD called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		NAMES(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "NAMES called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};
 // l'option X est chelou
void		REHASH(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "REHASH called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};
 // a voir
void		STATS(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "STATS called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		SUMMON(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "SUMMON called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		TIME(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "TIME called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		USERHOST(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "USERHOST called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		USERS(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "USERS called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};
 // a voir
void		VERSION(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "VERSION called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};
 // a voir
void		WALLOPS(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "WALLOPS called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		WHO(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "WHON called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		WHOIS(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "WHOIS called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		WHOWAS(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "WHOWAS called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		LIST(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "LIST called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		PING(std::string input, std::pair<int, user> client
){ 
    std::cout << "PING called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		PONG(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "PONG called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		PART(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "PART called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};



// LISTE DE COMMANDES CHANNEL SIDE
void		INVITE(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "INVITE called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		JOIN(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "JOIN called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		KICK(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "KICK called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		KNOCK(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "KNOCK called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};
 // a voir
void		TOPIC(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "TOPIC called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};


// LISTE DE COMMANDES USER SIDE
void		AWAY(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "AWAY called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		NOTICE(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "NOTICE called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		OPER(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "OPER called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		PRIVMSG(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "PRIVMSG called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		QUIT(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "QUIT called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		SETNAME(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "SETNAME called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

void		USERIP(std::string input, std::pair<int, user> client) 
{ 
    std::cout << "USERIP called" << std::endl;
    
    std::cout << "input :" << input << std::endl;
    std::cout << "socket :" << client.first << std::endl;
    client.second.print_user();
    std::cout << std::endl << std::endl;
};

