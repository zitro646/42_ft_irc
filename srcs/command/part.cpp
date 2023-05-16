/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:57:51 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/16 20:12:52 by mortiz-d         ###   ########.fr       */
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

	if (str == "")
	{
		this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->get_host()));
		return;
	}
	line = split_in_vector(str,' ');
	channel = line[0].substr(0, line[0].size());
	if (this->channels.find(channel) != this->channels.end() && (this->channels[channel].find(clients[i].getusername_host()) != this->channels[channel].end()))
	{
		this->clients[i].remove_channel(channel);
        for (iter = this->channels[channel].begin(); iter != this->channels[channel].end(); iter++)
        {
            this->send_message(iter->second, ":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " PART " + channel + "\n");
        }
		this->channels[channel].erase(this->channels[channel].find(clients[i].getusername_host()));
		std::cout << "Server : User "<< clients[i].getnick()<< " deleted from channel "<< channel << std::endl;
	}
	else
		this->send_message(this->fds[i].fd,ERR_NOSUCHCHANNEL(this->get_host(),channel));
	// std::cout << "Cliente nuevo status" << std::endl << this->clients[i] << YELLOW;
	std::cout << YELLOW;
	this->look_channels();
	std::cout << RESET;
}