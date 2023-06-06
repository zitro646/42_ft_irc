/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:16:56 by miguelangel       #+#    #+#             */
/*   Updated: 2023/06/06 18:14:01 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

//REDO KILL

//ERR_NOOPERHOST (491) Por como esta no es necesario de momento (no hay MODO)
void server::KILL	(int i , std::string str , data_running *run) 
{	

    std::vector<std::string> aux = split_in_vector(str, ' ');
    std::string reason;

    if (!this->clients[i].getop())
    {
        this->send_message(this->fds[i].fd,ERR_NOPRIVILEGES(this->clients[i].get_name())); // ERR_NOPRIVILEGES
        return;
    }

    reason = ":";
    if (aux.size() >= 2)
        reason = &str[str.find(':', 0)];

    if (aux.size() >= 2)
    {
        for (int x = 0;x < run->n_active_fds; x++)
            if (this->clients[x].getnick() == aux[0])
            {
                if (this->clients[x].getop() == false)
                {
                    this->msg_to_all(this->fds[x].fd, ":" +clients[i].getnick() + " QUIT "+ ": killed " +this->clients[i].get_name() + " " + reason + "\r\n", run);
                    this->send_message(this->fds[x].fd, ":" +clients[i].get_name() + " ERROR "+ ":" + reason + "\r\n");
                    this->close_fds_client(x,run);
                }
                else
                    this->send_message(this->fds[i].fd,ERR_NOPRIVS(this->clients[i].get_name())); // ERR_NOPRIVS
                return;
            }
    }
    else
        this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->clients[i].get_name())); // ERR_NEEDMOREPARAMS
    std::cout << "frase -> "<< str<< std::endl;
}