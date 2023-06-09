/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:18:00 by miguelangel       #+#    #+#             */
/*   Updated: 2023/06/07 18:25:01 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"


void server::KICK	(int i , std::string str , data_running *run) 
{	
    (void)run;
    std::vector<std::string> aux = split_in_vector(str, ' ');
    std::string 				nick;
    std::string 				channel;
    std::string 				reason;
    

    if (aux.size() < 2)
    {
        this->send_message(this->fds[i].fd, ERR_NEEDMOREPARAMS(this->clients[i].get_name()));
        return;
    }
    
	channel = aux[0].substr(0, aux[0].size());
    nick = aux[1].substr(0, aux[1].size());
    reason = "";
    if (aux.size() >= 2)
        reason = str.substr(str.find(':') + 1);
    std::cout << "KICK ;" << channel << ";" << nick << ";" << reason << ";" << std::endl;
    if (this->cha.find(channel) == this->cha.end())
    {
        this->send_message(this->fds[i].fd, ERR_NOSUCHCHANNEL(this->clients[i].get_name(),channel));
        return;
    }

    if (this->clients[i].getclientchannels().find(channel) == this->clients[i].getclientchannels().end())
    {
        this->send_message(this->fds[i].fd, ERR_NOTONCHANNEL(this->clients[i].get_name(),channel));
        return;
    }
    if(this->cha[channel].find_client_by_hostname(this->clients[i].getusername_host())->second.op == 0)
    {
        this->send_message(this->fds[i].fd, ERR_CHANOPRIVSNEEDED(this->clients[i].get_name(),channel));
        return;
    }  

    std::map<std::string,data_client> cn = this->cha[channel].getclientlist();
	for (std::map<std::string,data_client>::iterator iter = cn.begin(); iter != cn.end(); iter++)
    {
        if (reason == "")
            this->send_message(iter->second.fd, ":" + this->clients[i].get_name() + " KICK " + channel + " " + nick + " :No reason given\n");
        else
            this->send_message(iter->second.fd, ":" + this->clients[i].get_name() + " KICK " + channel + " " + nick + " :"+ reason +"\n");
        
    }

    for(int x = 0;x < run->n_active_fds; x++)
    {
        if (this->clients[x].getnick() == nick)
        {
            this->clients[x].remove_channel(channel);
            this->cha[channel].remove_client(this->clients[x].getusername_host());
            break;
        }
    }
    
}