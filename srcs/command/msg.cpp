/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:56:51 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/16 20:08:07 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

void server::MSG	(int i , std::string str , data_running *run)
{

	(void)run;
	// std::string receptor = str.substr(0,str.find(":",0) - 1);
	// str = &str[str.find(":",0) + 1];
	// int client_id = this->get_client_id_by_nick(receptor, run);
	
	// this->send_message(this->fds[client_id].fd,str);
	
	
	//:prueba4242!~josuna-t@195.55.210.173 PRIVMSG #canalprueba42 :hola
	
	std::string channel;
	
	channel = str.substr(0, str.find(" ", 0));
	std::cout << channel << " - " << str << "\n";
	if (this->check_client_NICK_USER(i))
	{
		std::cout << "Cliente con datos\n";
		if (channel[0] == '#')
		{
			std::cout << "Busca canal\n";
			this->msg_to_all(this->fds[i].fd, ":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " PRIVMSG " + str + "\n", channel);
		}
		else
			this->msg_to_user(":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " PRIVMSG " + str + "\n", channel);
	}
	else
		this->send_message(this->fds[i].fd,"Server : Set up ur NICK/USER first before sending an MSG\n");
  return;
}