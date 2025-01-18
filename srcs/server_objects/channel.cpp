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

channel::channel( void ) : topic(""), modes("")
{
  std::map<std::string, data_client> c;
  client_list = c;
  return ;
}

channel::channel( const channel & var ) {
  *this = var;
  std::cout << "Copy constructor called" << std::endl;

}

channel::~channel( void ) 
{
  return ;
}

channel &channel::operator=(const channel &tmp)
{
  this->client_list = tmp.client_list;
  this->topic = tmp.topic;
  // std::cout << "Operator Client equalizer called" << std::endl;
  return (*this);
}

std::ostream &operator<<(std::ostream& os, const channel &tmp)
{
  std::map<std::string, data_client>::iterator mi_iter;
	std::map<std::string, data_client> cn = tmp.getclientlist();

	os << "Topic " << tmp.gettopic() << std::endl;
  for (mi_iter = cn.begin(); mi_iter != cn.end(); mi_iter++)
		{
			os << "username: '" << mi_iter->first << "' | fd :" << mi_iter->second.fd << "' | nick :" << mi_iter->second.nick << "' | op :" << mi_iter->second.op <<std::endl;
		}
	return (os);
}

void channel::add_client(std::string str, int fd, std::string nick, bool op) 
{
  data_client client;
  client.nick = nick;
  client.fd = fd;
  client.op = op;

  this->client_list[str] = client;
  return;
}

void	channel::remove_client	(std::string str)
{
  this->client_list.erase(str);
  return;
}

std::map<std::string, data_client>::iterator	channel::find_client_by_hostname	(std::string hostname)
{
  return (this->client_list.find(hostname));
}

std::map<std::string, data_client>::iterator	channel::find_client_by_nickname	(std::string nickname)
{
  std::map<std::string, data_client>::iterator iter;
  std::map<std::string, data_client> cn = this->getclientlist();
  for (iter = cn.begin();iter != cn.end();iter++)
  {
    if (iter->second.nick == nickname)
      return iter;
  }
  iter = cn.end();
  return(iter);
}

void	channel::set_user_op_via_nick(std::string nickname, int status)
{
  std::cout << status << std::endl;
  if (status < 0)
    status = 0;
  std::map<std::string, data_client>::iterator iter;
  std::map<std::string, data_client> cn = this->getclientlist();
  for (iter = cn.begin();iter != cn.end();iter++)
  {
    if (iter->second.nick == nickname)
    {
      this->client_list[iter->first].op = status;
      return;
    }
  }
  iter = cn.end();
  return;
}

bool	channel::is_hostname_client_in_list(std::string hostname)
{
  if (this->client_list.find(hostname) != this->client_list.end())
    return (1);
  return(0);
  //return ((this->client_list.find(hostname) != this->client_list.end()));
}

bool	channel::is_nick_client_in_list(std::string nickname)
{
  std::map<std::string, data_client>::iterator iter;
  std::map<std::string, data_client> cn = this->getclientlist();
  for (iter = cn.begin();iter != cn.end();iter++)
  {
    if (iter->second.nick == nickname)
      return 1;
  }
  return(0);
  //return ((this->client_list.find(hostname) != this->client_list.end()));
}

void	channel::modify_nick	(std::string usr , std::string nick)
{
  this->client_list[usr].nick = nick;
  return;
}