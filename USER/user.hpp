// user class

#include <string>
#include <iostream>

class user
{
	private:
		std::string		_nick; // nickname used for identification by server
		std::string		_username; // username used when displaying messages
		std::string		_real_name; // full name of the client using the server
		std::string		_mode;	// gives level of commands or privileges accessible to the user
		bool			_auth; // bool if the user go the right pswd 0 =yes 1 = no
	
	public:
		user();
		~user();

		// GETTERS
		std::string		get_nick() const;
		std::string		get_username() const;
		std::string		get_real_name() const;
		std::string		get_mode() const;
		bool			get_auth() const;

		//SETTERS
		bool		set_nick( std::string new_nick );
		bool		set_username( std::string new_username );
		bool		set_real_name( std::string new_real_name );
		void		set_mode( std::string new_access_level );
		void		set_auth(int i);

		// UTILS
		void		print_user() const;
};