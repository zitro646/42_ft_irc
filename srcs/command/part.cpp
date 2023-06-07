/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:57:51 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/06/07 15:57:00 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

void 	server::PART	(int i , std::string str , data_running *run)
{
	(void)run;
	std::map<std::string,int>::iterator iter;
	std::vector <std::string>	line;
	std::string 				channel;
	int							resultado = 0;

	std::cout << YELLOW;
	this->look_cha();
	std::cout << RESET;

	if (str == "")
	{
		this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->clients[i].get_name()));
		return;
	}
	line = split_in_vector(str,' ');
	line = split_in_vector(line[0],',');
	
	for (int x = 0; x < (int)line.size(); x++)
	{
		channel = line[x];
		if (this->cha.find(channel) != this->cha.end())
			if (this->cha[channel].is_client_in_list(this->clients[i].getusername_host()))
				resultado = 1;
		if (resultado)
		{
			
			this->send_message(this->fds[i].fd,":" + this->clients[i].get_name() + " PART " + channel + "\n");
			this->msg_to_channel(this->fds[i].fd,":" + this->clients[i].get_name() + " PART " + channel + "\n",channel);
			
			
			this->clients[i].remove_channel(channel);
			this->cha[channel].remove_client(clients[i].getusername_host());
			if (this->cha[channel].getclientlist().size() == 0)
				this->cha.erase(channel);
		}
		else
		{
			this->send_message(this->fds[i].fd,ERR_NOSUCHCHANNEL(this->clients[i].get_name(),channel));
		}
	}
	std::cout << YELLOW;
	this->look_cha();
	std::cout << RESET;
}