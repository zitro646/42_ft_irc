/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:58:20 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/16 20:11:34 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

void 	server::LIST	(int i , std::string str , data_running *run)
{
	(void)run;
	(void)str;
	std::vector <std::string>	line;
	std::map<std::string,std::map<std::string,int> >::iterator iter;
	
	this->send_message(this->fds[i].fd,RPL_LISTSTART(this->get_host(),this->clients[i].getusername_host()));
	for (iter = this->channels.begin(); iter != this->channels.end(); iter++)
	{
		this->send_message(this->fds[i].fd,RPL_LIST(this->get_host(),this->clients[i].getusername_host(),iter->first,std::to_string(iter->second.size()),""));
		// std::cout << + (int)iter->second.size();
		// std::cout << i << " " << iter->first << std::endl;
	}
	this->send_message(this->fds[i].fd,RPL_LISTEND(this->get_host(),this->clients[i].getusername_host()));
	return;
}