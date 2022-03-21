// user class

#include <string>
#include <iostream>

class user
{
	private:
		string		_nick; // nickname used for identification by server
		string		_username; // username used when displaying messages
		string		_real_name; // full name of the client using the server
		string		_mode;	// gives level of commands or privileges accessible to the user
	
	public:
		user();
		~user();

		// GETTERS
		string		get_nick() const;
		string		get_username() const;
		string		get_real_name() const;
		int			get_mode() const;

		//SETTERS
		bool		set_nick( string new_nick );
		bool		set_username( string new_username );
		bool		set_real_name( string new_real_name );
		void		set_mode( int new_access_level );

		// UTILS
		void		print_user() const;
};