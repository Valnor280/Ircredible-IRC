#include "server.hpp"

server::server(char * port_number, char * pswd) : _pswd(pswd)
{
	_sockfd = socket(AF_INET, SOCK_STREAM, 0); //should have an error gestion
	_sockaddr.sin_family = AF_INET;
	_sockaddr.sin_addr.s_addr = INADDR_ANY; // should use get* fcnt
	_sockaddr.sin_port = htons(atoi(port_number));
	bind(_sockfd, (struct sockaddr *)(&_sockaddr), sizeof(_sockaddr)); //should have an error gestion
	listen(_sockfd, 10); // should have an error gestion

}

server::~server()
{
	close(_connection);
	close(_sockfd);
}