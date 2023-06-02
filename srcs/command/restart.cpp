/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:04:22 by miguelangel       #+#    #+#             */
/*   Updated: 2023/06/02 20:11:51 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

void server::RESTART	(int i , std::string str , data_running *run) 
{
    (void)str;
    int x;
    if (!this->clients[i].getop())
    {
        this->send_message(this->fds[i].fd,ERR_NOPRIVILEGES(this->clients[i].get_name())); // ERR_NOPRIVILEGES
        return;
    }
    
    x = 0;
    while (run->n_active_fds != 1)
    {
        this->send_message(this->fds[x].fd, ":" +clients[i].getnick() + " QUIT : RESTARTING SERVER\r\n");
        this->close_fds_client(x,run);
    }

    // for (int x = 0;x == run->n_active_fds; x = 0)
    // {
        
    // }
}