// user class

#include "USER/user.hpp"

user::user(): _nick(""), _username(""), _real_name(""), _mode(""), _auth(1), _registration(0), _quit(false), _op_name("")
{
	// nothing here
	this->oct_recv = 0;
	this->oct_send = 0;
	this->mess_recv = 0;
	this->mess_send = 0;

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

std::string			user::get_status() const
{
	return _status;
}


bool			user::get_auth() const
{
	return _auth;
}

std::string			user::get_hostname() const
{
	return _hostname;
}

std::string			user::get_op_name() const
{
	return _op_name;
}

std::string			user::get_id() const
{
	return this->get_nick() + "!" + this->get_username() + "@" + this->get_hostname();
}

int				user::get_registration() const
{
	return this->_registration;
}


std::string		user::get_away_msg() const
{
	return this->_away_msg;
}

std::string		user::get_buff()
{
	return this->_tmp_buff;
}

void	user::set_buff(std::string buff)
{
	_tmp_buff += buff;
}

void	user::erase_buff(int i, int y)
{
	_tmp_buff.erase(i, y);
}

void	user::clear_buff()
{
	_tmp_buff.clear();
}

int				user::get_socket() const
{
	return this->_socket;
}

long int	user::get_connected_time() const
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000000 + tv.tv_usec)) - ((this->first_connect.tv_sec * 1000000) + this->first_connect.tv_usec));
}

unsigned long	user::get_oct_recv() const
{
	return (this->oct_recv);
}
unsigned long	user::get_oct_send() const
{
	return (this->oct_send);
}
unsigned long	user::get_mess_recv() const
{
	return (this->mess_recv);
}
unsigned long	user::get_mess_send() const
{
	return (this->mess_send);
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

void		user::set_auth(int i)
{
	this->_auth = i;
}
void		user::set_status( std::string new_status )
{
	this->_status = new_status;
}

void		user::set_hostname( std::string new_hostname )
{
	this->_hostname = new_hostname;
}

void		user::set_op_name( std::string new_op_name )
{
	this->_op_name = new_op_name;
}

void		user::set_quit( int quit )
{
	this->_quit = quit;
}

bool			user::get_quit() const
{
	return this->_quit;
}

void		user::set_registration( int new_reg )
{
	if (new_reg >= 0 && new_reg <= 3)
		this->_registration = new_reg;
}

void		user::set_away_msg( std::string msg )
{
	this->_away_msg = msg;
}
void		user::set_socket( int new_socket )
{
	this->_socket = new_socket;
}
void		user::set_first_connect(void)
{
	gettimeofday(&(this->first_connect), NULL);
}

void	user::add_oct_recv(unsigned long nb)
{
	this->oct_recv += nb;
}
void	user::add_oct_send(unsigned long nb)
{
	this->oct_send += nb;
}
void	user::add_mess_recv(unsigned long nb)
{
	this->mess_recv += nb;
}
void	user::add_mess_send(unsigned long nb)
{
	this->mess_send += nb;
}

void		user::print_user() const
{
	std::cout << "|| USER IDENTIFICATION ||" << std::endl;
	std::cout << "Nick      : " << _nick << std::endl;
	std::cout << "Username  : " << _username << std::endl;
	std::cout << "Real name : " << _real_name << std::endl;
	std::cout << "Mode      : " << _mode << std::endl;
	std::cout << "Status    : " << _status << std::endl;
	std::cout << "Regis_num : " << _registration << std::endl;
	std::cout << "Hostname  : " << _hostname << std::endl;
	std::cout << "Socket	: " << _socket << std::endl;
}

bool operator==(const user& lhs, const user& rhs) 
{ 
	if(lhs.get_socket() == rhs.get_socket() && lhs.get_mode() == rhs.get_mode() && lhs.get_nick() == rhs.get_nick())
		return true;
	else
		return false;
}
bool operator!=(const user& lhs, const user& rhs) { return !(lhs == rhs);}
