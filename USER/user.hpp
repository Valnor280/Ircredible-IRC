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
		std::string     _status;


	public:
		user();
		~user();

		// GETTERS
		std::string		get_nick() const;
		std::string		get_username() const;
		std::string		get_real_name() const;
		std::string		get_mode() const;
		std::string		get_status() const;

		//SETTERS
		bool		set_nick( std::string new_nick );
		bool		set_username( std::string new_username );
		bool		set_real_name( std::string new_real_name );
		void		set_mode( std::string new_access_level );
		void		set_status( std::string status );

		// UTILS
		void		print_user() const;
};

#endif
