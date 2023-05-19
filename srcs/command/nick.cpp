/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:54:55 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/19 17:31:31 by miguelangel      ###   ########.fr       */
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
			{
				this->clients[i].setnick(nick);
				//Modificamos el nick en los canales en los que este
				std::set<std::string>::iterator siter;
				std::set<std::string> cn = this->clients[i].getclientchannels();
				for (siter = cn.begin(); siter != cn.end(); siter++)
				{
					this->cha[*siter].remove_client(this->clients[i].getusername_host());
					if (this->clients[i].getusername_host() != "")
						this->cha[*siter].modify_nick(this->clients[i].getusername_host(),nick);
				}
			}	
		}
		else
			this->send_message(this->fds[i].fd,ERR_ERRONEUSNICKNAME(this->get_host())); //ERR_ERRONEUSNICKNAME
	}
	else
		this->send_message(this->fds[i].fd,ERR_NONICKNAMEGIVEN(this->get_host())); // ERR_NONICKNAMEGIVEN

	return;
}