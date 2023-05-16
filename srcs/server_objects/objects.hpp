#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../general/general.hpp"

class	client {

	private:
		std::string realname_host;
		std::string username_host;
		std::string nick;
		std::string userip;
		std::string tempcommand;
		std::set<std::string> client_channels;
		bool		op;
	
	public:

		client ( void );
		client ( std::string rh, std::string uh, std::string ni);
		client ( const client & var );
		~client ( void );
		client &operator=(const client &tmp);

		/*###########################################
		#				FUNCTIONS					#
		############################################*/
		void clear_Client	(void);
		void add_channel	(std::string str);
		void remove_channel	(std::string str);
		
		/*###########################################
		#				GETTERS						#
		############################################*/
		std::string 			getnick			(void)	const	{return(this->nick);};
		std::string 			getrealname_host(void)	const 	{return(this->realname_host);};
		std::string 			getusername_host(void)	const 	{return(this->username_host);};
		std::string 			getuserip		(void)	const 	{return(this->userip);};
		std::string 			gettempcommand	(void)	const 	{return(this->tempcommand);};
		bool					getoperator		(void)	const 	{return(this->op);};
		std::set<std::string> 	getclientchannels(void)	const 	{return(this->client_channels);};

		/*###########################################
		#				SETTERS						#
		############################################*/
		void setnick			(std::string str)		{this->nick = str;};
		void setrealname_host	(std::string str)	 	{this->realname_host = str;};
		void setusername_host	(std::string str)	 	{this->username_host = str;};
		void setuserip			(std::string str)	 	{this->userip = str;};
		void settempcommand		(std::string str)	 	{this->tempcommand = str;};
		// void setclientchannels	(std::set<std::string>c){this->client_channels = c;};
		void setuseroperator	(bool		 o)	 		{this->op = o;};
};

std::ostream &operator<<(std::ostream& os, const client &tmp);

class	channel {

	private:
		std::map<std::string, int> client_list;
		std::string					topic;
	public:

		channel ( void );
		// channel ( std::string channel);
		channel ( const channel & var );
		~channel ( void );
		channel &operator=(const channel &tmp);
	
	/*###########################################
	#				OPERATIONS					#
	############################################*/
	void									add_client		(std::string str , int fd);
	void									remove_client	(std::string str);
	std::map<std::string, int>::iterator	find_client	(std::string str);

	/*###########################################
	#				GETTER						#
	############################################*/
	std::string 				gettopic		(void)	const	{return(this->topic);};
	std::map<std::string, int>	getclientlist	(void)	const	{return(this->client_list);};
	
	/*###########################################
	#				SETTER						#
	############################################*/
	void settopic (std::string str)	{this->topic = str;};
};

std::ostream &operator<<(std::ostream& os, const channel &tmp);

#endif
