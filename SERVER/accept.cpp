#include "SERVER/server.hpp"

int server::accept_connect(int numsock)
{
	int                                             new_client_socket = 0;
	sockaddr_storage                                 new_client_address;
	sockaddr_in *test;
	socklen_t	len = sizeof(new_client_address);

	if (FD_ISSET(_sockfd, &_sock_ready))
	{
		numsock--;
		std::cout << _sockfd << std::endl;
		if ((new_client_socket = accept(_sockfd, (sockaddr *) &new_client_address, &len)) >= 0)
		{
			FD_SET(new_client_socket, &_sock_client);			
			_open_sock.insert(new_client_socket);
			std::cout << "Accepted conection\n";
			test = (sockaddr_in *) &new_client_address;
			_user_map.insert(std::make_pair(new_client_socket, user()));
			_user_map[new_client_socket].set_first_connect();
			_user_map[new_client_socket].set_hostname(std::string(inet_ntoa(test->sin_addr)));
			_user_map[new_client_socket].set_socket(new_client_socket);
		
		}
		else
		{
			std::cerr << "Accept fail: " << strerror(errno) << "\n";
		}
	}
	return(new_client_socket);
}
