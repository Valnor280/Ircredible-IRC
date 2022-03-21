// channel class

#include <vector>
#include <string>
#include "USER/user.hpp"

class channel
{
	private:
		string		_name;
		vector<user>		_user_list;
		vector<user>		_op_list;
	
	public:
		channel( const user creator );
		~channel();

		// GETTERS
		string				get_name() const;
		vector<user>		get_user_list() const;
		vector<user>		get_op_list() const;

		// SETTERS
		void				set_name( string new_name );
		void				add_user( const user member );
		void				remove_user( const user member );
		void				add_op_user( const user member );
		void				remove_op_user( const user member );
		void				clear_user_list();
		void				clear_op_list();
}