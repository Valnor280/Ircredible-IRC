#ifndef COMMANDS_HPP
# define COMMANDS_HPP


#include <string>
#include <iostream>
#include <map>
#include "USER/user.hpp"

//// LISTE DE COMMANDES SERVER-SIDE////
void		ADMIN(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		CAP(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		NICK(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		PASS(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		USER(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		DIE(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		HELP(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		INFO(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		ISON(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		KILL(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		LIST(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		LUSERS(std::string input, std::pair<int, user> client, std::map<int, user> &user_map); // a voir
void		MODE(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		MOTD(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		NAMES(std::string input, std::pair<int, user> client, std::map<int, user> &user_map); // l'option X est chelou
void		PART(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		PING(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		PONG(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		REHASH(std::string input, std::pair<int, user> client, std::map<int, user> &user_map); // a voir
void		STATS(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		SUMMON(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		TIME(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		USERHOST(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		USERS(std::string input, std::pair<int, user> client, std::map<int, user> &user_map); // a voir
void		VERSION(std::string input, std::pair<int, user> client, std::map<int, user> &user_map); // a voir
void		WALLOPS(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		WHO(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		WHOIS(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		WHOWAS(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);

// LISTE DE COMMANDES CHANNEL SIDE
void		INVITE(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		JOIN(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		KICK(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		KNOCK(std::string input, std::pair<int, user> client, std::map<int, user> &user_map); // a voir
void		TOPIC(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);

// LISTE DE COMMANDES USER SIDE
void		AWAY(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		NOTICE(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		OPER(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		PRIVMSG(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		QUIT(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		SETNAME(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
void		USERIP(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);


#endif
