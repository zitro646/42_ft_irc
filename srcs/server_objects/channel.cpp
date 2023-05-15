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

channel::channel( void ) //: channel_name("")
{
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
  // std::cout << "Operator Client equalizer called" << std::endl;
  return (*this);
}

std::ostream &operator<<(std::ostream& os, const channel &tmp)
{
  (void)(tmp);
	os << "Channels |     ";
	return (os);
}

void	add_client	(std::string str , int fd) 
{
  (void)(str);
  (void)(fd);
  // this->client_list.insert(str , fd);
  return;
}