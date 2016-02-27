#include "session.hpp"
#include <utility>
#include <iostream>
#include <fstream>

Session::Session(boost::asio::io_service &io_service,std::string strDir):socket_(io_service),m_reqhdnl(strDir){
    m_iReaded=0;
//    m_result=http::request_parser::indeterminate;
}

void Session::start(){
    socket_.async_read_some(
                boost::asio::buffer(data_,sizeof(data_)),
                boost::bind(&Session::handle_read,this,boost::asio::placeholders::error,
                                    boost::asio::placeholders::bytes_transferred)
                );

}

void Session::close(){
    socket_.close();
}

void Session::do_write(){
//    printf("ok\n");
//    printf("readed %s",data_);
    std::ofstream myfile;
    myfile.open ("example.txt");
    myfile << data_;
    myfile.close();
    boost::asio::async_write(socket_,m_reply.to_buffers(),
            boost::bind(&Session::handle_written,this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
    close();
}

void Session::handle_written(const boost::system::error_code &er, size_t bytes){
//    printf("written\n");
}

void Session::handle_read(const boost::system::error_code &er, size_t bytes){
                if(!er){

                m_iReaded+=bytes;
                std::tie(m_result,std::ignore)=m_reqprs.parse(
                            m_req,data_,data_+m_iReaded+1
                            );
                if(m_result==http::request_parser::good){
                    m_reqhdnl.handle_request(m_req,m_reply);
                    do_write();
                };
                if(m_result==http::request_parser::bad){
                    m_reply=http::reply::stock_reply(http::reply::bad_request);
                    do_write();
                    printf("bad\n");
                }
                }else{
//                    printf("err\n");
                    close();
                }
}

