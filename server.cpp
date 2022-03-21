#include "server.hpp"

server::server(char * port_number, char * pswd) : _pswd(pswd)
{
	FD_ZERO(&_sock_client);
	addrinfo hints, *res, *p; // res = potential adress p = adress iterator;
	memset(&hints, 0, sizeof(hints));
	
	hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_addr = NULL;
    hints.ai_canonname = NULL;
    hints.ai_next = NULL;

	int gaddres = getaddrinfo(NULL, port_number, &hints, &res);
	if(gaddres != 0)
	{
		std::cout << gai_strerror(gaddres) << "\n";
		throw ConstructorException();
	}

	for(p = res; p != NULL; p = p->ai_next)
	{
		_sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (_sockfd == -1)
		{
			std::cout << "Failed to create socket." << std::endl;
			continue;
		}
		
		if(bind(_sockfd, p->ai_addr, p->ai_addrlen) != 0)
		{
			std::cout << "error : bind fail " << std::endl;
			close(_sockfd);
			continue;
		}
		else
		{
			if (p->ai_family == AF_INET)
            {
                struct sockaddr_in *ipv4 = reinterpret_cast<struct sockaddr_in *>(p->ai_addr);
               _hostname = std::string(inet_ntoa(ipv4->sin_addr));
            }
			else
			{
				_hostname = std::string("localhost_ipv6");
			}
			std::cout << _hostname << std::endl;
			    
            if (listen(_sockfd, 10) != 0)
            {
                std::cout << "listen error" << std::endl;
            }
            else
            {  
                break ;
            }
			close(_sockfd);
		}
	}
	freeaddrinfo(res);

	if (p == NULL)
    {
        std::cout << "no addr" << std::endl;
        throw ConstructorException();
    }
	FD_SET(_sockfd, &_sock_client);
	_open_sock.insert(_sockfd);
}

void server::loop()
{
	int numsock;
	
	_sock_ready = _sock_client;
	int max_fd = *(_open_sock.rbegin());
	timeval time;

	time.tv_sec = 86400;
	time.tv_usec= 0;
	while(true)
	{
		numsock = select(max_fd + 1, &_sock_ready, NULL, NULL, &time);
		
		if(numsock == -1)
		{
			std::cout << "error select" << std::endl;
			break;
		}
		else if(numsock == 0)
		{
			std::cout << "time out : " << time.tv_sec << " sec" << std::endl;
			break;
		}
		else
		{
			int                                             new_client_socket;
			sockaddr_storage                                 new_client_address;
			socklen_t	len = sizeof(new_client_address);

			if (FD_ISSET(_sockfd, &_sock_ready))
			{
				numsock--;
				std::cout << _sockfd << std::endl;
				if ((new_client_socket = accept(_sockfd, (sockaddr *) &new_client_address, &len)) >= 0)
				{
					/*int optval = 1;
					if (setsockopt(_sockfd, SOL_SOCKET, 0, &optval, sizeof(optval)) != 0)
					{
						std::cout << "close" << std::endl;
						close(new_client_socket);
					}
					else*/
					{
						char buff[100];
						//fcntl(new_client_socket, F_SETFL, O_NONBLOCK);
						recv(new_client_socket, buff, 100, 0);
						std::cout << buff << std::endl;
						FD_SET(new_client_socket, &_sock_client);
						//_unnamed_users.insert(std::make_pair(new_client_socket, pending_socket()));
						_open_sock.insert(new_client_socket);
						std::cout << "Accepted conection\n";
					}
				}
				else
				{
					std::cerr << "Accept fail: " << strerror(errno) << "\n";
					
				}
			}
		}
	}
}

server::~server()
{
	close(_connection);
	close(_sockfd);
}