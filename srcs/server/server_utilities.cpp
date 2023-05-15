/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utilities.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:37:55 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/15 19:57:39 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

//
void server::look_channels(void) const
{
	std::map<std::string, std::map<std::string, int> >::iterator me_iter;
	std::map<std::string, int>::iterator mi_iter;
	std::map<std::string, std::map<std::string, int> > cn = this->channels;
	std::cout << "Canales en general " << std::endl;
	for (me_iter = cn.begin(); me_iter != cn.end(); me_iter++)
	{
		std::cout << "Canal " << me_iter->first << std::endl;
		for (mi_iter = me_iter->second.begin(); mi_iter != me_iter->second.end(); mi_iter++)
		{
			std::cout << mi_iter->first << " | " << mi_iter->second << std::endl;
		}
		std::cout << "- - - - - - - - -" << std::endl;
	}

	
}

//NEED to test if this works
void server::erase_client_from_channels(int id)
{
	std::set<std::string>::iterator siter;
	std::set<std::string> cn = this->clients[id].getclientchannels();

	for (siter = cn.begin(); siter != cn.end(); siter++)
		this->channels[*siter].erase(this->clients[id].getusername_host());
	// this->channels.find();
	return;
}

int server::msg_to_all(int i, std::string str, std::string channel)
{
	(void) i;
	(void) str;
	std::map<std::string,int>::iterator iter;
	for (iter = this->channels[channel].begin(); iter != this->channels[channel].end(); iter++)
	{
		std::cout << "entra aqui\n";
		if (iter->second != i)
		{
			std::cout << iter->first << iter->second << std::endl;
			this->send_message(iter->second,str);
		}
	} 
	std::cout << str << std::endl;


	// int aux;

	// for (int j = 0; j < N_CLIENTS; j++)
	// {
	// 	if (j == i)
	// 		continue;
	// 	if (j == this->listening_socket)
	// 		break;
	// 	if (this->clients[i].getchannel_title() == this->clients[j].getchannel_title())
	// 	{
	// 		aux = this->send_message(fds[j].fd, str);
	// 		if (!aux)
	// 			return (0);
	// 	}
	// }
	return (1);
}

int server::msg_to_user(std::string str, std::string user)
{
	for (int a = 0; a < N_CLIENTS; a++)
	{
		if (this->clients[a].getnick() == user)
		{
			this->send_message(this->fds[a].fd, str);
			return (0);
		}
	}
	return (1);
}

int		server::get_client_id_by_nick	(std::string nick, data_running *run)
{
    for (int i = 0;i < run->n_active_fds; i++)
        if (this->clients[i].getnick() == nick)
            return (i);
    return (-1);
}

int server::find_client_nick(std::string str, data_running *run)
{
    for (int i = 0;i < run->n_active_fds; i++)
        if (this->clients[i].getnick() == str)
            return (1);
    return (0);
}

int server::find_client_username(std::string str, data_running *run)
{
    for (int i = 0;i < run->n_active_fds; i++)
        if (this->clients[i].getusername_host() == str)
            return (1);
    return (0);
}

int server::find_client_realname(std::string str, data_running *run)
{
    for (int i = 0;i < run->n_active_fds; i++)
        if (this->clients[i].getrealname_host() == str)
            return (1);
    return (0);
}

int server::check_client_NICK_USER(int i)
{
    if (this->clients[i].getnick() == "")
        return (0);
    if (this->clients[i].getrealname_host() == "")
        return (0);
    if (this->clients[i].getusername_host() == "")
        return (0);
    return (1);
}

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
	std::cout << "Valor de str: " << str << std::endl;
    str = str + std::string(buff,bytes);

	if (!(str.find('\n',0) <  str.size()))
	   	return (-1);
	std::cout << get_Time_now() << BLUE << "Message from fd(" << fd << "):"<< std::endl << str << RESET << std::endl;
	return (1);
	// if (str.find('\n',0) <  str.size())
	// {
	// 	std::cout << get_Time_now() << BLUE << "Message from fd(" << fd << "):"<< std::endl << str << RESET << std::endl;
    // 	return (1);
	// }
	// else
	// {
	// 	return (-1);
	// }
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
	std::cout << get_Time_now() << RED << "Reply to fd(" << fd << "):"<< std::endl << str << RESET << std::endl;
  	return (1);
}