/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:00:33 by miguelangel       #+#    #+#             */
/*   Updated: 2023/05/23 20:51:06 by miguelangel      ###   ########.fr       */
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
            this->send_message(this->fds[i].fd,RPL_YOUREOPER(this->get_host())); // RPL_YOUREOPER
        }
        else
            this->send_message(this->fds[i].fd,ERR_PASSWDMISMATCH(this->get_host())); // ERR_PASSWDMISMATCH
    }
    else
        this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->get_host())); // ERR_NEEDMOREPARAMS
    std::cout << "frase -> "<< str<< std::endl;
}