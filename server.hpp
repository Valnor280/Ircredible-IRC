#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <iostream> 
#include <unistd.h>
#include <cerrno>
#include <string>

class server
{
	public:
		server(char *port_number, char * pswd); // constructor should start evrything until listening
		~server();

		//need a loop fcnt with select and acces;
	private:
		int _sockfd;
		char * _pswd;
		sockaddr_in _sockaddr;
		int _connection;
		std::string _welcome_msg;

};