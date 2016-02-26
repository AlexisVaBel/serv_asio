#include "server.hpp"


Server::Server(std::string strHost, int iPort, std::string strDir, boost::asio::io_service &io_service):
m_iPort(iPort) ,
m_strDir(strDir),
m_strHost(strHost),
io_service_(io_service),
acceptor_(io_service,boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(strHost),iPort)){
    Session *newsession=new Session(io_service_,strDir);
    acceptor_.async_accept(newsession->socket(),
                           boost::bind(&Server::handle_accept,this,newsession,boost::asio::placeholders::error));
}

void Server::handle_accept(Session *newSession,const boost::system::error_code &er){
    if(!er){
//        acceptor_
        newSession->start();
        newSession =new Session(io_service_,m_strDir);
        acceptor_.async_accept(newSession->socket(),
                               boost::bind(&Server::handle_accept,this,newSession,boost::asio::placeholders::error));
    }else{
        delete newSession;
    }
}

