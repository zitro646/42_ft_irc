/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 22:08:39 by miguelangel       #+#    #+#             */
/*   Updated: 2023/06/01 22:52:44 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"


void server::INVITE	(int i , std::string str , data_running *run) 
{	
    (void)run;
    std::vector<std::string> aux = split_in_vector(str, ' ');
    std::cout << "INVITE CALLED" << std::endl;
    if (aux.size() < 2)
    {
        this->send_message(this->fds[i].fd, ERR_NEEDMOREPARAMS(this->clients[i].get_name()));
        return;
    }
    
    if (this->cha.find(aux[1]) == this->cha.end())
    {
        this->send_message(this->fds[i].fd, ERR_NOSUCHCHANNEL(this->clients[i].get_name(),aux[1]));
        return;
    }

    if (this->cha[aux[1]].getclientlist().find(this->clients[i].getusername_host()) == this->cha[aux[1]].getclientlist().end())
    {
        this->send_message(this->fds[i].fd, ERR_NOTONCHANNEL(this->clients[i].get_name(),aux[1]));
        return;
    }

    std::map<std::string,data_client> cn = this->cha[aux[1]].getclientlist();
    for (std::map<std::string,data_client>::iterator iter = cn.begin(); iter != cn.end(); iter++ )
    {
        if (iter->second.nick == aux[0])
        {
            this->send_message(this->fds[i].fd, ERR_USERONCHANNEL(this->clients[i].get_name(), aux[0], aux[1]));
            return;
        }
    }
    std::cout << "Busca para invitar" << std::endl;
    for (int x = 0; x < run->n_active_fds; x++ )
    {
        if (this->clients[x].getnick() == aux[0])
        {
            this->send_message(this->fds[x].fd, RPL_INVITE(this->clients[i].get_name(), aux[0], aux[1]));
            std::cout << "INVITE devuelto con exito" << std::endl;
            return;
        }
    }
}