/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_comm.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:59:58 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/31 06:15:22 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"



/*###########################################
#			THE REAL DEAL					#
############################################*/

//Todo empieza aqui
int	server::start(void)
{
	data_running *serv_run;

	if (!is_server_listening(&this->serv_data, this->fds))
		return (0);

	serv_run = (data_running *)calloc(sizeof(data_running), 1);
	serv_run->n_active_fds = 1;
	serv_run->status = true;
	do
	{
		serv_run->poll_result = poll(this->fds, serv_run->n_active_fds, TIMEOUT_MS);
		if (serv_run->poll_result <= 0) 	//Poll failed
		{
			if (serv_run->poll_result < 0)
				std::cout << "Poll failed ... breaking server " << std::endl;
			else
				std::cout << "TIME_OUT ERROR ... breaking server " << std::endl;
			break;
		}
		//Si recibe alguna llamada buscamos donde fue
		this->search_fds(serv_run);
	}
	while (serv_run->status);
	
	for (int i = 0; i < serv_run->n_active_fds; i++)
	{
		if(fds[i].fd >= 0)
		close(fds[i].fd);
	}
	delete serv_run;
	return (0);
}


void	server::search_fds(data_running *run)
{
	for (int i = 0; i < run->n_active_fds;i++)
	{
		if (this->fds[i].revents ==  0)
			continue;
		if(fds[i].revents != POLLIN && fds[i].revents != 17)
		{
			std::cout << "Error revent is  : " << fds[i].revents << std::endl;
			run->status = false;
			break;
		}
		if (i == run->n_active_fds - 1 )//this->listening_socket) // && run->n_active_fds < N_CLIENTS
     	{
			//Aceptamos el cliente
			if (!this->accept_client(run))
				break;
		}
		else if(fds[i].revents != 17) //17 means quit conexion
		{
			if(!recieve_data(run,i)) //Recibimos el mensaje y lo procesamos, en caso de no recibir nada cerramos la conexion considerando que occurio un error
				this->close_fds_client(i, run);
			
		}
		else //Cerramos la conexion
			this->close_fds_client(i, run);
	}
	return;
}

int server::recieve_data(data_running *run, int i)
{
	int	result;
	std::string str;

	str = this->clients[i].gettempcommand();

	result = this->recv_message(fds[i].fd, str);
	if (result == -1)
	{
		this->clients[i].settempcommand(str);
		return(1);
	}
	this->clients[i].settempcommand("");
	if (result) //Procesamos el mensaje
	{
		this->analize_msg(i, str, run);//Analizamos el mensaje y mostramos en el terminal los datos no procesados
	}
	else //Si paso algo raro cerramos el cliente
	{
		std::cout << "Un error inesperado cerro la conexion del cliente... " << std::endl;
		return (0);
	}
	return (1);
}

//Esta funcion es el core del proceso del mensaje que nos envia el cliente, aqui recibimos los datos 
// y los procesamos para ejecutar las distintas ordenes.
void server::analize_msg (int i, std::string str , data_running *run)
{
	(void) i;
	(void) str;
	(void) run;
	std::vector <std::string>line = split_in_vector(str,'\n');
	std::string cmd[14] = {"NICK","USER","JOIN","PING","PART","LIST","QUIT","PRIVMSG","OPER","KILL","TOPIC","NOTICE", "NAMES" , "KICK"};
	server::funptr function[14] = {&server::NICK, &server::USERNAME, &server::JOIN, &server::PONG,&server::PART,&server::LIST, &server::QUIT,&server::MSG,&server::OPER,&server::KILL,&server::TOPIC,&server::NOTICE,&server::NAMES, &server::KICK};// &server::extract_JOIN,

	
	if (line.size() >= 1)
	{
		for (int y = 0; y < (int)line.size(); y++)
		{
			for (int x = 0; x < 14; x++)
			{
				
				// std::cout  << YELLOW << "Pos msg size " << line[y].size() << RESET << std::endl;
				if (find_single_word_on_str(line[y], cmd[x]) != -1)
				{
					if (line[y].length() == cmd[x].length())
						line[y] =  "";
					else
						line[y] = &line[y][cmd[x].length() + 1];
					(this->*(function[x]))(i , line[y] , run);
					break;
				}
			}
		}
	}
}