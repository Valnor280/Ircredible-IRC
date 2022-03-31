#include "SERVER/server.hpp"

int main(int ac, char **av)
{



	if (ac != 3 || *(av[2]) == '\0') 
	{
        std::cout << "Please launch the program using: '" << av[0] << " <port> <password>'\n";
        return (0);
	}
	server *test;
	
	try
	{
		test = new server(av[1], av[2]);

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return(-1);
	}

	signal(SIGPIPE, SIG_IGN);
	test->loop();
	delete test;
	std::cout << "server closed" << std::endl;
}
