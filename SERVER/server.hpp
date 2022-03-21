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
#include <fcntl.h>
#include <signal.h>

class server
{
	public:
		server(char *port_number, char * pswd); // constructor should start evrything until listening
		~server();
	
		void loop();
		//need a loop fcnt with select and acces;
	private:
	    struct ConstructorException : std::exception
        {
            const char * what()
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
		fd_set _sock_client;
		fd_set _sock_ready;

};