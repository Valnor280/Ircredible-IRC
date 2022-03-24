// channel class

#include "CHANNEL/channel.hpp"

channel::channel( const user creator, std::string name) : _name(name)
{
	_user_list.push_back(creator);
	_op_list.push_back(creator);
}

channel::~channel()
{

}

std::string			channel::get_name() const
{
	return _name;
}

std::vector<user>	channel::get_user_list() const
{
	return this->_user_list;
}

std::vector<user>	channel::get_op_list() const
{
	return this->_op_list;
}

std::string			channel::get_chan_mode() const
{
	return this->_chan_mode;
}

void				channel::set_name( std::string new_name )
{
	this->_name = new_name;
}

void				channel::add_user( const user member )
{
	this->_user_list.push_back(member);
}

void				channel::remove_user( const user member )
{
	this->_user_list.erase(find(_user_list.begin(), _user_list.end(), member));
}

void				channel::add_op_user( const user member )
{
	this->_op_list.push_back(member);
}

void				channel::remove_op_user( const user member )
{
	this->_op_list.erase(find(_op_list.begin(), _op_list.end(), member));
}

void				channel::clear_user_list()
{
	this->_user_list.clear();
}

void				channel::clear_op_list()
{
	this->_op_list.clear();
}

bool operator==(const channel& lhs, const channel& rhs)
{
	return lhs.get_name() == rhs.get_name();
}