/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 00:47:48 by miguelangel       #+#    #+#             */
/*   Updated: 2023/06/09 16:38:45 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

void server::MODE   (int i , std::string str , data_running *run)
{
    (void)run;
    std::string canal;
    std::string nickname;
    std::vector <std::string>   line;
    line = split_in_vector(str, ' ');
    if (line.size() != 3)
        return;
    nickname = line[2];
    canal = line[0];
    if (this->cha.find(canal) == this->cha.end())
       return;
    
    //Comprobamos que ambos esten en la lista y que quien manda la orden sea operador del canal
    if (!(this->cha[canal].is_nick_client_in_list(nickname)))
        return ;
    if (!(this->cha[canal].is_hostname_client_in_list(this->clients[i].getusername_host())))
        return ;
    if ((this->cha[canal].find_client_by_hostname(this->clients[i].getusername_host())->second.op != 1))
        return;
    
    this->msg_to_channel(this->fds[i].fd, ":" + this->clients[i].get_name() + " MODE " + str + "\r\n", canal);
    this->send_message(this->fds[i].fd, ":" + this->clients[i].get_name() + " MODE " + str + "\r\n");
}