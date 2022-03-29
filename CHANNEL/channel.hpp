// channel class
#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "USER/user.hpp"
class channel
{
	private:
		std::string				_name;
		std::vector<user>		_user_list;
		std::vector<user>		_op_list;
		std::vector<user>		_ban_list;
		std::vector<user>		_invite_list;
		std::vector<user>		_mute_list;
		std::string				_chan_mode;
		std::string				_topic;
		std::string				_key;
		int						_user_limit;
	
	public:
		channel();
		~channel();

		// GETTERS
		std::string				get_name() const;
		std::string				get_topic() const;
		std::string				get_key() const;
		std::vector<user>		get_user_list(std::map<int, user> umap);
		std::vector<user>		get_op_list(std::map<int, user> umap);
		std::vector<user>		get_ban_list(std::map<int, user> umap);
		std::vector<user>		get_invite_list(std::map<int, user> umap);
		std::vector<user>		get_mute_list(std::map<int, user> umap);
		std::string				get_chan_mode() const;
		int						get_user_limit() const;

		// SETTERS
		void				set_name( std::string new_name );
		void				set_topic( std::string new_topic );
		void				set_key( std::string new_key );
		void				set_chan_mode( std::string new_modes );
		void				set_user_limit( int new_limit );
		void				add_user( const user member );
		void				add_ban( const user member );
		void				add_invite( const user member );
		void				add_mute( const user member );
		void				remove_user( const user member );
		void				remove_ban( const user member );
		void				remove_mute( const user member );
		void				remove_invite( const user member );
		void				add_op_user( const user member );
		void				remove_op_user( const user member );
		void				clear_user_list();
		void				clear_op_list();
		void				clear_mute_list();
};

bool operator==(const channel& lhs, const channel& rhs);
#endif