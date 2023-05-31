/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:56:51 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/31 04:29:31 by miguelangel      ###   ########.fr       */
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
	std::cout << channel << " - " << str << "\n";
	if (this->clients[i].check_Client_full_data())
	{
		std::cout << "Cliente con datos\n";
		if (channel[0] == '#' && this->cha.find(channel) != this->cha.end())
		{
			std::cout << "Busca canal\n";
			this->msg_to_channel(this->fds[i].fd, ":" + this->clients[i].get_name() + " PRIVMSG " + str + "\n", channel);
		}
		else
			this->msg_to_user(":" + this->clients[i].get_name() + " PRIVMSG " + str + "\n", channel);
	}
	else
		this->send_message(this->fds[i].fd,"Server : Set up ur NICK/USER first before sending an MSG\n");
  return;
}
