/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:06:53 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/01 20:45:33 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"

#define RPL_WELCOME(nick) ":localhost 001 " + nick + " : welcome\r\n"
#define RPL_YOURHOST(hostname) ":localhost 002 : Your host is " + hostname + " , running version <version>\r\n"
#define RPL_CREATED ":localhost 003 : This server was created <datetime>\r\n"
#define RPL_MYINFO ":localhost 004 : <client> <servername> <version> <available user modes> <available channel modes> <channel modes with a parameter>\r\n"

//REPLYS NICK
#define ERR_NONICKNAMEGIVEN(ip_server)	":" + ip_server + " 431 :No nickname given\r\n" //NO parametros
#define ERR_ERRONEUSNICKNAME(ip_server) ":" + ip_server + " 432 :Erroneus nickname\r\n" //Nick con caracteres prohibidos
#define ERR_NICKNAMEINUSE(ip_server , nick) ":" + ip_server + " 433 " + nick + " :Nickname is already in use\r\n" //Nick ya en uso

//FALTA implementar ERR_ERRONEUSNICKNAME 
void server::extract_NICK	(int i , std::string str , data_running *run) 
{
	std::vector <std::string>	line;
	std::string nick;
	
	line = split_in_vector(str,' ');
	if ( line.size() >= 2)
	{
		nick = line[1].erase(line[1].find_last_not_of(" \n\r\t")+1);
		if (this->find_client_nick(nick,run))
			this->send_message(this->fds[i].fd,ERR_NICKNAMEINUSE(this->get_host(),nick)); //ERR_NICKNAMEINUSE
		else			
			this->clients[i].setnick(nick);	
	}
	else
		this->send_message(this->fds[i].fd,ERR_NONICKNAMEGIVEN(this->get_host())); // ERR_NONICKNAMEGIVEN

	return;
}

//BASED ON  -> USER <username> <hostname> <servername> :<realname> (RFC 1459)
//REPLYS USER
#define ERR_NEEDMOREPARAMS(ip_server)	":" + ip_server + " 461 :Not enough parameters\r\n" //NO dio parametros
#define ERR_ALREADYREGISTERED(ip_server)	":" + ip_server + " 462 :You may not reregister\r\n" //Ya esta registrado

//Rehacer el extract UserName
void server::extract_USERNAME	(int client_id , std::string str , data_running *run)
{
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

			std::string returnlist = ":" + this->get_host() + " 353 " + clients[i].getusername_host() + " = " + channel + " :"; //RPL_
			std::map<std::string,int>::iterator iter;
			for (iter = this->channels[channel].begin(); iter != this->channels[channel].end(); iter++)
			{
				this->send_message(iter->second, ":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " JOIN " + channel + "\n");
				std::cout << i << " " << iter->second << std::endl;
				returnlist += iter->first + " ";
			} 
			returnlist += "\n";
			this->send_message(this->fds[i].fd, returnlist);
			this->send_message(this->fds[i].fd, ":" + this->get_host() + " 366 " + clients[i].getusername_host() + " " + channel + " :End of /NAMES list.\n"); //RPL_
		}
		else
			this->send_message(this->fds[i].fd,"Server : User is already on channel " + channel + "\n");
	}
	else
		this->send_message(this->fds[i].fd,"Server :Error trying to JOIN channel\n");

	return;
}


// IMPORTANTE FALTAN LOS RPL para autentificar que salio del canal
void 	server::PART_channel	(int i , std::string str , data_running *run)
{
	(void)run;
	std::vector <std::string>	line = split_in_vector(str,' ');
	std::string channel = line[1].substr(0, line[1].size() - 1);
	if (line.size() >= 2)
	{
		
		if (this->channels.find(channel) != this->channels.end() && (this->channels[channel].find(clients[i].getusername_host()) != this->channels[channel].end()))
		{
			this->channels[channel].erase(this->channels[channel].find(clients[i].getusername_host()));
			std::cout << "Server : User "<< clients[i].getnick()<< " deleted from channel "<< channel << std::endl;
		}
		else
		{
			this->send_message(this->fds[i].fd,"Server : User isnt on channel to delete" + channel + "\n");
		}
	}
	else
		this->send_message(this->fds[i].fd,"Server :Error trying to PART channel\n");
	
}

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