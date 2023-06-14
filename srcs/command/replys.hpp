/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replys.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:05:43 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/06/12 23:05:37 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLYS_HPP
#define REPLYS_HPP

#define RPL_WELCOME(client_name , nick) ":" + client_name + " 001 " + nick + " : welcome\r\n"
#define RPL_YOURHOST(client_name , hostname) ":" + client_name + " 002 : Your host is " + hostname + " , running version <version>\r\n"
#define RPL_CREATED(client_name) ":" + client_name + " 003 : This server was created <datetime>\r\n"
#define RPL_MYINFO(client_name) ":" + client_name + " 004 : <client> <servername> <version> <available user modes> <available channel modes> <channel modes with a parameter>\r\n"

#define RPL_LISTSTART(client_name, nick)	":" + client_name + " 321 "+ nick + " Channel :Users  Name\r\n"
#define RPL_LIST(client_name, nick , canal, count , topic)	":" + client_name + " 322 " + nick + " " + canal + " " + count + " :" + topic + "\r\n"
#define RPL_LISTEND(client_name, nick)	":" + client_name + " 323 "+ nick + " :End of /LIST\r\n"

#define RPL_NOTOPIC(client_name , canal)	":" + client_name + " 331 " + canal + " : No topic is set\r\n"
#define RPL_TOPIC(client_name , canal, topic)	":" + client_name + " TOPIC " + canal + " :" + topic + "\r\n"
  //"<client> <nick> <channel>" :mortiz_!~miguelang@139.47.73.236 INVITE mortiz :#4243
#define RPL_INVITE(client_name , cliente, canal)	":" + client_name + " INVITE " + cliente + " :" + canal + "\r\n"


#define RPL_YOUREOPER(client_name)	":" + client_name + " 381 : You are now an IRC operator\r\n"

#define ERR_CANNOTSENDTOCHAN(client_name, canal)	":" + client_name + " " + canal + " 404 :Cannot send to channel\r\n"
#define ERR_NOORIGIN(client_name)	":" + client_name + " 409 :No origin specified\r\n"
#define ERR_NOSUCHCHANNEL(client_name , canal)	":" + client_name + " " + canal + " 403 :No such channel\r\n"
#define ERR_NONICKNAMEGIVEN(client_name)	":" + client_name + " 431 : No nickname given\r\n"
#define ERR_ERRONEUSNICKNAME(client_name) ":" + client_name + " 432 : Erroneus nickname\r\n"
#define ERR_NICKNAMEINUSE(client_name , nick) ":" + client_name + " 433 " + nick + " : Nickname is already in use\r\n"
#define ERR_NOTONCHANNEL(client_name , canal)	":" + client_name + " " + canal + " 442 : You're not on that channel\r\n"
#define ERR_USERONCHANNEL(client_name , nick , canal)	":" + client_name + " " + nick + " " + canal + " 443 : is already on channel\r\n"
#define ERR_NEEDMOREPARAMS(client_name) ":" + client_name + " 461 : Not enough parameters\r\n"
#define ERR_ALREADYREGISTERED(client_name)  ":" + client_name + " 462 : User is already connected on the server\r\n"

#define ERR_PASSWDMISMATCH(client_name)  ":" + client_name + " 464 :Password incorrect\r\n"

#define ERR_NOPRIVILEGES(client_name)  ":" + client_name + " 481 : Permission Denied- You're not an IRC operator\r\n"
#define ERR_CHANOPRIVSNEEDED(client_name , canal)  ":" + client_name + " 482 " + canal + " : You're not channel operator\r\n"
#define ERR_NOPRIVS(client_name)  ":" + client_name + " 723 : Insufficient oper privileges.\r\n"


#endif