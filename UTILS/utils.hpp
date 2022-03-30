#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "SERVER/server.hpp"
#include "CHANNEL/channel.hpp"
#include "USER/user.hpp"

class server;
class user;

bool    						isspecial(char c);
std::vector<std::string>		ft_split(std::string buffer, char sep);
std::string 					send_reply(std::string input, int socket_client, server & my_serv, int code, std::string chan);
void							send_welcome(int socket_client, server & my_serv);
std::string						ft_toupper(std::string input);
bool							check_user_mode_input(std::string arg);
bool							check_channel_mode_input(std::string arg);
bool							modif_mode_user(user & us, char c, int u);
bool							modif_mode_channel(user & us, char c, int u, channel & chan, std::string target, server & my_serv);
bool							is_nick_op_channel(std::string target, channel & chan, server & my_serv);

bool 							find_user(std::vector<user> vect, user user);
std::string						user_list(std::vector<user> op, std::vector<user> us);

bool							check_name_match(user & target, user & member , std::string pattern);
bool							star_name_checker(std::string str, std::string pattern);


#endif
