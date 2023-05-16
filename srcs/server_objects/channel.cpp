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

channel::channel( void ) : topic("")
{
  std::map<std::string, int> c;

  client_list = c;
  return ;
}

// channel::channel( std::string str) : channel_name(str)
// {
//   return ;
// }

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
  std::map<std::string, int>::iterator mi_iter;
	std::map<std::string, int> cn = tmp.getclientlist();

	os << "Topic " << tmp.gettopic() << std::endl;
  for (mi_iter = cn.begin(); mi_iter != cn.end(); mi_iter++)
		{
			os << "username: '" << mi_iter->first << "' | fd :" << mi_iter->second << std::endl;
		}
	return (os);
}

void	channel::add_client	(std::string str , int fd) 
{
  this->client_list[str] = fd;
  return;
}

void	channel::remove_client	(std::string str)
{
  this->client_list.erase(str);
  return;
}

std::map<std::string, int>::iterator	channel::find_client	(std::string str)
{
  return (this->client_list.find(str));
}