// channel class

#include "CHANNEL/channel.hpp"

channel::channel( const user creator)
{
	_op_list.push_back(creator);
}

channel::~channel()
{
	// nothing here
}

string			channel::get_name() const
{
	return _name;
}

vector<user>	get_user_list() const
{
	return _user_list;
}

vector<user>	get_op_list() const
{
	return _op_list;
}

void				channel::set_name( string new_name )
{
	this->_name = new_name;
}

void				channel::add_user( const user member )
{
	this->_user_list.push_back(member);
}

void				channel::remove_user( const user member )
{
	this->_user_list.erase(_user_list.find(member));
}

void				channel::add_op_user( const user member )
{
	this->_op_list.push_back(member);
}

void				channel::remove_op_user( const user member )
{
	this->_op_list.erase(_op_list.find(member));
}

void				channel::clear_user_list()
{
	this->_user_list.clear();
}

void				channel::clear_op_list()
{
	this->_op_list.clear();
}