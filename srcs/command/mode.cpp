/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 00:47:48 by miguelangel       #+#    #+#             */
/*   Updated: 2023/06/16 20:07:16 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

void server::MODE   (int i , std::string str , data_running *run)
{
    (void)run;
    int pos = 0;
    int sign;
    std::string canal;
    std::string nickname;
    std::string modes;
    std::vector <std::string>   line;
    int type;

    line = split_in_vector(str, ' ');
    if (line.size() == 1)
    {
        this->send_message(this->fds[i].fd, ":" + this->serv_data.host + " 324 " + this->clients[i].getnick() + " " + line[0] + " +C" +this->cha[line[0]].getmodes()+ "\n");
        this->send_message(this->fds[i].fd, ":" + this->serv_data.host + " 329 " + this->clients[i].getnick() + " " + line[0] + " 1" + "\n");
    }
    if (line.size() < 2)
        return;
    nickname = line[2];
    canal = line[0];
    if (this->cha.find(canal) == this->cha.end())
       return;
       
    //Comprobamos que ambos esten en la lista y que quien manda la orden sea operador del canal
    if (!(this->cha[canal].is_hostname_client_in_list(this->clients[i].getusername_host())))
        return ;
    if ((this->cha[canal].find_client_by_hostname(this->clients[i].getusername_host())->second.op != 1))
        return;

    modes = this->cha[canal].getmodes();
    while (line[1][pos] != 0)
    {
        type = 1;
        // std::cout << line[1][pos] << std::endl;
        switch (line[1][pos])
        {
            case '+':
            {
                sign=1;
                break;
            }
            case '-':
                sign=-1;
                break;
            case 'n':
            case 'p':
            case 'm':
            case 's':
            case 't':
            {
                
                if (sign == -1)
                {    
                    modes.erase(remove(modes.begin(), modes.end(), line[1][pos]), modes.end());
                }
                else
                {
                    if (modes.find(line[1][pos]) == std::string::npos)
                    {
                        modes+=line[1][pos];
                    }
                }
                std::cout << line[1][pos] << std::endl;
                break;
            }
            case 'v':
                type = 2;
            case 'o':
            {
                if (!(this->cha[canal].is_nick_client_in_list(nickname)))
                return ;
                std::cout<< "entra aqu2i\n";
                this->cha[canal].set_user_op_via_nick(nickname,  this->cha[canal].find_client_by_nickname(line[2])->second.op + (sign * type));
                break;
            }
        }
        pos++;

    }
    this->cha[canal].setmodes(modes);
    
    this->msg_to_channel(this->fds[i].fd, ":" + this->clients[i].get_name() + " MODE " + str + "\r\n", canal);
    this->send_message(this->fds[i].fd, ":" + this->clients[i].get_name() + " MODE " + str + "\r\n");
    
}