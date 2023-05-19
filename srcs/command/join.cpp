/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:57:25 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/19 17:33:43 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

void server::JOIN	(int i , std::string str , data_running *run)
{
	(void)run;
	std::vector <std::string>	line;
	std::string 				channel;
	int							result;
	(void)result;
	if (str == "")
	{
		this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->get_host()));
		return;
	}
	line = split_in_vector(str,' ');
	channel = line[0].substr(0, line[0].size());
	if (this->cha.find(channel) == this->cha.end() || !(this->cha[channel].is_client_in_list(this->clients[i].getusername_host())))
	{
		std::cout << "Resultados "<< (this->cha.find(channel) == this->cha.end()) << !(this->cha[channel].is_client_in_list(this->clients[i].getusername_host())) << std::endl;
		if (this->cha[channel].getclientlist().size() == 0)
			this->cha[channel].add_client(this->clients[i].getusername_host(),this->fds[i].fd,this->clients[i].getnick(),true);
		else
			this->cha[channel].add_client(this->clients[i].getusername_host(),this->fds[i].fd,this->clients[i].getnick(),false);
		this->clients[i].add_channel(channel);
		//Esta parte hace el reply al cliente y a los demás
		std::string returnlist = ":" + this->get_host() + " 353 " + clients[i].getusername_host() + " = " + channel + " :"; //RPL_
		
		std::map<std::string,data_client> cn = this->cha[channel].getclientlist();
		// std::cout << "cliente que deberia existir " << cn.begin()->first << " con fd "<< cn.begin()->second << std::endl;
		for (std::map<std::string,data_client>::iterator iter = cn.begin(); iter != cn.end(); iter++)
		{
			this->send_message(iter->second.fd, ":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " JOIN " + channel + "\n");
			// std::cout << "Mira el cliente " << iter->second << " con fd "<< iter->first << std::endl;
			returnlist += iter->second.nick + " ";
		} 
		returnlist += "\n";
		this->send_message(this->fds[i].fd, returnlist);
		this->send_message(this->fds[i].fd, ":" + this->get_host() + " 366 " + clients[i].getusername_host() + " " + channel + " :End of /NAMES list.\n"); //RPL_
	
 	}
	else
	{
		std::cout << "Resultados "<< (this->cha.find(channel) == this->cha.end()) << !(this->cha[channel].is_client_in_list(this->clients[i].getusername_host())) << std::endl;
		this->send_message(this->fds[i].fd,ERR_USERONCHANNEL(this->get_host(),this->clients[i].getnick(), channel)); //RPL_
	}
	
	
	std::cout << GREEN;
	this->look_cha();
	std::cout << RESET;
	// if (this->channels.find(channel) == this->channels.end() || (this->channels[channel].find(clients[i].getusername_host()) == this->channels[channel].end()))
	// {
	// 	this->channels[channel][this->clients[i].getusername_host()] = this->fds[i].fd;
	// 	this->clients[i].add_channel(channel);

	// 	//Esta parte hace el reply al cliente y a los demás
	// 	std::string returnlist = ":" + this->get_host() + " 353 " + clients[i].getusername_host() + " = " + channel + " :"; //RPL_
	// 	std::map<std::string,int>::iterator iter;
	// 	for (iter = this->channels[channel].begin(); iter != this->channels[channel].end(); iter++)
	// 	{
	// 		this->send_message(iter->second, ":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " JOIN " + channel + "\n");
	// 		std::cout << i << " " << iter->second << std::endl;
	// 		returnlist += iter->first + " ";
	// 	} 
	// 	returnlist += "\n";
	// 	this->send_message(this->fds[i].fd, returnlist);
	// 	this->send_message(this->fds[i].fd, ":" + this->get_host() + " 366 " + clients[i].getusername_host() + " " + channel + " :End of /NAMES list.\n"); //RPL_
	// }
	// else
	// 	this->send_message(this->fds[i].fd,ERR_USERONCHANNEL(this->get_host(),this->clients[i].getnick(), channel)); //RPL_
	
	return;
}