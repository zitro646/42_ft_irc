/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:58:51 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/16 17:10:20 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"
#include "replys.hpp"

//ELIMINAR A LOS CANALES de los que pertenece al cliente y rehacer disconnect
void 	server::QUIT	(int i , std::string str , data_running *run)
{
	(void)i;
	(void)str;
	(void)run;
	
	if (str != "")
	{
		std::cout << "Deberia de mandar un mensaje antes de salir"<<std::endl;
		// this->msg_to_all(i, clients[i].getnick() + ":" + &str[find_single_word_on_str(line[2] , "MESSAGE")] + "\n", "");
	}
	this->close_fds_client(i, run);
	return;
}