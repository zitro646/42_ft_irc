/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:55:05 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/06/07 17:43:24 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

//BASED ON  -> USER <username> <hostname> <servername> :<realname> (RFC 1459)
void server::USERNAME	(int client_id , std::string str , data_running *run)
{
	std::vector <std::string>	line;
	std::vector <std::string>	line2;

	line = split_in_vector(str,' ');
	line2 = split_in_vector(str,':');
	if (line.size() >= 4 && line2.size() == 2)
	{
		line[1].erase(line[1].find_last_not_of(" \n\r\t")+1);
		line2[1].erase(line2[1].find_last_not_of("\n\r\t")+1);
		//Intentamos crear el user name
		if (!this->find_client_by_hostname_username(line[0],run))
		{
			this->clients[client_id].setrealname_host(line2[1]);
			this->clients[client_id].setusername_host(line[0]);
			this->clients[client_id].setuserip(line[2]);
			this->send_message(this->fds[client_id].fd,RPL_WELCOME(this->clients[client_id].get_name() , this->clients[client_id].getnick()));
            this->send_message(this->fds[client_id].fd,RPL_YOURHOST(this->clients[client_id].get_name() , this->clients[client_id].getusername_host()));
            this->send_message(this->fds[client_id].fd,RPL_CREATED(this->clients[client_id].get_name()));
            this->send_message(this->fds[client_id].fd,RPL_MYINFO(this->clients[client_id].get_name()));
		}
		else
			this->send_message(this->fds[client_id].fd,ERR_ALREADYREGISTERED(this->clients[client_id].get_name()));
	}
	else
		this->send_message(this->fds[client_id].fd,ERR_NEEDMOREPARAMS(this->clients[client_id].get_name()));
  
  	return;
}