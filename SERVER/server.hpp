#ifndef SERVER_HPP
#define SERVER_HPP

// ceci est un test

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
#include "RPL_ERR_DEFINE.hpp"
#include "UTILS/utils.hpp"
#include "CHANNEL/channel.hpp"
class server;

#include "../COMMANDS/commands.hpp"
#define USERLEN 12

class server
{
	//class user;
	public:
		server(char *port_number, char * pswd); // constructor should start evrything until listening
		~server();
	
		void loop();

		void user_read(int &sock_ready, int new_sock);
		int accept_connect(int numsock);

		char *get_pswd();

		std::string						get_servername() const;
		std::map<int, user>				&get_usermap(void);
		std::map<std::string, user>		&get_regi_map(void);
		std::string						get_hostname(void) const;
		std::string						get_version(void) const;
		std::string						get_date(void) const;
		std::string						get_motd(void) const;
		std::map<std::string, channel>			&get_chan_map(void);

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
		std::string		_servername; // SERVERNAME qui nous sert dans les reponses qu'on envoie (de base je le set dans le constructeur mais normalement on le recupere dans le fichier de config)
		std::string 	_version; // On doit avoir une version du server mais je sais pas a quoi ca correspond donc set dans le constructeur x)
		std::string		_dateofbirth; // explicite
		std::string		_motd; // message of the day
		time_t 			_time_struct;
		
		//MAP DES USERS
		std::map<int, user> 													_user_map; // map generale avec socket_client en clé

		std::map<std::string, user>											_registered_map; // map permettant d'acceder a des users par leur nickname
		
		
		// MAP DES COMMANDES
		std::map<std::string, void (*)(std::string, int, server &)>				cmd_map;

		//VEctor des chans
		std::map<std::string, channel>	_chan_map;

		
};

#endif