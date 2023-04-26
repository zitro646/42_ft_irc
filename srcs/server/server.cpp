/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:15:25 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/04/27 01:42:26 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

/*###########################################
#			CONSTRUCTOR						#
############################################*/

server::server( void )
{
  return ;
}

server::server( std::string network , std::string prt , std::string pass )
{
	std::vector <std::string>	seglist;
	
	seglist = split_in_vector(network,':');
    if (seglist.size() == 3)
		this->serv_data = (data_server) {seglist[0], seglist[1], seglist[2], prt, pass};
	else
		this->serv_data = (data_server) {"", "", "", prt, pass};
  return ;
}

server::server( const server & var )
{
	(void) var;
	std::cout << "Copy constructor called" << std::endl;
}

server::~server( void ) 
{
	std::cout << "Destructor constructor called" << std::endl;
}

/*###########################################
#			OVERLOADING						#
############################################*/

server & server::operator=(const server &tmp)
{
	(void) tmp;
	std::cout << "Operator equalizer called" << std::endl;
	return *this;
}

std::ostream &operator<<(std::ostream& os, const server &tmp)
{
	os << "Parameter Server called - "<< &tmp << std::endl;
	os << "Operator output called" << std::endl;
	os << "host           |     " << tmp.get_host() << std::endl;
	os << "network pass   |     " << tmp.get_network_pass() << std::endl;
	os << "network port   |     " << tmp.get_network_port() << std::endl;
	os << "password       |     " << tmp.get_password() << std::endl;
	os << "port           |     " << tmp.get_port() << std::endl;
	return (os);
}

/*###########################################
#			PARSEO							#
############################################*/

void server::fds_search_data(void) const
{
	std::cout << "FDS RESULTS" << std::endl;
	for (int i = 0;i < N_CLIENTS ; i++)
		std::cout << "fds[" << i <<"]fd = "<< this->fds[i].fd <<" events = "<< this->fds[i].events << " revents = "<< this->fds[i].revents << std::endl;
}

