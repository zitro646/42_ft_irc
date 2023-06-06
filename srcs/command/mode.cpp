/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:00:41 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/06/06 20:22:29 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void server::MODE   (int i , std::string str , data_running *run)
{
    (void)run;
    std::vector <std::string>   line;
    line = split_in_vector(str, ' ');
    if (line.size() != 3)
    {
        this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->clients[i].get_name()));
        return;
    }
    if ((this->cha[line[0]].find_client(this->clients[i].getusername_host())->second.op != 1))
    {
        std::cout << this->cha[line[0]].find_client(this->clients[i].getusername_host())->second.op << std::endl;
        this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->clients[i].get_name()));
        return;
    }
    if (this->cha.find(line[0]) != this->cha.end())
    {
       if ((this->cha[line[0]].is_client_in_list(this->cha[line[0]].find_client(line[2])->second.nick)))
       {
            std::cout << line[2] << this->cha[line[0]].is_client_in_list(line[2]) << std::endl;
            return ;
       }
    }
    else
        std::cout << line[0] << std::endl;
    std::map<std::string,data_client> cn = this->cha[line[0]].getclientlist();
    for (std::map<std::string,data_client>::iterator iter = cn.begin(); iter != cn.end(); iter++)
    {
        if (iter->second.nick == line[2])
        {
            iter->second.op = 1;
        }
        this->send_message(iter->second.fd, ":" + this->clients[i].get_name() + " MODE " + str + "\n");
    }
}