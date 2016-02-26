#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <getopt.h>
#include <string>

#include "./serv/server.hpp"

struct globalArgs_t{
    char *host;     // ip
    int  port;      // port
    char *dir;       // directory

} globalArgs;

static const char *optString="h:p:d:";

using namespace std;
void initGlArgs(){
    globalArgs.host="none";
    globalArgs.port=0;
    globalArgs.dir="dir";
}

void fillGlArgs(int opt){
    switch(opt){
    case 'h':;
    case 'H':
        globalArgs.host=optarg;
    break;
    case 'p':
    case 'P':
        globalArgs.port=stoi(optarg);
    break;
    case 'd':
    case 'D':
        globalArgs.dir=optarg;
    break;
    }
}


int main(int argc, char **argv){
    //work with args
    initGlArgs();
    int opt=0;
    do{
        opt=getopt(argc,argv,optString);
        fillGlArgs(opt);
    }
    while(opt!=-1);
    //~work with args
    if(fork()==0){
	    boost::asio::io_service io_service;
	    Server* serv=new Server(globalArgs.host,globalArgs.port,globalArgs.dir,io_service);
	    io_service.run();
    }
    return 0;
}
