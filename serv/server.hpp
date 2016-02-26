#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <bits/shared_ptr.h>
#include "session.hpp"

class Server{
public:
    Server(std::string strHost, int iPort, std::string strDir,boost::asio::io_service &io_service);
    void    handle_accept(Session *session, const boost::system::error_code &er);
    bool canRun(){return m_bCon;}
    typedef boost::system::error_code   error_code;
private:
    std::string m_strHost;
    std::string m_strDir;
    int            m_iPort;
    bool    m_bCon;

    boost::asio::io_service           &io_service_;
    boost::asio::ip::tcp::acceptor  acceptor_;
};

#endif // SERVER_H
