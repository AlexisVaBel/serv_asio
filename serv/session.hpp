#ifndef SESSION_H
#define SESSION_H

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <array>
#include <memory>
#include <string>
#include "../http/reply.hpp"
#include "../http/request.hpp"
#include "../http/request_handler.hpp"
#include "../http/request_parser.hpp"




#define MAXLNG 1024*5

using boost::asio::ip::tcp;

class Session{
private:
    tcp::socket socket_;
    int     m_iReaded;
    char data_[MAXLNG];

    http::request                 m_req;
    http::reply                     m_reply;
    http::request_parser     m_reqprs;
    http::request_handler   m_reqhdnl;
    http::request_parser::result_type m_result;
public:
    explicit Session(boost::asio::io_service &io_service, std::string strDir);
    tcp::socket &socket(){return socket_;}
    void    start();
    void    close();
    void    do_write();
    void    handle_written(const boost::system::error_code &er, size_t bytes);
    void    handle_read(const boost::system::error_code &er, size_t bytes);
};

#endif // SESSION_H
