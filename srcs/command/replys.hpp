/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replys.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:05:43 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/23 23:32:59 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLYS_HPP
#define REPLYS_HPP

#define RPL_WELCOME(ip_server , nick) ":" + ip_server + " 001 " + nick + " : welcome\r\n"
#define RPL_YOURHOST(ip_server , hostname) ":" + ip_server + " 002 : Your host is " + hostname + " , running version <version>\r\n"
#define RPL_CREATED(ip_server) ":" + ip_server + " 003 : This server was created <datetime>\r\n"
#define RPL_MYINFO(ip_server) ":" + ip_server + " 004 : <client> <servername> <version> <available user modes> <available channel modes> <channel modes with a parameter>\r\n"

#define RPL_LISTSTART(ip_server, username)	":" + ip_server + " 321 "+ username + " Channel : Users Name\r\n"
#define RPL_LIST(ip_server, username , canal, count , topic)	":" + ip_server + " 322 " + username + " " + canal + " " + count + ":" + topic + "\r\n"
#define RPL_LISTEND(ip_server, username)	":" + ip_server + " 323 "+ username + " :End of /LIST list.\n"

#define RPL_NOTOPIC(ip_server , canal)	":" + ip_server + " " + canal + " 331 : No topic is set\r\n"
#define RPL_TOPIC(ip_server , canal, topic)	":" + ip_server + " " + canal + " 332 : "+topic+"\r\n"

#define RPL_YOUREOPER(ip_server)	":" + ip_server + " 381 : You are now an IRC operator\r\n"

#define ERR_NOORIGIN(ip_server)	":" + ip_server + " 409 :No origin specified\r\n"
#define ERR_NOSUCHCHANNEL(ip_server , canal)	":" + ip_server + " " + canal + " 403 :No such channel\r\n"
#define ERR_NONICKNAMEGIVEN(ip_server)	":" + ip_server + " 431 : No nickname given\r\n"
#define ERR_ERRONEUSNICKNAME(ip_server) ":" + ip_server + " 432 : Erroneus nickname\r\n"
#define ERR_NICKNAMEINUSE(ip_server , nick) ":" + ip_server + " 433 " + nick + " : Nickname is already in use\r\n"
#define ERR_NOTONCHANNEL(ip_server , canal)	":" + ip_server + " " + canal + " 442 : You're not on that channel\r\n"
#define ERR_USERONCHANNEL(ip_server , nick , canal)	":" + ip_server + " " + nick + " " + canal + " 443 : is already on channel\r\n"
#define ERR_NEEDMOREPARAMS(ip_server) ":" + ip_server + " 461 : Not enough parameters\r\n"
#define ERR_ALREADYREGISTERED(ip_server)  ":" + ip_server + " 462 : User is already connected on the server\r\n"

#define ERR_PASSWDMISMATCH(ip_server)  ":" + ip_server + " 464 :Password incorrect\r\n"

#define ERR_NOPRIVILEGES(ip_server)  ":" + ip_server + " 481 : Permission Denied- You're not an IRC operator\r\n"
#define ERR_NOPRIVS(ip_server)  ":" + ip_server + " 723 : Insufficient oper privileges.\r\n"


#endif