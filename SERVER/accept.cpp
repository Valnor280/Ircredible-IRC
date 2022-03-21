#include "server.hpp"

int server::accept_connect(int numsock)
{
	int                                             new_client_socket = 0;
	sockaddr_storage                                 new_client_address;
	socklen_t	len = sizeof(new_client_address);

	if (FD_ISSET(_sockfd, &_sock_ready))
	{
		numsock--;
		std::cout << _sockfd << std::endl;
		if ((new_client_socket = accept(_sockfd, (sockaddr *) &new_client_address, &len)) >= 0)
		{
			FD_SET(new_client_socket, &_sock_client);
			FD_SET(new_client_socket, &_sock_ready);
			//.insert(std::make_pair(new_client_socket, pending_socket()));
			_open_sock.insert(new_client_socket);
			std::cout << "Accepted conection\n";
		}
		else
		{
			std::cerr << "Accept fail: " << strerror(errno) << "\n";
		}
	}
	return(new_client_socket);
}