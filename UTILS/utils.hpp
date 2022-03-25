#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>
#include "SERVER/server.hpp"

class server;

bool    						isspecial(char c);
std::vector<std::string>		ft_split(std::string buffer, char sep);
std::string 					send_reply(std::string input, int socket_client, server & my_serv, int code, std::string chan);
void							send_welcome(int socket_client, server & my_serv);
std::string						ft_toupper(std::string input);
bool							check_user_mode_input(std::string arg);
bool							modif_mode_user(user & us, char c, int u);
bool							check_name_match(user & target, user & member , std::string pattern);
bool							star_name_checker(std::string str, std::string pattern);

#endif