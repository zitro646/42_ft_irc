/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:58:51 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/06/01 23:52:16 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

//ELIMINAR A LOS CANALES de los que pertenece al cliente y rehacer disconnect
void 	server::QUIT	(int i , std::string str , data_running *run)
{
	if (str != "")
		this->msg_to_all(i, ": "+ clients[i].getnick() + " QUIT "+ str + "\n", run);
	this->close_fds_client(i, run);
	return;
}