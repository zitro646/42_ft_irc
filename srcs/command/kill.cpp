/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:16:56 by miguelangel       #+#    #+#             */
/*   Updated: 2023/05/31 04:28:18 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

//ERR_NOOPERHOST (491) Por como esta no es necesario de momento (no hay MODO)
void server::KILL	(int i , std::string str , data_running *run) 
{	
	(void)i;
    (void)str;
    (void)run;
    std::vector<std::string> aux = split_in_vector(str, ' ');
    if (!this->clients[i].getop())
    {
        this->send_message(this->fds[i].fd,ERR_NOPRIVILEGES(this->clients[i].get_name())); // ERR_NOPRIVILEGES
        return;
    }

    if (aux.size() == 2)
    {
        for (int x = 0;x < run->n_active_fds; x++)
            if (this->clients[x].getnick() == aux[0] && this->clients[x].getop() == false)
            {
                //this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->clients[i].get_name())); // Necesito enviar el mensaje de eliminado
                return;
            }
            else if (this->clients[x].getnick() == aux[0] && this->clients[x].getop() == true)
            {
                this->send_message(this->fds[i].fd,ERR_NOPRIVS(this->clients[i].get_name())); // ERR_NOPRIVS
                return;
            }
        
    }
    else
        this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->clients[i].get_name())); // ERR_NEEDMOREPARAMS
    std::cout << "frase -> "<< str<< std::endl;
}