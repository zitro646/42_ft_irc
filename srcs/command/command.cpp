/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:06:53 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/04/30 19:01:53 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"

#define RPL_WELCOME(nick) ":localhost 001 " + nick + " : welcome\r\n"
#define RPL_YOURHOST(hostname) ":localhost 002 : Your host is " + hostname + " , running version <version>\r\n"
#define RPL_CREATED ":localhost 003 : This server was created <datetime>\r\n"
#define RPL_MYINFO ":localhost 004 : <client> <servername> <version> <available user modes> <available channel modes> <channel modes with a parameter>\r\n"

void server::extract_NICK	(int i , std::string str , data_running *run)
{
	(void)run;
	std::vector <std::string>	line;
	int aux;

	aux = find_single_word_on_str(str , NICKNAME);
	
	line = split_in_vector(&str[aux],' ');
	if ( line.size() >= 2)
	{
		line[1].erase(line[1].find_last_not_of(" \n\r\t")+1);
		if (this->find_client_nick(line[1],run))
			this->send_message(this->fds[i].fd,"Server : NICK is already taken\n");
		else			
			this->clients[i].setnick(line[1]);	
	}
	else
		this->send_message(this->fds[i].fd,"Server : Not enought args to set up NICK\n"); // ERR_NONICKNAMEGIVEN

	return;
}

//BASED ON  -> USER <username> <hostname> <servername> :<realname> (RFC 1459)
void server::extract_USERNAME	(int client_id , std::string str , data_running *run)
{
	(void)run;
	std::vector <std::string>	line;
	std::vector <std::string>	line2;
	int aux;

	aux = find_single_word_on_str(str , USERNAME);
	line = split_in_vector(&str[aux],' ');
	line2 = split_in_vector(&str[aux],':');
	if ( line.size() >= 5 && line2.size() == 2)
	{
		line[1].erase(line[1].find_last_not_of(" \n\r\t")+1);
		line2[1].erase(line2[1].find_last_not_of("\n\r\t")+1);

		//Intentamos crear el real name
		if (!this->find_client_realname(line2[1],run))
			this->clients[client_id].setrealname_host(line2[1]);
		else
			this->send_message(this->fds[client_id].fd,"Server : USER realname is already taken \n" );
		//Intentamos crear el user name
		if (!this->find_client_username(line[1],run) && this->clients[client_id].getnick() != "" )
		{
			this->clients[client_id].setusername_host(line[1]);
			this->clients[client_id].setuserip(line[2]);
			this->send_message(this->fds[client_id].fd,RPL_WELCOME(this->clients[client_id].getnick()));
            this->send_message(this->fds[client_id].fd,RPL_YOURHOST(this->clients[client_id].getusername_host()));
            this->send_message(this->fds[client_id].fd,RPL_CREATED);
            this->send_message(this->fds[client_id].fd,RPL_MYINFO);
		}
		else
			this->send_message(this->fds[client_id].fd,"Server : USER username is already taken \n" );
	}
	else
		this->send_message(this->fds[client_id].fd,"Server : Cannot set up USER\n");
  
  	return;
}

void server::extract_MSG	(int i , std::string str , data_running *run)
{
	(void)run;
	int aux;
	std::string channel;
	
	aux = find_single_word_on_str(str , MESSAGE);
	channel = str.substr(8, str.find(" ", 8) - 8);
	if (this->check_client_NICK_USER(i))
	{
		if (channel[0] == '#')
			this->msg_to_all(this->fds[i].fd, ":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " " + &str[aux] + "\n", channel);
		else
			this->msg_to_user(":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " " + &str[aux] + "\n", channel);
	}
	else
		this->send_message(this->fds[i].fd,"Server : Set up ur NICK/USER first before sending an MSG\n");
  return;
}

void server::extract_JOIN	(int i , std::string str , data_running *run)
{
	(void)run;
	std::vector <std::string>	line;
	line = split_in_vector(str,' ');
	std::string channel = line[1].substr(0, line[1].size() - 1);
	if (line.size() == 2)
	{
		if (this->channels.find(channel) == this->channels.end() || (this->channels[channel].find(clients[i].getusername_host()) == this->channels[channel].end()))
		{
			std::cout << channel << std::endl;
			this->channels[channel][this->clients[i].getusername_host()] = this->fds[i].fd;

			std::string returnlist = ":" + this->get_host() + " 353 " + clients[i].getusername_host() + " = " + channel + " :";
			std::map<std::string,int>::iterator iter;
			for (iter = this->channels[channel].begin(); iter != this->channels[channel].end(); iter++)
			{
				this->send_message(iter->second, ":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " JOIN " + channel + "\n");
				std::cout << i << " " << iter->second << std::endl;
				returnlist += iter->first + " ";
			} 
			returnlist += "\n";
			this->send_message(this->fds[i].fd, returnlist);
			this->send_message(this->fds[i].fd, ":" + this->get_host() + " 366 " + clients[i].getusername_host() + " " + channel + " :End of /NAMES list.\n");
		}
		else
			this->send_message(this->fds[i].fd,"Server : User is already on channel " + channel + "\n");
	}
	else
		this->send_message(this->fds[i].fd,"Server :Error trying to JOIN channel\n");

	return;
}

// void server::extract_JOIN	(int i , std::string str , data_running *run)
// {
// 	(void)run;
// 	std::vector <std::string>	line;
// 	line = split_in_vector(str,' ');

// 	if (line.size() == 2)
// 	{
// 		//comprobamos que no este en el mismo canal ya
// 		if (this->clients[i].getchannel_title() == line[1])
// 			this->send_message(this->fds[i].fd,"Server : User is already on channel " +line[1]+ "\n");
// 		else
// 		{
// 			//hace al cliente abandonar su canal y trata de unirle a otro
// 			this->clients[i].setchannel_title(line[1]);
// 			this->send_message(this->fds[i].fd,"Server : User joined channel " +line[1]+ "\n");
// 		}
// 	}
// 	else
// 		this->send_message(this->fds[i].fd,"Server :Error trying to JOIN channel\n");

// 	return;
// }

void 	server::DISCONNECT_client	(int i , std::string str , data_running *run)
{
	(void)run;
	std::vector <std::string>	line;

	line = split_in_vector(str,' ');
	std::cout << "Linea pa eliminar -> "<< str<< std::endl;
	if (line.size() >= 2)
	{
		if (line[1] == "*" || line[1] == this->serv_data.host)
		{
			if (line.size() > 2)
				this->msg_to_all(i, clients[i].getnick() + ":" + &str[find_single_word_on_str(line[2] , MESSAGE)] + "\n", "");
			this->close_fds_client(i, run);
		}
		else
			this->send_message(this->fds[i].fd , "server : Cant disconnect from host "+this->serv_data.host+" beacuse of inapropiate host name -> "+line[1]+ "\n");
		
	}
	else
		this->send_message(this->fds[i].fd,"Server :Error not enought args on disconnect\n");
}