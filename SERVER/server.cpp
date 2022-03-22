#include "server.hpp"
#include <set>

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
	int retbuff = 0;
	int t;
	int max_fd;
	
	while(true)
	{
		max_fd = *(_open_sock.rbegin());
		_sock_ready = _sock_client;
		timeval time;

		time.tv_sec = 0;
		time.tv_usec= 50;
		numsock = select(max_fd + 1, &_sock_ready, NULL, NULL, &time);
		if(numsock == -1)
		{
			std::cout << "error select" << std::endl;
			break;
		}
		/*else if(numsock == 0)
		{
			std::cout << "time out : " << time.tv_sec << " sec" << std::endl;
		}*/
		else
		{
			t = accept_connect(numsock);
			//if(t != 0)
			 	//user_read(numsock, t);
		}
		for(std::set<int>::iterator itr = _open_sock.begin(); itr != _open_sock.end(); itr++)
		{
			if ( *itr != _sockfd && FD_ISSET(*itr, &_sock_client))
			{
				//		std::cout << "before recv" << std::endl;
				if ((retbuff = recv(*itr, _buffer, 512, MSG_DONTWAIT)) > 0)
				{
					_buffer[retbuff] = 0;
					std::cout << "msg : " << _buffer << "socket :" << *itr << std::endl;
					/*for (int k = 0; k < FD_SETSIZE; ++k)
						if (k != *itr && FD_ISSET(k, &_sock_client))
						send(k, _buffer, retbuff, 0);*/
				}
				else if(retbuff == 0)
				{
					std::cout << "\nsocket n'" << *itr << " is closed on client side.\n";
					close(*itr);
            		FD_CLR(*itr, &_sock_client);
					_open_sock.erase(*itr);
					if (_open_sock.empty() == 0)
						break;
				}
				//	std::cout << "after recv" << std::endl;
				//FD_CLR(*itr, &_sock_client);
			}
		}
	}
}

server::~server()
{
	close(_connection);
	close(_sockfd);
}


// LISTE DE COMMANDES SERVER SIDE
void		server::ADMIN(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::NICK(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::PASS(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::USER(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::DIE(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::HELP(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::INFO(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::ISON(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::KILL(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::LUSERS(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; }; // a voir
void		server::MODE(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::MOTD(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::NAMES(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; }; // l'option X est chelou
void		server::REHASH(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; }; // a voir
void		server::STATS(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::SUMMON(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::TIME(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::USERHOST(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::USERS(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; }; // a voir
void		server::VERSION(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; }; // a voir
void		server::WALLOPS(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::WHO(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::WHOIS(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::WHOWAS(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };

// LISTE DE COMMANDES CHANNEL SIDE
void		server::INVITE(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::JOIN(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::KICK(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::KNOCK(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; }; // a voir
void		server::TOPIC(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };

// LISTE DE COMMANDES USER SIDE
void		server::AWAY(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::NOTICE(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::OPER(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::PRIVMSG(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::QUIT(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::SETNAME(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };
void		server::USERIP(std::string input) { (void)input; std::cout << "ADMIN called" << std::endl; };