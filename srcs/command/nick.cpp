/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:54:55 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/06/09 16:38:54 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

void server::NICK   (int i , std::string nick , data_running *run)
{
    if ( nick != "")
    {
        if (check_nickname_restrictions(nick))
        {
            if (this->find_client_by_hostname_nick(nick,run))
                this->send_message(this->fds[i].fd,ERR_NICKNAMEINUSE(this->clients[i].get_name(),nick)); //ERR_NICKNAMEINUSE
            else
            {
                //Modificamos el nick en los canales en los que este
                std::set<std::string> cn = this->clients[i].getclientchannels();
                for (std::set<std::string>::iterator siter = cn.begin(); siter != cn.end(); siter++)
                {
                    this->cha[*siter].modify_nick(this->clients[i].getusername_host(),nick);
                	this->msg_to_channel(this->fds[i].fd, ":" + this->clients[i].get_name() + "!~" + this->clients[i].getnick() + " NICK :" + nick  + "\n",*siter);
                }
				this->send_message(this->fds[i].fd, ":" + this->clients[i].get_name() + "!~" + this->clients[i].getnick() + " NICK :" + nick  + "\n");
                this->clients[i].setnick(nick);
            }
        }
        else
            this->send_message(this->fds[i].fd,ERR_ERRONEUSNICKNAME(this->clients[i].get_name())); //ERR_ERRONEUSNICKNAME
    }
    else
        this->send_message(this->fds[i].fd,ERR_NONICKNAMEGIVEN(this->clients[i].get_name())); // ERR_NONICKNAMEGIVEN

    return;
	
}