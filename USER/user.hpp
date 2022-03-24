#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <iostream>

class user
{
	private:
		std::string		_nick; // nickname used for identification by server
		std::string		_username; // username used when displaying messages
		std::string		_real_name; // full name of the client using the server
		std::string		_mode;	// gives level of commands or privileges accessible to the user
<<<<<<< HEAD
=======
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
>>>>>>> master
		bool			_auth; // bool if the user go the right pswd 0 =yes 1 = no
		int				_registration; // int that gives us a value for where user currently is in terms of registration:
										// 0 : nothing yet or just PASS
										// 1 : NICK has been set
										// 2 : USER has been set
<<<<<<< HEAD
	
		std::string     _status;
		std::string		_hostname;
=======
										// 3 : ALL is set, RPL_WELCOME has been sent and user has been added to registered map

		std::string     _status;
		std::string		_hostname;
		int				_socket;
>>>>>>> master


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
		std::string		get_id() const; // Permet de construire une string tel que "[nickname]![username]@[hostname]"
		int				get_registration() const;
<<<<<<< HEAD
=======
		int				get_socket() const;
>>>>>>> master

		//SETTERS
		bool		set_nick( std::string new_nick );
		bool		set_username( std::string new_username );
		bool		set_real_name( std::string new_real_name );
		void		set_mode( std::string new_access_level );
		void		set_auth(int i);
		void		set_status( std::string status );
		void		set_hostname( std::string new_hostname );
		void		set_registration( int new_reg );
<<<<<<< HEAD
=======
		void		set_socket(int new_socket );
>>>>>>> master

		// UTILS
		void		print_user() const;
};

#endif
