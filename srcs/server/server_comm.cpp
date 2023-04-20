/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_comm.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:59:58 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/04/17 20:35:53 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

//Esta funcion es el core del proceso del mensaje que nos envia el cliente, aqui recibimos los datos 
// y los procesamos para ejecutar las distintas ordenes.
// void server::analize_msg (int i, std::string str , data_running *run)
// {
// 	std::vector <std::string>line = split_in_vector(str,'\n');
// 	std::string cmd[5] = {NICKNAME,USERNAME,MESSAGE,JOIN,DISCONNECT};
// 	server::funptr function[5] = {&server::extract_NICK, &server::extract_USERNAME, &server::extract_MSG, &server::extract_JOIN, &server::DISCONNECT_client};
//   	if (line.size() >= 1)
// 	{
// 		for (int y = 0; y < (int)line.size(); y++)
// 		{
// 			for (int x = 0; x < 5; x++)
// 			{
// 				if (find_single_word_on_str(line[y], cmd[x]) != -1)
// 					(this->*(function[x]))(i , line[y] , run);
// 			}
// 		}
// 	}
// }

int	server::close_fds_client(int i, data_running *run)
{	
	close(this->fds[i].fd);
	this->fds[i].fd = -1;
	for (int x = 0; x < run->n_active_fds; x++)
	{
		if (fds[x].fd == -1)
		{
			for(int j = x; j < run->n_active_fds; j++)
			{
				fds[j].fd = fds[j+1].fd;
			}
			x--;
			run->n_active_fds--;
		}
	}
	return (1);
}

int server::recieve_data(data_running *run, int i)
{
	bool close_connection;
	std::string str;

	close_connection = false;
	if (!this->recv_message(fds[i].fd, str))//Comprobamos que recibimos el mensaje
		close_connection = true;
	
	if (close_connection)//Si paso algo raro cerramos el cliente ,sino, procesamos el mensaje
	{
		std::cout << "Un error inesperado cerro la conexion del cliente... " << std::endl;
		this->close_fds_client(i, run);
		return (0);
	}
	else
	{
		std::cout << str ;
		// this->analize_msg(i, str, run);//Analizamos el mensaje y mostramos en el terminal los datos no procesados
	}
	return (1);
}

int	server::accept_client(data_running *run)
{
	run->new_sd = accept(this->listening_socket, NULL, NULL);
	if (run->new_sd < 0)
	{
		std::cout << "Error accept failed " << std::endl;
		run->status = false;
		return (0);
	}
	if (run->n_active_fds >= N_CLIENTS)
	{
		std::cout << "CLIENT REJECTED - Error to many clients "<< std::endl;
		this->send_message(run->new_sd,"Cliente rechazado... demasiados clientes\n");
		close(run->new_sd);
	}
	else
	{
		fds[run->n_active_fds].fd = this->listening_socket;
		fds[run->n_active_fds].events = POLL_IN;
		fds[run->n_active_fds - 1].fd = run->new_sd;
		fds[run->n_active_fds - 1].events = POLLIN;
		std::cout << "New client added to the network ..." << std::endl;
		run->n_active_fds++;
	}
	return (1);
}