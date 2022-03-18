#include "server.hpp"

server::server(char * port_number, char * pswd) : _pswd(pswd)
{
	addrinfo hints, *res, *p; // res = potential adress p = adress iterator;
	memset(&hints, 0, sizeof(hints));
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	int gaddres = getaddrinfo(NULL, port_number, &hints, &res);
	if(gaddres != 0)
	{
		std::cout << gai_strerror(gaddres) << "\n";
		throw ConstructorException();
	}
	for(p = res; p != NULL; p = p->ai_next)
	{
		_sockfd = socket(p->ai_family, p->ai_socktype, p->ai_socktype);
		
		if(bind(_sockfd, p->ai_addr, p->ai_addrlen) != 0)
		{
			std::cout << "error : bind fail";
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
}

void server::loop()
{
	int numsock;
	int max_fd; = ??;
	timeval time;
	time.tv_sec = 60;
	time.tv_usec= 0;
	while(true)
	{
	numsock = select(max_fd + 1, &_ready_sockets, NULL, NULL, time);

	}
}
server::~server()
{
	close(_connection);
	close(_sockfd);
}