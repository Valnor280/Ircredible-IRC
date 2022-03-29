#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>

class user
{
	private:
		std::string		_nick; // nickname used for identification by server
		std::string		_username; // username used when displaying messages
		std::string		_real_name; // full name of the client using the server
		std::string		_mode;	// gives level of commands or privileges accessible to the user
								// a : user is away and any private message must be answered by the away message
								// B : user is a bot
								// d : disables PRIVMSG for the user (can only receive messages through channels)
								// D : disables messages from everyone except Operators, servers and services
								// H : hides Operator status, users using /WHOIS will not see you are Operator                 [only if already 'o']
								// I : hides online time in /WHOIS                                                             [can be stopped by server config]
								// i : makes you invisible on /WHO and /NAMES commands to anyone outside the channel
								// o : Operator status!                                                                        [set by server or by /OPER]
								// O : local Operator, see 'o'
								// p : hides channels you are in from /WHOIS
								// q : Un-kickable (can only be kicked by certain services)                                    [only if already 'o']
								// r : indicates this is a "registered nick"                                                   [authentificated by a service]
								// R : only receives private messages from "registered nicks"
								// S : user is a service bot
								// T : prevents you from receiving CTCP's? (Client to Client protocols) on verra...
								// V : indicates you are using a /VHOST (virtual host) and you are hiding you IP adress        [set by the server /VHOST, /OPER, /*HOST]
								// W : Let's you see when people do a /WHOIS on you                                            [only if already 'o']
								// w : can listen to WALLOPS messages (/WALLOPS from Operators)
								// x : gives you a hidden/cloaked hostname
								// Z : only allows interaction with secure users (users with mode 'z')
								// z : indicates you are connected via SSL/TLS (secure connection)
		bool			_auth; // bool if the user go the right pswd 0 =yes 1 = no
		int				_registration; // int that gives us a value for where user currently is in terms of registration:
										// 0 : nothing yet or just PASS
										// 1 : NICK has been set
										// 2 : USER has been set
										// 3 : ALL is set, RPL_WELCOME has been sent and user has been added to registered map
		std::string		_away_msg; // the away msg used by the command away and its reply
	
		bool			_quit; // to know if a user already quitted
		std::string     _status;
		std::string		_hostname;
		std::string		_op_name;
		int				_socket;


		//STATS
		struct timeval	first_connect;//set dans accept connect
		unsigned long	oct_recv;
		unsigned long	oct_send;
		unsigned long	mess_recv;
		unsigned long	mess_send;


	public:
		user();
		~user();

		// GETTERS
		std::string		get_nick() const;
		std::string		get_username() const;
		std::string		get_real_name() const;
		std::string		get_mode() const;
		bool			get_auth() const;
		std::string		get_status() const;
		std::string		get_hostname() const;
		std::string		get_op_name() const;
		std::string		get_id() const; // Permet de construire une string tel que "[nickname]![username]@[hostname]"
		bool			get_quit() const;
		int				get_registration() const;
		std::string		get_away_msg() const;
		int				get_socket() const;
		long long int	get_connected_time() const;
		unsigned long	get_oct_recv() const;
		unsigned long	get_oct_send() const;
		unsigned long	get_mess_recv() const;
		unsigned long	get_mess_send() const;

		//SETTERS
		bool		set_nick( std::string new_nick );
		void		set_quit( int quit );
		bool		set_username( std::string new_username );
		bool		set_real_name( std::string new_real_name );
		void		set_mode( std::string new_access_level );
		void		set_auth(int i);
		void		set_status( std::string status );
		void		set_hostname( std::string new_hostname );
		void		set_op_name( std::string new_op_name );
		void		set_registration( int new_reg );
		void		set_away_msg(std::string msg);
		void		set_socket(int new_socket );
		void		set_first_connect(void);
		void		add_oct_recv(unsigned long nb);
		void		add_oct_send(unsigned long nb);
		void		add_mess_recv(unsigned long nb);
		void		add_mess_send(unsigned long nb);


		// UTILS
		void		print_user() const;
		
		
};

bool operator==(const user& lhs, const user& rhs);
bool operator!=(const user& lhs, const user& rhs);

#endif
