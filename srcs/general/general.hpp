/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:05:27 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/05/16 17:09:11 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_HPP
#define GENERAL_HPP

#define	sock_in		struct sockaddr_in
#define	sock_addr	struct sockaddr
#define N_CLIENTS	2+1			//Numero de Clientes (fd) + el fd del host
#define TIMEOUT_MS	10*1000*60 	//Tiempo de desconexion en caso de no recivir nada

#define SERV_VERS	"0.01"
#define NICK_LENGTH	9
#define USER_LENGTH	9

// Colores
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

#include <poll.h>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <chrono>
#include <ctime>
#include <set>
#include <map>


//Struct para almacenar los datos del servidor
typedef struct data_server {             
	std::string host;
	std::string network_port;
	std::string network_pass;
	std::string port;
	std::string password;
} data_server; 

//Struct para almacenar los datos que debe tener el servidor activo
typedef struct data_running {            
	bool		status;
	int			poll_result;
	int			new_sd;
	int			n_active_fds;
} data_running; 

//Funciones que cualquiera puede usar
std::vector<std::string> 	split_in_vector(std::string str, char c);
int							find_single_word_on_str (std::string str , std::string word);
int							str_end_word_position (std::string str , std::string end);
bool						check_data_correct(data_server data);
bool						is_server_listening(data_server *serv_data, pollfd *fds);
std::string 				get_Time_now			(void);
bool    					check_nickname_restrictions (std::string nick);
bool    					check_username_restrictions (std::string username);

#endif