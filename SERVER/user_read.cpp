#include "SERVER/server.hpp"

void server::user_read(int &num_sock_ready, int new_sock)
{
	//std::map<int, std::string> pending_user(); 
	int ret;
	_sock_ready = _sock_client;
	while(num_sock_ready > 0)
	{
		if(FD_ISSET(new_sock, &_sock_ready))
		{
			std::cout << new_sock << std::endl;
			FD_CLR(new_sock, &_sock_ready);
            --num_sock_ready;
			memset(_buffer, 0, 512 + 1);
			ret = recv(new_sock, _buffer, 512, 0);
			std::cout << "socket n'" << new_sock << ". bytes received: " << ret << "\n";
			if (ret == -1)
			{
				if (errno == EAGAIN)
				{
					continue ;
				}
				std::cout << "\nsocket n'" << new_sock << " recv error: " << strerror(errno) << "\n";
			}
			else if (ret == 0)
			{
				std::cout << "\nsocket n'" << new_sock << " is closed on client side.\n";
				memset(_buffer, 0, 512 + 1);
				break;
			}
			else
			{
				std::cout << _buffer << std::endl;
				continue;
			}
			close(new_sock);
            _open_sock.erase(new_sock);
            FD_CLR(new_sock, &_sock_client);
		}
	}
}