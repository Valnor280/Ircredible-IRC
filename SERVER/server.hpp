#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <iostream> 
#include <unistd.h>
#include <cerrno>
#include <string>
#include <netdb.h>
#include <arpa/inet.h>
#include <exception>
#include <set>
#include <map>
#include <fcntl.h>
#include "../USER/user.hpp"
#include <signal.h>


#include "../COMMANDS/commands.hpp"


class server
{
	//class user;
	public:
		server(char *port_number, char * pswd); // constructor should start evrything until listening
		~server();
	
		void loop();

		void user_read(int &sock_ready, int new_sock);
		int accept_connect(int numsock);

		void		PASS(std::string input, std::pair<int, user> client, std::map<int, user> &user_map);
	private:
	    struct ConstructorException : public std::exception
        {
			using std::exception::what;
            virtual const char * what() 
            {
                return "Constructor error\n";
            }
        };
		int _sockfd;
		char * _pswd;
		std::set<int> _open_sock;
		//sockaddr_in _sockaddr;
		int _connection;
		std::string _welcome_msg;
		std::string _hostname;
		char _buffer[512 + 1];
		fd_set _sock_client;
		fd_set _sock_ready;

		
		//MAP DES USERS
		std::map<int, user> 													_user_map;
		
		
		// MAP DES COMMANDES
		std::map<std::string, void (*)(std::string, std::pair<int, user>, std::map<int, user>&)>		cmd_map;

		
};

#endif