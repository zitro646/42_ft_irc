/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:00:57 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/04/27 17:59:04 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "server/server.hpp"

void leaks (void)
{
	system("leaks -q ircserv");
}

int exit_msg(std::string msg)
{
	std::cout << msg << std::endl;
	return (0);
}

int main(int argc, char **argv)
{
	atexit(leaks);
	(void)argc;
	(void)argv;
	server *serv;
	
	if (argc != 4)
		return (exit_msg("Unexact number of argvs"));
	serv = new server(argv[1], argv[2], argv[3]);
	if (check_data_correct(serv->get_serv_data()))
	{
		std::cout << "GOOD CHECK "<< std::endl << *serv <<std::endl;
		serv->start();
	}
	else
		std::cout << "BAD CHECK "<< std::endl << *serv <<std::endl;
	delete serv;
	return (0);
}
