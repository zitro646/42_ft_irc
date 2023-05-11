#ifndef SERVER_HPP
#define SERVER_HPP


#include "../general/general.hpp"
#include "../server_objects/objects.hpp"



class server
{

	private:

		client				clients[N_CLIENTS];
		pollfd				fds[N_CLIENTS];
		data_server 		serv_data;
		std::map<std::string, std::map<std::string, int> > channels;

		/*###########################################
		#			CLOSED    	FUNCTIONS			#
		############################################*/
		server	( void );

		/*###########################################
		#			COMMS    	FUNCTIONS			#
		############################################*/
		void	search_fds		(data_running *run);
		int		accept_client	(data_running *run);
		int		recieve_data	(data_running *run, int i);
		int		msg_to_all  	(int i, std::string str, std::string channel);
		int		msg_to_user  	(std::string str, std::string user);
		int		close_fds_client(int i, data_running *run);
		void	analize_msg		(int i , std::string str , data_running *run);

		/*###########################################
		#		UTILITIES    	FUNCTIONS			#
		############################################*/
		int		find_client_nick		(std::string str, data_running *run);
		int 	find_client_username	(std::string str, data_running *run);
		int		find_client_realname	(std::string str, data_running *run);
		int		get_client_id_by_nick	(std::string nick, data_running *run);
		int		check_client_NICK_USER	(int i);
		void	erase_client_from_channels(int id);
		int		recv_message			(int fd, std::string &str);
		int		send_message			(int fd, std::string str);


		/*###########################################
		#			DEBUG    	FUNCTIONS			#
		############################################*/
		void fds_search_data(void) const;
		void look_channels(void)const;

		/*###########################################
		#			COMMANDS    FUNCTIONS			#
		############################################*/
		typedef void (server::*funptr) (int i , std::string str , data_running *run);
		void	MSG					(int i , std::string str , data_running *run);
		void	USERNAME			(int i , std::string str , data_running *run);
		void	NICK				(int i , std::string str , data_running *run);
		void	JOIN				(int i , std::string str , data_running *run);
		void 	QUIT			(int i , std::string str , data_running *run);
		void 	PART				(int i , std::string str , data_running *run);
		void 	PONG				(int i , std::string str , data_running *run);
		void 	LIST				(int i , std::string str , data_running *run);

	public:

		server	( std::string network , std::string prt , std::string pass );
		server 	( const server & var );
		~server ( void );
		server &operator=(const server &tmp);

		/*###########################################
		#				GETTERS						#
		############################################*/
		std::string get_host		(void) const {return(this->serv_data.host);};
		std::string get_network_pass(void) const {return(this->serv_data.network_pass);};
		std::string get_network_port(void) const {return(this->serv_data.network_port);};
		std::string get_port		(void) const {return(this->serv_data.port);};
		std::string get_password	(void) const {return(this->serv_data.password);};
		data_server get_serv_data	(void) const {return(this->serv_data);};
		/*###########################################
		#			INTERFACE	FUNCTIONS			#
		############################################*/
		int		start				(void);
};

std::ostream &operator<<(std::ostream& os, const server &tmp);

sock_in	init_socket_struct(std::string port, std::string host);

#endif
