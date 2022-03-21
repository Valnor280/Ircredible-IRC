// user class

#include "./user.cpp"

user::user(): _nick(""), _username(""), _real_name(""), _user_mode("")
{
	// nothing here
}

user::~user()
{
	// nothing here
}

string			user::get_nick() const
{
	return _nick;
}

string			user::get_username() const
{
	return _username;
}

string			user::get_real_name() const
{
	return _real_name;
}

int				user::get_mode() const
{
	return _user_mode;
}

bool		user::set_nick( string new_nick )
{
	// add function to verify validity
	this->_nick = new_nick;
	return true;
}

bool		user::set_username( string new_username )
{
	// add function to verify validity
	this->_username = new_username;
	return true;
}
bool		user::set_real_name( string new_real_name )
{
	// add function to verify validity
	this->_real_name = new_real_name;
	return true;
}

void		user::set_mode( string new_mode )
{
	this->_mode = new_mode;
}

void		user::print_user() const
{
	std::cout << "|| USER IDENTIFICATION ||" << std::endl;
	std::cout << "Nick      : " << _nick << std::endl;
	std::cout << "Username  : " << _username << std::endl;
	std::cout << "Real name : " << _real_name << std::endl;
	std::cout << "Mode      : " << _mode << std::endl;
}

