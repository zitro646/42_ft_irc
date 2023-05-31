/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:57:25 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/31 04:40:01 by miguelangel      ###   ########.fr       */
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
		this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->clients[i].get_name()));
		return;
	}
	line = split_in_vector(str,' ');
	channel = line[0].substr(0, line[0].size());
	if (this->cha.find(channel) == this->cha.end() || !(this->cha[channel].is_client_in_list(this->clients[i].getusername_host())))
	{
		std::cout << "Resultados "<< (this->cha.find(channel) == this->cha.end()) << !(this->cha[channel].is_client_in_list(this->clients[i].getusername_host())) << std::endl;
		//Si el canal no existe añadimos el usuario como el creador del channel (Half-op)
		if (this->cha[channel].getclientlist().size() == 0)
			this->cha[channel].add_client(this->clients[i].getusername_host(),this->fds[i].fd,this->clients[i].getnick(),true);
		else
			this->cha[channel].add_client(this->clients[i].getusername_host(),this->fds[i].fd,this->clients[i].getnick(),false);
		this->clients[i].add_channel(channel);

		//Esta parte hace el reply al cliente y a los demás
		std::string returnlist = ":" + this->clients[i].get_name() + " 353 " + clients[i].getusername_host() + " = " + channel + " :"; //RPL_
		
		std::map<std::string,data_client> cn = this->cha[channel].getclientlist();
		for (std::map<std::string,data_client>::iterator iter = cn.begin(); iter != cn.end(); iter++)
		{
			this->send_message(iter->second.fd, ":" + this->clients[i].get_name() + " JOIN " + channel + "\n");
			returnlist += check_name(iter->second) + " ";
		} 
		returnlist += "\n";
		this->send_message(this->fds[i].fd, returnlist);
		this->send_message(this->fds[i].fd, ":" + this->get_host() + " 366 " + clients[i].getusername_host() + " " + channel + " :End of /NAMES list.\n"); //RPL_

		//Enviamos el topic del canal
		if (this->cha[channel].gettopic().size() == 0)
			this->send_message(this->fds[i].fd, RPL_NOTOPIC(this->clients[i].get_name(), channel));
		else
			this->send_message(this->fds[i].fd, RPL_TOPIC(this->clients[i].get_name(), channel,this->cha[channel].gettopic()));
	
 	}
	else
	{
		std::cout << "Resultados "<< (this->cha.find(channel) == this->cha.end()) << !(this->cha[channel].is_client_in_list(this->clients[i].getusername_host())) << std::endl;
		this->send_message(this->fds[i].fd,ERR_USERONCHANNEL(this->clients[i].get_name(),this->clients[i].getnick(), channel)); //RPL_
	}
	
	
	std::cout << GREEN;
	this->look_cha();
	std::cout << RESET;
	return;
}