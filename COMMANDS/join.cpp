#include "commands.hpp"

void		join_single(int socket_client, server &my_serv, std::string chan, std::string key)
{
	std::cout << "COUCOU JE PASSE PAR ICI" << std::endl;
	chan.erase(std::remove(chan.begin(), chan.end(), '\n'), chan.end());
	chan.erase(std::remove(chan.begin(), chan.end(), '\r'), chan.end());
	if(my_serv.get_chan_map()[chan].get_op_list(my_serv.get_usermap()).empty() != 0 && my_serv.get_chan_map()[chan].get_user_list(my_serv.get_usermap()).empty() != 0)
	{
		std::cout << "COUCOU JE PASSE PAR OP" << std::endl;
		if(my_serv.get_chan_map().size() == MAXCHAN)
		{
			std::cout << "YAUNEERREUR" << std::endl;
			std::string tmp = send_reply("JOIN", socket_client, my_serv, ERR_TOOMANYCHANNELS, chan);
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			return;
		}
		my_serv.get_chan_map()[chan].add_op_user(my_serv.get_usermap()[socket_client]);
		my_serv.get_chan_map()[chan].set_name(chan);
		my_serv.get_chan_map()[chan].set_key(key);
		std::string tmp = ":" + my_serv.get_usermap()[socket_client].get_id() + " JOIN " + chan + "\r\n"; 
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		if(my_serv.get_chan_map()[chan].get_topic().empty() != 0)
			tmp = send_reply("JOIN", socket_client, my_serv, RPL_NOTOPIC, chan);
		else
			tmp = send_reply("JOIN", socket_client, my_serv, RPL_TOPIC, chan);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("JOIN", socket_client, my_serv, RPL_NAMREPLY, chan);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("JOIN", socket_client, my_serv, RPL_ENDOFNAMES, chan); // maybe 
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	
	}
	else
	{
		std::cout << "COUCOU JE PASSE PAR LA PLEBEs" << std::endl;
		if(find(my_serv.get_chan_map()[chan].get_ban_list().begin(), my_serv.get_chan_map()[chan].get_ban_list().end(), (my_serv.get_usermap()[socket_client]).get_id()) == my_serv.get_chan_map()[chan].get_ban_list().end() || my_serv.get_chan_map()[chan].get_ban_list().empty() == 1)
		{
			if(find_user(my_serv.get_chan_map()[chan].get_user_list(my_serv.get_usermap()), my_serv.get_usermap()[socket_client]) != true)
				my_serv.get_chan_map()[chan].add_user(my_serv.get_usermap()[socket_client]);
		}
		else
		{
			std::string tmp = send_reply("JOIN", socket_client, my_serv, ERR_BANNEDFROMCHAN, chan);
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			return;
		}
		if(my_serv.get_chan_map()[chan].get_chan_mode().find('I') != std::string::npos && find(my_serv.get_chan_map()[chan].get_invite_list(my_serv.get_usermap()).begin(), my_serv.get_chan_map()[chan].get_invite_list(my_serv.get_usermap()).end(), my_serv.get_usermap()[socket_client]) == my_serv.get_chan_map()[chan].get_invite_list(my_serv.get_usermap()).end())
		{
			std::string tmp = send_reply("JOIN", socket_client, my_serv, ERR_INVITEONLYCHAN, chan);
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			return;
		}
		if(my_serv.get_chan_map()[chan].get_user_list(my_serv.get_usermap()).size() == MAXCHANUSER)
		{
			std::string tmp = send_reply("JOIN", socket_client, my_serv, ERR_CHANNELISFULL, chan);
			send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
			return;
		}
		std::vector<user> list = my_serv.get_chan_map()[chan].get_user_list(my_serv.get_usermap());
		std::string tmp;
		std::string id = my_serv.get_usermap()[socket_client].get_id().substr();
		tmp = ":" + id + " JOIN " + chan + "\r\n";
		for(std::vector<user>::iterator itr = list.begin(); itr != list.end(); ++itr)
		{
			int socket = itr->get_socket();
			std::cout << "COUCOU JE PASSE PAR msgus socket:" <<  socket << std::endl;
			std::cout << chan << std::endl;
			send(socket, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		}
		std::vector<user> list_op = my_serv.get_chan_map()[chan].get_op_list(my_serv.get_usermap());
		for(std::vector<user>::iterator itr = list_op.begin(); itr != list_op.end(); ++itr)
		{
			int socket = itr->get_socket();
			std::cout << "COUCOU JE PASSE PAR msgOP" << socket << std::endl;
			send(socket, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		}
		if(my_serv.get_chan_map()[chan].get_topic().empty() != 0)
			tmp = send_reply("JOIN", socket_client, my_serv, RPL_NOTOPIC, chan);
		else
			tmp = send_reply("JOIN", socket_client, my_serv, RPL_TOPIC, chan);
		std::cout << "TEST" << "'" << chan << "'" << std::endl;
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("JOIN", socket_client, my_serv, RPL_NAMREPLY, chan);
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
		tmp = send_reply("JOIN", socket_client, my_serv, RPL_ENDOFNAMES, chan); // maybe 
		send(socket_client, tmp.c_str(), tmp.length(), MSG_DONTWAIT);
	}
}

void		JOIN(std::string input, int socket_client, server & my_serv) 
{ 
    std::cout << "JOIN called" << std::endl;
    
	std::vector<std::string>	splitted = ft_split(input, ' ');
	std::vector<std::string>	chan;
	std::vector<std::string>	key;
	std::string					tmp;
	if (splitted[1].find(',') > 0)
	{
		chan = ft_split(splitted[1], ',');
	}
	else
	{
		if(splitted[1].find_first_of('#') == 0)
			chan.push_back(splitted[1]);
		else 
			return;
	}
	if (splitted.size() > 2)
	{
		if(splitted[2].find(',') > 0)
			key = ft_split(splitted[2], ',');
		else
			key.push_back(splitted[2]);
	}

	if(chan.size() > 1)
	{
		if(key.empty() == 1)
		{
			int i = 0;
			while(i != (int)chan.size())
			{
				join_single(socket_client, my_serv, chan[i], "");
				i++;
			}
		}
		else
		{
			int i = 0;
			int y = 0;
			while (i != (int)chan.size())
			{
				if(chan[i].find_first_of('#') != 0)
					return;
				if(key[y].compare(my_serv.get_chan_map()[chan[i]].get_key()) == 0 || my_serv.get_chan_map()[chan[i]].get_key().empty() == 1)
					join_single(socket_client, my_serv, chan[i], key[y]);
				else
				{
					tmp = send_reply("JOIN", socket_client, my_serv, ERR_BADCHANNELKEY, chan[i]);
					send(socket_client, tmp.c_str(), tmp.length(), MSG_CONFIRM);
				}
				if(y < (int)key.size())
					y++;
				i++;
			}
			
		}
	}
	else if(chan[0].compare("0") == 0)
	{
		for(std::map<std::string, channel>::iterator itr = my_serv.get_chan_map().begin(); itr != my_serv.get_chan_map().end(); itr++)
		{
			itr->second.remove_op_user(my_serv.get_usermap()[socket_client]);
			itr->second.remove_user(my_serv.get_usermap()[socket_client]);
		}
	}
	else
	{			
		if(chan[0].find_first_of('#') != 0)
			return;
		join_single(socket_client, my_serv, chan[0], "");
	}
    std::cout << std::endl << std::endl;
};