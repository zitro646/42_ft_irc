/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:58:20 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/06/16 19:56:12 by josuna-t         ###   ########.fr       */
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
	
	this->send_message(this->fds[i].fd,RPL_LISTSTART(this->clients[i].get_name(),this->clients[i].getnick()));
	for (iter = this->cha.begin(); iter != this->cha.end(); iter++)
	{
		if (iter->second.getmodes().find('s') == std::string::npos && iter->second.getmodes().find('p') == std::string::npos)
			this->send_message(this->fds[i].fd,RPL_LIST(this->clients[i].get_name(),this->clients[i].getnick(),iter->first,std::to_string(iter->second.getclientlist().size()),iter->second.gettopic()));
	}
	this->send_message(this->fds[i].fd,RPL_LISTEND(this->clients[i].get_name(),this->clients[i].getnick()));
	return;
}