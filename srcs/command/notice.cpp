/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:51:53 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/31 04:32:12 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

void server::NOTICE	(int i , std::string str , data_running *run)
{
	(void)run;	
    (void)i;	
    std::string msg;
    std::vector <std::string> target;
    
	if (str == "")
        return;
    target = split_in_vector(str.substr(0, str.find(" ", 0)),',');
    
    if ((str.find(':',0) <= (str.size())))
        msg = &str[str.find(':',0) + 1];
    else
        msg = "";
    
	if (this->clients[i].check_Client_full_data())
	{
		if (target[0][0] == '#' && this->cha.find(target[0]) != this->cha.end())
		{
			this->msg_to_channel(this->fds[i].fd, ":" + this->clients[i].get_name() + " NOTICE " + str + "\n", target[0]);
		}
		else
        {
			this->msg_to_user(":" + this->clients[i].get_name() + " NOTICE " + str + "\n", target[0]);
        }
	}
    
  return;
}