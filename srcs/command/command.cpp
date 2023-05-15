/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:06:53 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/15 17:48:24 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/server.hpp"

#define RPL_WELCOME(ip_server , nick) ":" + ip_server + " 001 " + nick + " : welcome\r\n"
#define RPL_YOURHOST(ip_server , hostname) ":" + ip_server + " 002 : Your host is " + hostname + " , running version <version>\r\n"
#define RPL_CREATED(ip_server) ":" + ip_server + " 003 : This server was created <datetime>\r\n"
#define RPL_MYINFO(ip_server) ":" + ip_server + " 004 : <client> <servername> <version> <available user modes> <available channel modes> <channel modes with a parameter>\r\n"

#define RPL_LISTSTART(ip_server, username)	":" + ip_server + " 321 "+ username + " Channel : Users Name\r\n"
#define RPL_LIST(ip_server, username , canal, count , topic)	":" + ip_server + " 322 " + username + " " + canal + " " + count + ":" + topic + "\r\n"
#define RPL_LISTEND(ip_server, username)	":" + ip_server + " 323 "+ username + " :End of /LIST list.\n"

#define ERR_NOORIGIN(ip_server)	":" + ip_server + " 409 :No origin specified\r\n"
#define ERR_NOSUCHCHANNEL(ip_server , canal)	":" + ip_server + " " + canal + " 403 :No such channel\r\n"
#define ERR_NONICKNAMEGIVEN(ip_server)	":" + ip_server + " 431 : No nickname given\r\n"
#define ERR_ERRONEUSNICKNAME(ip_server) ":" + ip_server + " 432 : Erroneus nickname\r\n"
#define ERR_NICKNAMEINUSE(ip_server , nick) ":" + ip_server + " 433 " + nick + " : Nickname is already in use\r\n"
#define ERR_NOTONCHANNEL(ip_server , canal)	":" + ip_server + " " + canal + " 442 : You're not on that channel\r\n"
#define ERR_USERONCHANNEL(ip_server , nick , canal)	":" + ip_server + " " + nick + " " + canal + " 443 : is already on channel\r\n"
#define ERR_NEEDMOREPARAMS(ip_server) ":" + ip_server + " 461 : Not enough parameters\r\n"
#define ERR_ALREADYREGISTERED(ip_server)  ":" + ip_server + " 462 : User is already connected on the server\r\n"


void server::NICK	(int i , std::string nick , data_running *run) 
{	
	if ( nick != "")
	{
		std::cout << " Integridad del nick: " << nick << check_nickname_restrictions(nick) << std::endl;
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
void server::USERNAME	(int client_id , std::string str , data_running *run)
{
	std::vector <std::string>	line;
	std::vector <std::string>	line2;

	line = split_in_vector(str,' ');
	line2 = split_in_vector(str,':');
	if (line.size() >= 4 && line2.size() == 2)
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
// PRIVMSG #canal :hola
void server::MSG	(int i , std::string str , data_running *run)
{

	(void)run;
	// std::string receptor = str.substr(0,str.find(":",0) - 1);
	// str = &str[str.find(":",0) + 1];
	// int client_id = this->get_client_id_by_nick(receptor, run);
	
	// this->send_message(this->fds[client_id].fd,str);
	
	
	//:prueba4242!~josuna-t@195.55.210.173 PRIVMSG #canalprueba42 :hola
	
	std::string channel;
	
	channel = str.substr(0, str.find(" ", 0));
	std::cout << channel << " - " << str << "\n";
	if (this->check_client_NICK_USER(i))
	{
		std::cout << "Cliente con datos\n";
		if (channel[0] == '#')
		{
			std::cout << "Busca canal\n";
			this->msg_to_all(this->fds[i].fd, ":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " PRIVMSG " + str + "\n", channel);
		}
		else
			this->msg_to_user(":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " PRIVMSG " + str + "\n", channel);
	}
	else
		this->send_message(this->fds[i].fd,"Server : Set up ur NICK/USER first before sending an MSG\n");
  return;
}

void server::JOIN	(int i , std::string str , data_running *run)
{
	(void)run;
	std::vector <std::string>	line;
	std::string 				channel ;

	if (str == "")
	{
		this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->get_host()));
		return;
	}
	line = split_in_vector(str,' ');
	channel = line[0].substr(0, line[0].size());
	if (this->channels.find(channel) == this->channels.end() || (this->channels[channel].find(clients[i].getusername_host()) == this->channels[channel].end()))
	{
		this->channels[channel][this->clients[i].getusername_host()] = this->fds[i].fd;
		this->clients[i].add_channel(channel);
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
		this->send_message(this->fds[i].fd,ERR_USERONCHANNEL(this->get_host(),this->clients[i].getnick(), channel)); //RPL_
	std::cout << GREEN;
	this->look_channels();
	std::cout << RESET;
	return;
}


// IMPORTANTE FALTAN LOS RPL para autentificar que salio del canal

void 	server::PART	(int i , std::string str , data_running *run)
{
	(void)run;
	std::map<std::string,int>::iterator iter;
	std::vector <std::string>	line;
	std::string 				channel;

	if (str == "")
	{
		this->send_message(this->fds[i].fd,ERR_NEEDMOREPARAMS(this->get_host()));
		return;
	}
	line = split_in_vector(str,' ');
	channel = line[0].substr(0, line[0].size());
	if (this->channels.find(channel) != this->channels.end() && (this->channels[channel].find(clients[i].getusername_host()) != this->channels[channel].end()))
	{
		this->clients[i].remove_channel(channel);
        for (iter = this->channels[channel].begin(); iter != this->channels[channel].end(); iter++)
        {
            this->send_message(iter->second, ":" + clients[i].getnick() + "!~" + clients[i].getusername_host() + " PART " + channel + "\n");
        }
		this->channels[channel].erase(this->channels[channel].find(clients[i].getusername_host()));
		std::cout << "Server : User "<< clients[i].getnick()<< " deleted from channel "<< channel << std::endl;
	}
	else
		this->send_message(this->fds[i].fd,ERR_NOSUCHCHANNEL(this->get_host(),channel));
	// std::cout << "Cliente nuevo status" << std::endl << this->clients[i] << YELLOW;
	std::cout << YELLOW;
	this->look_channels();
	std::cout << RESET;
}


void 	server::LIST	(int i , std::string str , data_running *run)
{
	(void)run;
	(void)str;
	std::vector <std::string>	line;
	std::map<std::string,std::map<std::string,int> >::iterator iter;
	
	this->send_message(this->fds[i].fd,RPL_LISTSTART(this->get_host(),this->clients[i].getusername_host()));
	for (iter = this->channels.begin(); iter != this->channels.end(); iter++)
	{
		this->send_message(this->fds[i].fd,RPL_LIST(this->get_host(),this->clients[i].getusername_host(),iter->first,std::to_string(iter->second.size()),""));
		// std::cout << + (int)iter->second.size();
		// std::cout << i << " " << iter->first << std::endl;
	}
	this->send_message(this->fds[i].fd,RPL_LISTEND(this->get_host(),this->clients[i].getusername_host()));
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