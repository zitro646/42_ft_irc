/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:06:53 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/09 23:10:28 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"

#define RPL_WELCOME(ip_server , nick) ":" + ip_server + " 001 " + nick + " : welcome\r\n"
#define RPL_YOURHOST(ip_server , hostname) ":" + ip_server + " 002 : Your host is " + hostname + " , running version <version>\r\n"
#define RPL_CREATED(ip_server) ":" + ip_server + " 003 : This server was created <datetime>\r\n"
#define RPL_MYINFO(ip_server) ":" + ip_server + " 004 : <client> <servername> <version> <available user modes> <available channel modes> <channel modes with a parameter>\r\n"

//REPLYS NICK
#define ERR_NONICKNAMEGIVEN(ip_server)	":" + ip_server + " 431 :No nickname given\r\n" //NO parametros
#define ERR_ERRONEUSNICKNAME(ip_server) ":" + ip_server + " 432 :Erroneus nickname\r\n" //Nick con caracteres prohibidos
#define ERR_NICKNAMEINUSE(ip_server , nick) ":" + ip_server + " 433 " + nick + " :Nickname is already in use\r\n" //Nick ya en uso

//FALTA implementar ERR_ERRONEUSNICKNAME 
void server::NICK	(int i , std::string nick , data_running *run) 
{	
	if ( nick != "")
	{
		// std::cout << " Integridad del nick " << check_nickname_restrictions(nick) << std::endl;
		if (check_nickname_restrictions(nick))
		{
			if (this->find_client_nick(nick,run))
				this->send_message(this->fds[i].fd,ERR_NICKNAMEINUSE(this->get_host(),nick)); //ERR_NICKNAMEINUSE
			else
				this->clients[i].setnick(nick);
		}
		else
			this->send_message(this->fds[i].fd,ERR_ERRONEUSNICKNAME(this->get_host())); //ERR_ERRONEUSNICKNAME
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
void server::USERNAME	(int client_id , std::string str , data_running *run)
{
	std::vector <std::string>	line;
	std::vector <std::string>	line2;

	// std::cout << "USERNAME :'" << str << "'"<< std::endl;
	line = split_in_vector(str,' ');
	line2 = split_in_vector(str,':');
	if ( line.size() >= 4 && line2.size() == 2)
	{
		line[1].erase(line[1].find_last_not_of(" \n\r\t")+1);
		line2[1].erase(line2[1].find_last_not_of("\n\r\t")+1);

		//Intentamos crear el user name
		if (!this->find_client_username(line[0],run))
		{
			this->clients[client_id].setrealname_host(line2[1]);
			this->clients[client_id].setusername_host(line[0]);
			this->clients[client_id].setuserip(line[2]);
			this->send_message(this->fds[client_id].fd,RPL_WELCOME(this->get_host() , this->clients[client_id].getnick()));
            this->send_message(this->fds[client_id].fd,RPL_YOURHOST( this->get_host() , this->clients[client_id].getusername_host()));
            this->send_message(this->fds[client_id].fd,RPL_CREATED(this->get_host()));
            this->send_message(this->fds[client_id].fd,RPL_MYINFO(this->get_host()));
		}
		else
			this->send_message(this->fds[client_id].fd,ERR_ALREADYREGISTERED(this->get_host()));
	}
	else
		this->send_message(this->fds[client_id].fd,ERR_NEEDMOREPARAMS(this->get_host()));
  
  	return;
}


//Rehacer
void server::MSG	(int i , std::string str , data_running *run)
{
	(void)run;
	int aux;
	std::string channel;
	
	aux = find_single_word_on_str(str , "PRIVMSG");
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

void server::JOIN	(int i , std::string str , data_running *run)
{
	(void)run;
	std::set<std::string> 		client_channels;
	std::vector <std::string>	line = split_in_vector(str,' ');
	std::string channel = line[0].substr(0, line[1].size() - 1);

	if (line.size() == 1)
	{
		if (this->channels.find(channel) == this->channels.end() || (this->channels[channel].find(clients[i].getusername_host()) == this->channels[channel].end()))
		{
			// std::cout << channel << std::endl;
			this->channels[channel][this->clients[i].getusername_host()] = this->fds[i].fd;
			client_channels = this->clients[i].getclientchannels();
			client_channels.insert(channel);
			this->clients[i].setclientchannels(client_channels);
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
	// std::cout << "Cliente nuevo status" << std::endl << this->clients[i];
	return;
}


// IMPORTANTE FALTAN LOS RPL para autentificar que salio del canal
void 	server::PART	(int i , std::string str , data_running *run)
{
	(void)run;
	std::vector <std::string>	line = split_in_vector(str,' ');
	std::string channel = line[0].substr(0, line[1].size() - 1);
	std::set<std::string> 		client_channels;
	std::map<std::string,int>::iterator iter;
	
	if (line.size() >= 1)
	{
		
		if (this->channels.find(channel) != this->channels.end() && (this->channels[channel].find(clients[i].getusername_host()) != this->channels[channel].end()))
		{
			client_channels = this->clients[i].getclientchannels();
			client_channels.erase(channel);
			this->clients[i].setclientchannels(client_channels);
            for (iter = this->channels[channel].begin(); iter != this->channels[channel].end(); iter++)
            {
                this->send_message(iter->second, ":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " PART " + channel + "\n");
            }
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
	// std::cout << "Cliente nuevo status" << std::endl << this->clients[i];
}

void 	server::LIST	(int i , std::string str , data_running *run)
{
	(void)run;
	(void)str;
	std::vector <std::string>	line;
	std::cout << "HOLA\n";
	this->send_message(this->fds[i].fd, ":" + this->get_host() + " 321 " + clients[i].getusername_host() + " Channel : Users Name\n");
		std::map<std::string,std::map<std::string,int> >::iterator iter;
		for (iter = this->channels.begin(); iter != this->channels.end(); iter++)
		{
			this->send_message(this->fds[i].fd, ":" + this->get_host() + " 322 " + clients[i].getusername_host() + " " + iter->first + " " + std::to_string(iter->second.size()) + ":\n");
			std::cout << + (int)iter->second.size();
			std::cout << i << " " << iter->first << std::endl;
		} 
		this->send_message(this->fds[i].fd, ":" + this->get_host() + " 323 " + clients[i].getusername_host() + " :End of /LIST list.\n"); //RPL_
	return;
}

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


// PING REPLIES
#define ERR_NOORIGIN(ip_server)	":" + ip_server + " 409 :No origin specified\r\n" //NO dio parametros para el ping
void 	server::PONG	(int i , std::string str , data_running *run)
{
	(void)run;
	std::vector <std::string> line = split_in_vector(str,' ');
	
	if (line.size() >= 1)
		this->send_message(this->fds[i].fd , ":" +this->get_host()+ " PONG "+this->clients[i].getuserip()+" :"+str+"\r\n");
	else
		this->send_message(this->fds[i].fd,ERR_NOORIGIN(this->get_host()));
	return;
}