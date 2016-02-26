cmake_minimum_required(VERSION 2.8)

project(final)
include_directories("./http/" "./serv/")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS program_options filesystem system REQUIRED)

include_directories(${Boost_INCLUDE_DIR} "./http" "./serv")

link_directories(${Boost_LIBRARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread -lboost_system")
set(SRC_LIST main.cpp ./serv/server.cpp ./serv/session.cpp ./http/mime_type.cpp ./http/reply.cpp ./http/request_handler.cpp ./http/request_parser.cpp )
add_executable(final ${SRC_LIST})

target_link_libraries(final ${Boost_LIBRARIES} )

