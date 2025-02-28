/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 22:32:30 by miguelangel       #+#    #+#             */
/*   Updated: 2023/06/12 23:44:24 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

//ERR_NOOPERHOST (491) Por como esta no es necesario de momento (no hay MODO)
void server::TOPIC	(int i , std::string str , data_running *run) 
{	
    (void)run;
    std::vector <std::string>	line = split_in_vector(str,' ');
	std::string 				channel;
    std::string 				topic;
	channel = line[0].substr(0, line[0].size());
    
    if ((str.find(':',0) <= (str.size())))
        topic = &str[str.find(':',0) + 1];
    else
        topic = "";
    
    if (this->cha.find(channel) == this->cha.end())
    {
        this->send_message(this->fds[i].fd,ERR_NOSUCHCHANNEL(this->clients[i].get_name(),channel));
        return;
    }

    if (!this->cha[channel].is_hostname_client_in_list(this->clients[i].getusername_host()))
    {
        this->send_message(this->fds[i].fd,ERR_NOTONCHANNEL(this->clients[i].get_name(),channel));
        return;
    }
    
    //Una vez hacemos las comprobaciones basicas hacemos las normales
    if (topic == "")
       {
        if (this->cha[channel].gettopic() != "")
            this->send_message(this->fds[i].fd,RPL_TOPIC(this->clients[i].get_name(),channel,this->cha[channel].gettopic()));//Devolverle el topic del canal
        else
            this->send_message(this->fds[i].fd,RPL_NOTOPIC(this->clients[i].get_name(),channel));//Devolverle el topic del canal
    }
    else
    {
        if ((this->cha[channel].getmodes().find('t') != std::string::npos) &&\
            this->cha[channel].find_client_by_hostname(this->clients[i].getusername_host())->second.op != 1)
        {
            this->send_message(this->fds[i].fd,ERR_CHANOPRIVSNEEDED(this->clients[i].get_name(),channel));
            return;
        }
        this->cha[channel].settopic(topic);
        this->send_message(this->fds[i].fd,RPL_TOPIC(this->clients[i].get_name(),channel,topic));//Devolverle el topic del canal 
        this->msg_to_channel(this->fds[i].fd,RPL_TOPIC(this->clients[i].get_name(),channel,this->cha[channel].gettopic()),channel);
    }
    }