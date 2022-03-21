// channel class

#include <vector>
#include <string>
#include "../USER/user.hpp"

class channel
{
	private:
		string		_name;
		vector<user>		_user_list;
		vector<user>		_op_list;
	
	public:
		user();
		~user();

		// accessors et getters
}