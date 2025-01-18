/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:00:33 by miguelangel       #+#    #+#             */
/*   Updated: 2023/06/01 23:41:50 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

//ERR_NOOPERHOST (491) Por como esta no es necesario de momento (no hay MODO)
void server::OPER	(int i , std::string str , data_running *run) 
{	
	(void)i;
    (void)str;
    (void)run;
    std::vector<std::string> aux = split_in_vector(str, ' ');
    
    if (aux.size() == 2)
    {
        if (aux[1] == this->get_password())
        {
            this->clients[i].setop(true);
            this->send_message(this->fds[i].fd,RPL_YOUREOPER(this->clients[i].get_name())); // RPL_YOUREOPER
        }
        else
            this->send_message(this->fds[i].fd,ERR_PASSWDMISMATCH(this->clients[i].get_name())); // ERR_PASSWDMISMATCH
    }
    else
        this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->clients[i].get_name())); // ERR_NEEDMOREPARAMS
}