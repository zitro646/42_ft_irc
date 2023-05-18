/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:58:20 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/18 19:54:05 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

void 	server::LIST	(int i , std::string str , data_running *run)
{
	(void)run;
	(void)str;
	std::vector <std::string>	line;
	std::map<std::string,channel >::iterator iter;
	// std::map<std::string,channel> cn = this->cha.begin();
	
	this->send_message(this->fds[i].fd,RPL_LISTSTART(this->get_host(),this->clients[i].getusername_host()));
	for (iter = this->cha.begin(); iter != this->cha.end(); iter++)
	{
		this->send_message(this->fds[i].fd,RPL_LIST(this->get_host(),this->clients[i].getusername_host(),iter->first,std::to_string(iter->second.getclientlist().size()),iter->second.gettopic()));
		// std::cout << + (int)iter->second.size();
		// std::cout << i << " " << iter->first << std::endl;
	}
	this->send_message(this->fds[i].fd,RPL_LISTEND(this->get_host(),this->clients[i].getusername_host()));
	return;
}