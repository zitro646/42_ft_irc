/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:58:51 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/24 18:52:47 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

//ELIMINAR A LOS CANALES de los que pertenece al cliente y rehacer disconnect
void 	server::QUIT	(int i , std::string str , data_running *run)
{
	if (str != "")
		this->msg_to_all(i, clients[i].getnick() + " QUIT "+ str + "\n", run);
	this->close_fds_client(i, run);
	return;
}