#include "SERVER/server.hpp"

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
			//FD_SET(new_client_socket, &_sock_ready);
			//.insert(std::make_pair(new_client_socket, pending_socket()));
			_open_sock.insert(new_client_socket);
			std::cout << "Accepted conection\n";
			
			//user creation
			std::pair<int, user> pr = std::make_pair(new_client_socket, user()); 
			_user_map.insert(pr);

			send(new_client_socket, "Enter username :", 16, 0);
		}
		else
		{
			std::cerr << "Accept fail: " << strerror(errno) << "\n";
		}
	}
	return(new_client_socket);
}