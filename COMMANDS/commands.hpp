#ifndef COMMANDS_HPP
# define COMMANDS_HPP


#include <string>
#include <iostream>
#include <map>
#include "USER/user.hpp"
#include "SERVER/server.hpp"
#include "UTILS/utils.hpp"

// #define RPL_WELCOME(client, network_name, id) (client + " :Welcome to the " + network_name + " Network, " + id)

//// LISTE DE COMMANDES SERVER-SIDE////
void		ADMIN(std::string input, std::pair<int, user> client, server & my_serv);
void		CAP(std::string input, std::pair<int, user> client, server & my_serv);
void		NICK(std::string input, std::pair<int, user> client, server & my_serv);
void		PASS(std::string input, std::pair<int, user> client, server & my_serv);
void		USER(std::string input, std::pair<int, user> client, server & my_serv);
void		DIE(std::string input, std::pair<int, user> client, server & my_serv);
void		HELP(std::string input, std::pair<int, user> client, server & my_serv);
void		INFO(std::string input, std::pair<int, user> client, server & my_serv);
void		ISON(std::string input, std::pair<int, user> client, server & my_serv);
void		KILL(std::string input, std::pair<int, user> client, server & my_serv);
void		LIST(std::string input, std::pair<int, user> client, server & my_serv);
void		LUSERS(std::string input, std::pair<int, user> client, server & my_serv); // a voir
void		MODE(std::string input, std::pair<int, user> client, server & my_serv);
void		MOTD(std::string input, std::pair<int, user> client, server & my_serv);
void		NAMES(std::string input, std::pair<int, user> client, server & my_serv); // l'option X est chelou
void		PART(std::string input, std::pair<int, user> client, server & my_serv);
void		PING(std::string input, std::pair<int, user> client, server & my_serv);
void		PONG(std::string input, std::pair<int, user> client, server & my_serv);
void		REHASH(std::string input, std::pair<int, user> client, server & my_serv); // a voir
void		STATS(std::string input, std::pair<int, user> client, server & my_serv);
void		SUMMON(std::string input, std::pair<int, user> client, server & my_serv);
void		TIME(std::string input, std::pair<int, user> client, server & my_serv);
void		USERHOST(std::string input, std::pair<int, user> client, server & my_serv);
void		USERS(std::string input, std::pair<int, user> client, server & my_serv); // a voir
void		VERSION(std::string input, std::pair<int, user> client, server & my_serv); // a voir
void		WALLOPS(std::string input, std::pair<int, user> client, server & my_serv);
void		WHO(std::string input, std::pair<int, user> client, server & my_serv);
void		WHOIS(std::string input, std::pair<int, user> client, server & my_serv);
void		WHOWAS(std::string input, std::pair<int, user> client, server & my_serv);

// LISTE DE COMMANDES CHANNEL SIDE
void		INVITE(std::string input, std::pair<int, user> client, server & my_serv);
void		JOIN(std::string input, std::pair<int, user> client, server & my_serv);
void		KICK(std::string input, std::pair<int, user> client, server & my_serv);
void		KNOCK(std::string input, std::pair<int, user> client, server & my_serv); // a voir
void		TOPIC(std::string input, std::pair<int, user> client, server & my_serv);

// LISTE DE COMMANDES USER SIDE
void		AWAY(std::string input, std::pair<int, user> client, server & my_serv);
void		NOTICE(std::string input, std::pair<int, user> client, server & my_serv);
void		OPER(std::string input, std::pair<int, user> client, server & my_serv);
void		PRIVMSG(std::string input, std::pair<int, user> client, server & my_serv);
void		QUIT(std::string input, std::pair<int, user> client, server & my_serv);
void		SETNAME(std::string input, std::pair<int, user> client, server & my_serv);
void		USERIP(std::string input, std::pair<int, user> client, server & my_serv);


#endif
