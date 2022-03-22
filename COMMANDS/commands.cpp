#include "commands.hpp"


// LISTE DE COMMANDES SERVER SIDE
void		ADMIN(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		NICK(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		PASS(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		USER(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		DIE(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		HELP(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		INFO(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		ISON(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		KILL(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		LUSERS(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; }; // a voir
void		MODE(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		MOTD(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		NAMES(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; }; // l'option X est chelou
void		REHASH(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; }; // a voir
void		STATS(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		SUMMON(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		TIME(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		USERHOST(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		USERS(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; }; // a voir
void		VERSION(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; }; // a voir
void		WALLOPS(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		WHO(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		WHOIS(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		WHOWAS(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };

// LISTE DE COMMANDES CHANNEL SIDE
void		INVITE(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		JOIN(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		KICK(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		KNOCK(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; }; // a voir
void		TOPIC(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };

// LISTE DE COMMANDES USER SIDE
void		AWAY(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		NOTICE(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		OPER(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		PRIVMSG(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		QUIT(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		SETNAME(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
void		USERIP(std::string input, std::pair<int, user> client) { (void)input; (void)client; std::cout << "ADMIN called" << std::endl; };
