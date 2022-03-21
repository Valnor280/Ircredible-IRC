// user class

#include "USER/user.hpp"

user::user(): _nick(""), _username(""), _real_name(""), _mode("")
{
	// nothing here
}

user::~user()
{
	// nothing here
}

std::string			user::get_nick() const
{
	return _nick;
}

std::string			user::get_username() const
{
	return _username;
}

std::string			user::get_real_name() const
{
	return _real_name;
}

std::string			user::get_mode() const
{
	return _mode;
}

bool		user::set_nick( std::string new_nick )
{
	// add function to verify validity
	this->_nick = new_nick;
	return true;
}

bool		user::set_username( std::string new_username )
{
	// add function to verify validity
	this->_username = new_username;
	return true;
}
bool		user::set_real_name( std::string new_real_name )
{
	// add function to verify validity
	this->_real_name = new_real_name;
	return true;
}

void		user::set_mode( std::string new_mode )
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

