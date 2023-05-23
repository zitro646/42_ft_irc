/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 22:32:30 by miguelangel       #+#    #+#             */
/*   Updated: 2023/05/24 00:10:20 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

//ERR_NOOPERHOST (491) Por como esta no es necesario de momento (no hay MODO)
void server::TOPIC	(int i , std::string str , data_running *run) 
{	
	(void)i;
    (void)str;
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
        this->send_message(this->fds[i].fd,ERR_NOSUCHCHANNEL(this->get_host(),channel));
        return;
    }

    if (!this->cha[channel].is_client_in_list(this->clients[i].getusername_host()))
    {
        this->send_message(this->fds[i].fd,ERR_NOTONCHANNEL(this->get_host(),channel));
        return;
    }
    

    if (topic == "")
    {
        if (this->cha[channel].gettopic() != "")
            this->send_message(this->fds[i].fd,RPL_TOPIC(this->get_host(),channel,this->cha[channel].gettopic()));//Devolverle el topic del canal
        else
            this->send_message(this->fds[i].fd,RPL_NOTOPIC(this->get_host(),channel));//Devolverle el topic del canal
    }
    else
    {
        this->cha[channel].settopic(topic);
        this->send_message(this->fds[i].fd,RPL_TOPIC(this->get_host(),channel,topic));//Devolverle el topic del canal 
    }
}