#ifndef COMMANDS_HPP
# define COMMANDS_HPP
#include <string>
#include <iostream>
#include "../USER/user.hpp"

//// LISTE DE COMMANDES SERVER-SIDE////
void		ADMIN(std::string input, std::pair<int, user> client);
void		NICK(std::string input, std::pair<int, user> client);
void		PASS(std::string input, std::pair<int, user> client);
void		USER(std::string input, std::pair<int, user> client);
void		DIE(std::string input, std::pair<int, user> client);
void		HELP(std::string input, std::pair<int, user> client);
void		INFO(std::string input, std::pair<int, user> client);
void		ISON(std::string input, std::pair<int, user> client);
void		KILL(std::string input, std::pair<int, user> client);
void		LIST(std::string input, std::pair<int, user> client);
void		LUSERS(std::string input, std::pair<int, user> client); // a voir
void		MODE(std::string input, std::pair<int, user> client);
void		MOTD(std::string input, std::pair<int, user> client);
void		NAMES(std::string input, std::pair<int, user> client); // l'option X est chelou
void		PART(std::string input, std::pair<int, user> client);
void		PING(std::string input, std::pair<int, user> client);
void		PONG(std::string input, std::pair<int, user> client);
void		REHASH(std::string input, std::pair<int, user> client); // a voir
void		STATS(std::string input, std::pair<int, user> client);
void		SUMMON(std::string input, std::pair<int, user> client);
void		TIME(std::string input, std::pair<int, user> client);
void		USERHOST(std::string input, std::pair<int, user> client);
void		USERS(std::string input, std::pair<int, user> client); // a voir
void		VERSION(std::string input, std::pair<int, user> client); // a voir
void		WALLOPS(std::string input, std::pair<int, user> client);
void		WHO(std::string input, std::pair<int, user> client);
void		WHOIS(std::string input, std::pair<int, user> client);
void		WHOWAS(std::string input, std::pair<int, user> client);

// LISTE DE COMMANDES CHANNEL SIDE
void		INVITE(std::string input, std::pair<int, user> client);
void		JOIN(std::string input, std::pair<int, user> client);
void		KICK(std::string input, std::pair<int, user> client);
void		KNOCK(std::string input, std::pair<int, user> client); // a voir
void		TOPIC(std::string input, std::pair<int, user> client);

// LISTE DE COMMANDES USER SIDE
void		AWAY(std::string input, std::pair<int, user> client);
void		NOTICE(std::string input, std::pair<int, user> client);
void		OPER(std::string input, std::pair<int, user> client);
void		PRIVMSG(std::string input, std::pair<int, user> client);
void		QUIT(std::string input, std::pair<int, user> client);
void		SETNAME(std::string input, std::pair<int, user> client);
void		USERIP(std::string input, std::pair<int, user> client);


#endif
