#include "../server/server.hpp"
#include "replys.hpp"

void server::NAMES	(int i , std::string str , data_running *run)
{
    (void)run;
    std::cout << str << std::endl;

    std::string returnlist = ":" + this->clients[i].get_name() + " 353 " + clients[i].getusername_host() + " = " + str + " :"; //RPL_
    
    std::map<std::string,data_client> cn = this->cha[str].getclientlist();
    for (std::map<std::string,data_client>::iterator iter = cn.begin(); iter != cn.end(); iter++)
    {
    	returnlist += check_name(iter->second) + " ";
    } 
    returnlist += "\n";
    this->send_message(this->fds[i].fd, returnlist);
    this->send_message(this->fds[i].fd, ":" + this->clients[i].get_name() + " 366 " + clients[i].getusername_host() + " " + str + " :End of /NAMES list.\n"); //RPL_
}