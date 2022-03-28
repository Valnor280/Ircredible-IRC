// channel class

#include "CHANNEL/channel.hpp"

channel::channel() : _name("")
{
}

channel::~channel()
{

}

std::string			channel::get_name() const
{
	return _name;
}

std::string			channel::get_topic() const
{
	return _topic;
}

std::string			channel::get_key() const
{
	return _key;
}
std::vector<user>	channel::get_user_list(std::map<int, user> umap)
{
	for (std::vector<user>::iterator itr = _user_list.begin(); itr != _user_list.end(); itr++)
	{
		if(umap[itr->get_socket()] != *itr)
			*itr = umap[itr->get_socket()];
	} 
	return this->_user_list;
}

std::vector<user>	channel::get_invite_list() const
{
	return this->_invite_list;
}

std::vector<user>	channel::get_op_list(std::map<int, user> umap)
{
	for (std::vector<user>::iterator itr = _op_list.begin(); itr != _op_list.end(); itr++)
	{
		if(umap[itr->get_socket()] != *itr)
			*itr = umap[itr->get_socket()];
	} 
	return this->_op_list;
}

std::vector<user>	channel::get_ban_list() const
{
	return this->_ban_list;
}

std::string			channel::get_chan_mode() const
{
	return this->_chan_mode;
}

void				channel::set_name( std::string new_name )
{
	this->_name = new_name;
}

void				channel::set_topic( std::string new_topic )
{
	this->_topic = new_topic;
}

void				channel::set_key( std::string new_key )
{
	this->_key = new_key;
}

void				channel::add_user( const user member )
{
	this->_user_list.push_back(member);
}

void				channel::add_invite( const user member )
{
	this->_invite_list.push_back(member);
}

void				channel::remove_user( const user member )
{
	this->_user_list.erase(find(_user_list.begin(), _user_list.end(), member));
}

void				channel::add_op_user( const user member )
{
	this->_op_list.push_back(member);
}

void				channel::add_ban( const user member )
{
	this->_ban_list.push_back(member);
}

void				channel::remove_ban( const user member )
{
	this->_ban_list.erase(find(_ban_list.begin(), _ban_list.end(), member));
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