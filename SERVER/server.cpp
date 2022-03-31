

#include "server.hpp"
#include <set>



server::server(char * port_number, char * pswd) : _pswd(pswd), _servername("Ircredible_IRC"), _version("2.0"), _motd("RTFM!"), _admin_pswd("pswd"), _shutdown(false)
{
	// SERVER-SIDE
	cmd_map["ADMIN"] = &ADMIN;
	cmd_map["CAP"] = &CAP;
	cmd_map["NICK"] = &NICK;
	cmd_map["PASS"] = &PASS;
	cmd_map["USER"] = &USER;
	cmd_map["DIE"] = &DIE;
	cmd_map["INFO"] = &INFO;
	cmd_map["KILL"] = &KILL;
	cmd_map["LIST"] = &LIST;
	cmd_map["MODE"] = &MODE;
	cmd_map["MOTD"] = &MOTD;
	cmd_map["NAMES"] = &NAMES;
	cmd_map["PART"] = &PART;
	cmd_map["PING"] = &PING;
	cmd_map["PONG"] = &PONG;
	cmd_map["STATS"] = &STATS;
	cmd_map["TIME"] = &TIME;
	cmd_map["VERSION"] = &VERSION;
	cmd_map["WHO"] = &WHO;
	cmd_map["WHOIS"] = &WHOIS;

	// CHANNEL-SIDE
	cmd_map["INVITE"] = &INVITE;
	cmd_map["JOIN"] = &JOIN;
	cmd_map["KICK"] = &KICK;
	cmd_map["TOPIC"] = &TOPIC;

	// USER-SIDE
	cmd_map["AWAY"] = &AWAY;
	cmd_map["NOTICE"] = &NOTICE;
	cmd_map["OPER"] = &OPER;
	cmd_map["PRIVMSG"] = &PRIVMSG;
	cmd_map["QUIT"] = &QUIT;

   	_time_struct = time(0);
	// std::vector<std::string>		test = ft_split("PING 0.0.0.0\r\n", ' ');
	// for (unsigned long i = 0; i < test.size(); i++)
	// {
	// 	std::cout << test[i] << std::endl;
	// }
   
   	// convert now to string form
   	char* dt = ctime(&_time_struct);

	this->_dateofbirth = dt;
	_dateofbirth.resize(_dateofbirth.size() - 1);
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

	// testing macros
	// 	user	test;
	// test.set_nick("jay");
	// test.set_username("johnny");
	// test.set_real_name("Johnny Cool");
	// test.set_status("registered");
	// test.set_hostname(_hostname);
	// std::cout << RPL_WELCOME(":server_example.com", "Ircredible IRC", test.get_nick() + "!" + test.get_username() + "@" + test.get_hostname()) << std::endl;
}

void server::loop()
{
	int numsock;
	long int retbuff = 0;
	long int real_ret = 0;
	int t;
	int max_fd;
	
	std::string	str_buff;
	size_t		str_index;
	std::map<int, user>::iterator user_itr;

	
	while(true)
	{
		max_fd = *(_open_sock.rbegin());
		_sock_ready = _sock_client;
		timeval time;

		time.tv_sec = 0;
		time.tv_usec= 10;
		numsock = select(max_fd + 1, &_sock_ready, NULL, NULL, &time);
		if(numsock == -1)
		{
			std::cout << "error select" << std::endl;
			break;
		}
		else
		{
			t = accept_connect(numsock);
		}
		for(std::set<int>::iterator itr = _open_sock.begin(); itr != _open_sock.end(); itr++)
		{
			if ( *itr != _sockfd && FD_ISSET(*itr, &_sock_client))
			{
				//		std::cout << "before recv" << std::endl;

				bzero(_buffer, 512);
				retbuff = recv(*itr, _buffer, 512, MSG_DONTWAIT);
				if (retbuff > 0)
				{
					_user_map[*itr].add_mess_recv(1);
					_user_map[*itr].add_oct_recv((unsigned long)retbuff);
					//_buffer[retbuff] = 0;
					std::cout << "msg : " << _buffer << "socket :" << *itr << std::endl;
					
					user_itr = _user_map.find(*itr);
				
					//parse message
					_user_map[*itr].set_buff(_buffer);
					std::cout << "cmd : " << _user_map[*itr].get_buff() << std::endl;
					real_ret += retbuff;
					str_buff = _user_map[*itr].get_buff();
					if(str_buff.find('\r') != std::string::npos && str_buff.find('\n') != std::string::npos )
					{
						std::cout << "je passe par la\n";
						int ivc = 0;
						while (!str_buff.empty() && ivc < 5)
						{
							std::vector<std::string>		input_temp = ft_split(str_buff, '\n');
							std::vector<std::string>		input_temp_2 = ft_split(input_temp[0], '\r');
							std::vector<std::string>		input = ft_split(input_temp_2[0], ' ');
							std::cout << "str_buff '" << str_buff << "'" << std::endl;
							if (cmd_map.find(ft_toupper(input[0])) == cmd_map.end())
							{
								send(*itr, send_reply(input[0], *itr, *this, 421, "").c_str(), send_reply(input[0], *itr, *this, 421, "").length(), MSG_DONTWAIT);
							}
							else
							{
								cmd_map[ft_toupper(input[0])](input_temp_2[0], user_itr->first, *this);
							}
							
							str_index = str_buff.find('\n');
							str_buff.erase(0, str_index + 1);
							ivc++;
						}
						_user_map[*itr].clear_buff();
					}

				
				}
				else if(retbuff == 0)
				{
					std::cout << "\nsocket n'" << *itr << " is closed on client side.\n";
					if(_user_map[*itr].get_quit() == false)
						QUIT("QUIT", *itr, *this);
					if (_user_map[*itr].get_registration() == 3)
						_registered_map.erase(_user_map[*itr].get_nick());
					_open_sock.erase(*itr);

					if (_open_sock.empty() == 0)
						break;
				}
				rm_empty_map(*this);
				//	std::cout << "after recv" << std::endl;
				//FD_CLR(*itr, &_sock_client);
			}
			
		}
		if(_shutdown == true)
			break;
	}
}

std::map<int, user>		&server::get_usermap(void)
{
	return (this->_user_map);
}

server::~server()
{
	//close(_connection);
	//close(_sockfd);
}

char *server::get_pswd()
{
	return this->_pswd;
}

std::string		server::get_servername() const
{
	return this->_servername;
}

std::string				server::get_hostname(void) const
{
	return this->_hostname;
}

std::string				server::get_version(void) const
{
	return this->_version;
}

std::string				server::get_date(void) const
{
	return this->_dateofbirth;
}


std::string				server::get_motd(void) const
{
	return this->_motd;
}

std::map<std::string, user>		&server::get_regi_map(void)
{
	return (this->_registered_map);
}

std::map<std::string, channel>		&server::get_chan_map(void)
{
	return this->_chan_map;
}

std::string						server::get_admin_pswd(void) const
{
	return this->_admin_pswd;
}

void server::fd_erase(int socket)
{
	FD_CLR(socket, &_sock_client);
	return ;
}

std::set<int>		&server::get_open_sock(void)
{
	return this->_open_sock;
}

void							server::set_shutdown(bool shu)
{
	this->_shutdown = shu;
}
