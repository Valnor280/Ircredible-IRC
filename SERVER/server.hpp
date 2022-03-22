#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <iostream> 
#include <unistd.h>
#include <cerrno>
#include <string>
#include <netdb.h>
#include <arpa/inet.h>
#include <exception>
#include <set>
#include <map>
#include <fcntl.h>
#include "../USER/user.hpp"
#include <signal.h>

#define PASS_CMD "PASS"
#define ERR_NEEDMOREPARAMS(NICK, CMD) ':' + NICK + " " + CMD + " :Not enough parameters\r\n"
# define ERR_ALREADYREGISTRED(NICK) ':' + NICK + " :You may not reregister\r\n"
# define ERR_PASSWDMISMATCH ':' + " Password incorrect\r\n"
class server
{
	public:
		server(char *port_number, char * pswd); // constructor should start evrything until listening
		~server();
	
		void loop();

		void user_read(int &sock_ready, int new_sock);
		int accept_connect(int numsock);

				//// LISTE DE COMMANDES SERVER-SIDE////
		void		ADMIN(std::string input);
		void		NICK(std::string input);
		void		PASS(std::string input);
		void		USER(std::string input);
		void		DIE(std::string input);
		void		HELP(std::string input);
		void		INFO(std::string input);
		void		ISON(std::string input);
		void		KILL(std::string input);
		void		LIST(std::string input);
		void		LUSERS(std::string input); // a voir
		void		MODE(std::string input);
		void		MOTD(std::string input);
		void		NAMES(std::string input); // l'option X est chelou
		void		PART(std::string input);
		void		PING(std::string input);
		void		PONG(std::string input);
		void		REHASH(std::string input); // a voir
		void		STATS(std::string input);
		void		SUMMON(std::string input);
		void		TIME(std::string input);
		void		USERHOST(std::string input);
		void		USERS(std::string input); // a voir
		void		VERSION(std::string input); // a voir
		void		WALLOPS(std::string input);
		void		WHO(std::string input);
		void		WHOIS(std::string input);
		void		WHOWAS(std::string input);

		// LISTE DE COMMANDES CHANNEL SIDE
		void		INVITE(std::string input);
		void		JOIN(std::string input);
		void		KICK(std::string input);
		void		KNOCK(std::string input); // a voir
		void		TOPIC(std::string input);

		// LISTE DE COMMANDES USER SIDE
		void		AWAY(std::string input);
		void		NOTICE(std::string input);
		void		OPER(std::string input);
		void		PRIVMSG(std::string input);
		void		QUIT(std::string input);
		void		SETNAME(std::string input);
		void		USERIP(std::string input);

	private:
	    struct ConstructorException : public std::exception
        {
			using std::exception::what;
            virtual const char * what() 
            {
                return "Constructor error\n";
            }
        };
		int _sockfd;
		char * _pswd;
		std::set<int> _open_sock;
		//sockaddr_in _sockaddr;
		int _connection;
		std::string _welcome_msg;
		std::string _hostname;
		char _buffer[512 + 1];
		fd_set _sock_client;
		fd_set _sock_ready;

		//MAP USER
		std::map<int, user> user_map;

		// MAP DES COMMANDES
		//std::map<std::string, >

};