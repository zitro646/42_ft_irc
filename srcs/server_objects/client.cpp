/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:15:25 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/11/09 13:34:23 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.hpp"

client::client( void ) : realname_host(""), username_host(""), nick(""), tempcommand("") , op(false)
{
  return ;
}

client::client( std::string rh, std::string uh, std::string ni) : realname_host(rh), username_host(uh), nick(ni), tempcommand("") , op(false)
{
  return ;
}

client::client( const client & var ) {
  *this = var;
  std::cout << "Copy constructor called" << std::endl;

}

client::~client( void ) 
{
  return ;
}

client &client::operator=(const client &tmp)
{
  this->nick = tmp.nick;
  this->realname_host = tmp.realname_host;
  this->username_host = tmp.username_host;
  this->op = tmp.op;
  this->client_channels = tmp.client_channels;
  this->tempcommand = tmp.tempcommand;
  // std::cout << "Operator Client equalizer called" << std::endl;
  return (*this);
}

std::ostream &operator<<(std::ostream& os, const client &tmp)
{
  std::set<std::string>::iterator it;
	std::set<std::string> cn;
	cn = tmp.getclientchannels();
	os << "Client output" << std::endl;
	os << "realname_host	|     " << tmp.getrealname_host() << std::endl;
	os << "username_host	|     " << tmp.getusername_host() << std::endl;
	os << "nickname	|     " << tmp.getnick() << std::endl;
	os << "Channels count	|     " << cn.size() << std::endl;
	os << "Channels |     ";
  	for (it = cn.begin(); it != cn.end(); it++)
      os << *it + " ";
	os << std::endl;
	return (os);
}

void client::clear_Client(void)
{
  this->client_channels.clear();
  this->nick = "";
  this->realname_host = "";
  this->username_host = "";
  this->op = false;
  this->tempcommand = "";
  return ;
}

bool client::check_Client_full_data	(void) const
{
  if (this->nick == "" || this->realname_host == "" || this->username_host == "")
    return (0);
  return (1);
}

void client::add_channel	(std::string str)
{
  this->client_channels.insert(str);
  return;
}

void client::remove_channel	(std::string str)
{
  this->client_channels.erase(str);
}

std::string client::get_name(void) const
{
  // clients[i].getnick() + "!~" + clients[i].getusername_host() 
  if (this->check_Client_full_data())
    return(this->getnick() + "!~" + this->getusername_host());
  return("");
}