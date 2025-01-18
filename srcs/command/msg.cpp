/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:56:51 by mortiz-d          #+#    #+#             */
/*   Updated: 2025/01/18 19:59:49 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

void server::MSG	(int i , std::string str , data_running *run)
{
	(void)run;	
	//:prueba4242!~josuna-t@195.55.210.173 PRIVMSG #canalprueba42 :hola
	
	std::string channel;
	
	channel = str.substr(0, str.find(" ", 0));
	// std::cout << channel << " - " << str << "\n";
	if (this->clients[i].check_Client_full_data())
	{
		if (channel[0] == '#' && this->cha.find(channel) != this->cha.end())
		{
			if (((this->cha[channel].getmodes().find('m') != std::string::npos) &&\
                this->cha[channel].find_client_by_hostname(this->clients[i].getusername_host())->second.op == 0) || ((this->cha[channel].getmodes().find('n') != std::string::npos && this->cha[channel].is_hostname_client_in_list(this->clients[i].getusername_host()) == false)))
            {
                this->send_message(this->fds[i].fd, ERR_CANNOTSENDTOCHAN( this->clients[i].get_name() , channel));
            }
			else
			{
				std::cout << this->cha[channel].getmodes() << std::endl;
				this->msg_to_channel(this->fds[i].fd, ":" + this->clients[i].get_name() + " PRIVMSG " + str + "\n", channel);
			}
		}
		else
			this->msg_to_user(":" + this->clients[i].get_name() + " PRIVMSG " + str + "\n", channel);
	}
	else
		this->send_message(this->fds[i].fd,"Server : Set up ur NICK/USER first before sending an MSG\n");
	return;
}
