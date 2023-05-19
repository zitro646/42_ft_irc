/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:57:51 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/19 16:38:11 by miguelangel      ###   ########.fr       */
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

	if (str == "")
	{
		this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->get_host()));
		return;
	}
	line = split_in_vector(str,' ');
	channel = line[0].substr(0, line[0].size());
	if (this->cha.find(channel) != this->cha.end())
		if (this->cha[channel].is_client_in_list(this->clients[i].getusername_host()))
			resultado = 1;
	if (resultado)
	{
		this->clients[i].remove_channel(channel);
		
		std::map<std::string,data_client> cn = this->cha[channel].getclientlist();
		for (std::map<std::string,data_client>::iterator iter = cn.begin(); iter != cn.end(); iter++)
            this->send_message(iter->second.fd, ":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " PART " + channel + "\n");
		
		this->cha[channel].remove_client(clients[i].getusername_host());
		if (this->cha[channel].getclientlist().size() == 0)
			this->cha.erase(channel);
		// std::cout << "Server : User "<< clients[i].getnick()<< " deleted from channel "<< channel << std::endl;
	}
	else
	{
		this->send_message(this->fds[i].fd,ERR_NOSUCHCHANNEL(this->get_host(),channel));
	}
	// if (this->channels.find(channel) != this->channels.end() && (this->channels[channel].find(clients[i].getusername_host()) != this->channels[channel].end()))
	// {
	// 	this->clients[i].remove_channel(channel);
    //     for (iter = this->channels[channel].begin(); iter != this->channels[channel].end(); iter++)
    //     {
    //         this->send_message(iter->second, ":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " PART " + channel + "\n");
    //     }
	// 	this->channels[channel].erase(this->channels[channel].find(clients[i].getusername_host()));
	// 	std::cout << "Server : User "<< clients[i].getnick()<< " deleted from channel "<< channel << std::endl;
	// }
	// else
	// 	this->send_message(this->fds[i].fd,ERR_NOSUCHCHANNEL(this->get_host(),channel));
	
	// std::cout << "Cliente nuevo status" << std::endl << this->clients[i] << YELLOW;
	std::cout << YELLOW;
	this->look_cha();
	std::cout << RESET;
}