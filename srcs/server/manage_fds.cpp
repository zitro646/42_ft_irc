/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fds.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 03:00:06 by mortiz-d          #+#    #+#             */
/*   Updated: 2025/01/18 19:29:43 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

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
        this->clients[run->n_active_fds - 1].clear_Client();
		fds[run->n_active_fds].fd = this->fds[run->n_active_fds - 1].fd;
		fds[run->n_active_fds].events = POLL_IN;
		fds[run->n_active_fds - 1].fd = run->new_sd;
		fds[run->n_active_fds - 1].events = POLLIN;
		std::cout << get_Time_now() << "New client added to the network ..." << std::endl << "Now there are " << run->n_active_fds << " clients connected to the server" << std::endl << std::endl;
		run->n_active_fds++;
		// this->fds_search_data(); // para visualizar los fds
	}
	return (1);
}

int	server::close_fds_client(int i, data_running *run)
{	
	this->erase_client_from_channels(i);
	std::cout << MAGENTA << "- - - - - - - - -" << std::endl;
	this->look_cha();
	std::cout << WHITE << "- - - - - - - - -" << std::endl;
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
                    this->clients[j].clear_Client();
				}
				else
                {
                    clients[j] = clients[j + 1];
					fds[j] = fds[j+1];
                }
            }
			x--;
			run->n_active_fds--;
			std::cout << get_Time_now() << "Closed client [" << i << "] conection ..." << std::endl << "Now there are " << (run->n_active_fds - 1) << " clients connected to the server" << std::endl << std::endl;
		}
	}
	// this->fds_search_data();
	return (1);
}