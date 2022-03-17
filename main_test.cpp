#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <iostream> 
#include <unistd.h>
#include <cerrno>
#include <string>
#include <netdb.h>
#include <arpa/inet.h>



// struct sockaddr_in6 
// {
//     sa_family_t     sin6_family;   /* AF_INET6 */
//     in_port_t       sin6_port;     /* port number */
//     uint32_t        sin6_flowinfo; /* IPv6 flow information */
//     struct in6_addr sin6_addr;     /* IPv6 address */
//     uint32_t        sin6_scope_id; /* Scope ID (new in 2.4) */ 
// };

// struct sockaddr_in 
// {
//    sa_family_t    sin_family; /* address family: AF_INET */
//    in_port_t      sin_port;   /* port in network byte order */
//    struct in_addr sin_addr;   /* internet address */
// };

// struct in_addr 
// {
//     uint32_t       s_addr; /* address in network byte order */ 
// };


int main(int ac, char **av)
{
		
	if (ac != 3 || *(av[2]) == '\0') 
	{
        std::cout << "Please launch the program using: '" << av[0] << " <port> <password>'\n";
        return (0);
	}
	//int port = atoi(av[1]);
	int sockfd;

	addrinfo hints, *res, *p;    // we need 2 pointers, res to hold and p to iterate over
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	int gaddres = getaddrinfo(NULL, av[1], &hints, &res);
	if(gaddres != 0)
	{
		std::cout << gai_strerror(gaddres) << "\n";
		return -2;
	}

	unsigned int numOfAddr = 0;
    char ipStr[INET6_ADDRSTRLEN];

	for(p = res; p != NULL; p = p->ai_next)
	{
		void *addr;
		std::string ipVer;

		if(p->ai_family == AF_INET)
		{
			ipVer = "IPv4";
			sockaddr_in *ipv4 = reinterpret_cast<sockaddr_in *>(p->ai_addr);
			addr = &(ipv4->sin_addr);
			numOfAddr++;
		}
		else
		{
			ipVer = "IPv6";
			sockaddr_in6 *ipv6 = reinterpret_cast<sockaddr_in6 *>(p->ai_addr);
			addr = &(ipv6->sin6_addr);
			numOfAddr++;
		}
		inet_ntop(p->ai_family, addr, ipStr, sizeof(ipStr));
        std::cout << "(" << numOfAddr << ") " << ipVer << " : " << ipStr << std::endl;
	}

	if (!numOfAddr) {
        std::cerr << "Found no host address to use\n";
        return -3;
    }

	p = res;
	sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (sockfd == -1)
	{
		std::cout << "Failed to create socket." << std::endl;
		freeaddrinfo(res);
		exit(EXIT_FAILURE);
	}
	/*sockaddr_in sockaddr;
	sockaddr.sin_family = AF_UNSPEC;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(atoi(av[1]));*/

	if(bind(sockfd, p->ai_addr, p->ai_addrlen)< 0)
	{
		std::cout << "Failed to bind on port." << errno << std::endl;
		close(sockfd);
        freeaddrinfo(res);
		exit(EXIT_FAILURE);
	}

	if(listen(sockfd, 10) < 0)
	{
		std::cout << "Failed to listen on socket." << std::endl;
   	 	exit(EXIT_FAILURE);
	}

	sockaddr_storage client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
	std::string response = "Welcome to this IRC_server prototype please don't mind the mess\n";
	
	while (1) {

        // accept call will give us a new socket descriptor
        int newFD
          = accept(sockfd, (sockaddr *) &client_addr, &client_addr_size);
        if (newFD == -1) {
            std::cerr << "Error while Accepting on socket\n";
            continue;
        }

        // send call sends the data you specify as second param and it's length as 3rd param, also returns how many bytes were actually sent
        send(newFD, response.data(), response.length(), 0);
        close(newFD);
    }
	close(sockfd);
	freeaddrinfo(res);
}