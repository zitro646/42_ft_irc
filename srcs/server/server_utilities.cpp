/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utilities.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:37:55 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/04/27 01:52:22 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

// int server::find_client_nick(std::string str, data_running *run)
// {
//     for (int i = 0;i < run->n_active_fds; i++)
//         if (this->clients[i].getnick() == str)
//             return (1);
//     return (0);
// }

// int server::find_client_username(std::string str, data_running *run)
// {
//     for (int i = 0;i < run->n_active_fds; i++)
//         if (this->clients[i].getusername_host() == str)
//             return (1);
//     return (0);
// }

// int server::find_client_realname(std::string str, data_running *run)
// {
//     for (int i = 0;i < run->n_active_fds; i++)
//         if (this->clients[i].getrealname_host() == str)
//             return (1);
//     return (0);
// }

// int server::check_client_NICK_USER(int i)
// {
//     if (this->clients[i].getnick() == "")
//         return (0);
//     if (this->clients[i].getrealname_host() == "")
//         return (0);
//     if (this->clients[i].getusername_host() == "")
//         return (0);
//     return (1);
// }

int server::recv_message(int fd , std::string &str)
{
    char 		buff[4096];
    int bytes;
    
    bytes = recv(fd, buff, sizeof(buff), 0);
    // std::cout << "Bytes recieved -> " << this->get_bytes_recieved() << std::endl;
    if (bytes < 0)
	{
		std::cout << "Error recv() failed " << std::endl;
		return (0);
	}
	if (bytes == 0)
	{
		std::cout << "Connection closed "<< std::endl;
		return (0);;
	}
    str = std::string(buff,bytes);
    return (1);
}

int server::send_message(int fd, std::string str)
{
    int result;

	result = send(fd, str.c_str(), str.size(), 0);
	if (result < 0)
	{
		std::cout << "Error send() failed " << std::endl;
		return (0);
	}
  return (1);
}

int	server::accept_client(data_running *run)
{
	run->new_sd = accept( this->fds[run->n_active_fds - 1].fd, NULL, NULL);
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
		fds[run->n_active_fds].fd = this->fds[run->n_active_fds - 1].fd;
		fds[run->n_active_fds].events = POLL_IN;
		fds[run->n_active_fds - 1].fd = run->new_sd;
		fds[run->n_active_fds - 1].events = POLLIN;
		std::cout << "New client added to the network ..." << std::endl;
		run->n_active_fds++;
		this->fds_search_data(); // para visualizar los fds
	}
	return (1);
}

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
				if (j + 1 == N_CLIENTS)
				{
					fds[j].fd = 0;
					fds[j].events = 0;
					fds[j].revents = 0;
				}
				else
					fds[j] = fds[j+1];
			}
			x--;
			run->n_active_fds--;
		}
	}
	std::cout << "Cerramos connexion con un cliente" << std::endl;
	this->fds_search_data();
	return (1);
}