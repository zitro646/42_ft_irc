/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:54:55 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/16 17:09:43 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

void server::NICK	(int i , std::string nick , data_running *run) 
{	
	if ( nick != "")
	{
		std::cout << " Integridad del nick: " << nick << check_nickname_restrictions(nick) << std::endl;
		if (check_nickname_restrictions(nick))
		{
			if (this->find_client_nick(nick,run))
				this->send_message(this->fds[i].fd,ERR_NICKNAMEINUSE(this->get_host(),nick)); //ERR_NICKNAMEINUSE
			else
				this->clients[i].setnick(nick);
		}
		else
			this->send_message(this->fds[i].fd,ERR_ERRONEUSNICKNAME(this->get_host())); //ERR_ERRONEUSNICKNAME
	}
	else
		this->send_message(this->fds[i].fd,ERR_NONICKNAMEGIVEN(this->get_host())); // ERR_NONICKNAMEGIVEN

	return;
}