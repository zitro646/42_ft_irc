/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:00:30 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/26 18:21:40 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../server/server.hpp"
#include "replys.hpp"

// void server::NAME	(int i , std::string str , data_running *run)
// {
// 	(void)run;
// 	std::vector <std::string>	line;
// 	std::string 				channel;
	
// 	if (str == "")
// 	{
// 		this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->get_host()));
// 		return;
// 	}
// 	line = split_in_vector(str,' ');
// 	channel = line[0].substr(0, line[0].size());
// 	if (this->cha.find(channel) == this->cha.end() || !(this->cha[channel].is_client_in_list(this->clients[i].getusername_host())))
// 	{
// 		std::cout << "Resultados "<< (this->cha.find(channel) == this->cha.end()) << !(this->cha[channel].is_client_in_list(this->clients[i].getusername_host())) << std::endl;
// 		//Si el canal no existe añadimos el usuario como el creador del channel (Half-op)
// 		if (this->cha[channel].getclientlist().size() == 0)
// 			this->cha[channel].add_client(this->clients[i].getusername_host(),this->fds[i].fd,this->clients[i].getnick(),true);
// 		else
// 			this->cha[channel].add_client(this->clients[i].getusername_host(),this->fds[i].fd,this->clients[i].getnick(),false);
// 		this->clients[i].add_channel(channel);

// 		//Esta parte hace el reply al cliente y a los demás
// 		std::string returnlist = ":" + this->get_host() + " 353 " + clients[i].getusername_host() + " = " + channel + " :"; //RPL_
		
// 		std::map<std::string,data_client> cn = this->cha[channel].getclientlist();
// 		for (std::map<std::string,data_client>::iterator iter = cn.begin(); iter != cn.end(); iter++)
// 		{
// 			this->send_message(iter->second.fd, ":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " JOIN " + channel + "\n");
// 			returnlist += iter->second.nick + " ";
// 		} 
// 		returnlist += "\n";
// 		this->send_message(this->fds[i].fd, returnlist);
// 		this->send_message(this->fds[i].fd, ":" + this->get_host() + " 366 " + clients[i].getusername_host() + " " + channel + " :End of /NAMES list.\n"); //RPL_

// 		//Enviamos el topic del canal
// 		if (this->cha[channel].gettopic().size() == 0)
// 			this->send_message(this->fds[i].fd, RPL_NOTOPIC(this->get_host(), channel));
// 		else
// 			this->send_message(this->fds[i].fd, RPL_TOPIC(this->get_host(), channel,this->cha[channel].gettopic()));
	
//  	}
// 	else
// 	{
// 		std::cout << "Resultados "<< (this->cha.find(channel) == this->cha.end()) << !(this->cha[channel].is_client_in_list(this->clients[i].getusername_host())) << std::endl;
// 		this->send_message(this->fds[i].fd,ERR_USERONCHANNEL(this->get_host(),this->clients[i].getnick(), channel)); //RPL_
// 	}
	
	
// 	std::cout << GREEN;
// 	this->look_cha();
// 	std::cout << RESET;
// 	return;
}