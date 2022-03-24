#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>
#include "SERVER/server.hpp"

bool    						isspecial(char c);
std::vector<std::string>		ft_split(std::string buffer, char sep);
std::string 					send_reply(std::string input, int socket_client, server & my_serv, int code);
void							send_welcome(int socket_client, server & my_serv);
<<<<<<< HEAD
=======
std::string						ft_toupper(std::string input);
>>>>>>> master

#endif