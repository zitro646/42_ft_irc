/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:59:14 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/16 17:10:02 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

void 	server::PONG	(int i , std::string str , data_running *run)
{
	(void)run;
	std::vector <std::string> line = split_in_vector(str,' ');
	
	if (line.size() >= 1)
		this->send_message(this->fds[i].fd , ":" +this->get_host()+ " PONG "+this->clients[i].getuserip()+" :"+str+"\r\n");
	else
		this->send_message(this->fds[i].fd,ERR_NOORIGIN(this->get_host()));
	return;
}