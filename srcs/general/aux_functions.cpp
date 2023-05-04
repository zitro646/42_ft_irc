/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josuna-t <josuna-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:33:58 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/04 19:14:30 by josuna-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.hpp"

std::vector<std::string> split_in_vector(std::string str, char c)
{
    std::stringstream 			test(str);
    std::string 				segment;
    std::vector <std::string>	seglist;

    while (std::getline(test,segment,c))
	{
		segment[segment.length()] = '\0';
    	seglist.push_back(segment);
	}
	return (seglist);
}

int find_single_word_on_str (std::string str , std::string word)
{
    std::string newstr(str);
    for (int x = newstr.find(word); x != -1; x = newstr.find(word))
    {
        if (newstr[x + word.length()] == ' ')
            return (x);
        else
            newstr = &newstr[x + word.length()];
    }
    return (-1);
}

int str_end_word_position (std::string str , std::string end)
{
  int aux ;
  
  // std::cout << "crash1.1" << std::endl;
  aux = str.find(end);
  // std::cout << "crash1.2" << std::endl;
  aux += end.length();
  return (aux);
}

std::string get_Time_now (void)
{
    std::time_t now = time(0);
    char* date_time = ctime(&now);

    return (date_time);
}

bool    check_nickname_restrictions (std::string nick)
{
	std::cout << "0 " << std::endl;
    std::cout << nick << std::endl;
    if (nick.empty())
        return (0);
	std::cout << "find last of " << nick.find_first_of(" ,*?!@.") << std::endl;
    if (nick.find_first_of(" ,*?!@.") <= nick.length())
        return (0);
	std::cout << "2 " << std::endl;
    if (nick[0] == '$' || nick[0] == ':')
    	return (0);
	std::cout << "3 " << std::endl;
    if (nick[0] == '&' || nick[0] == '#')
    	return (0);
		// std::cout << "4 " << std::endl;
    return (1);
}