#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstddef> //size_t
#include <sstream>

#include <fstream>

#include <pthread.h>

#include <boost/asio.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp> 

#include "frame.hpp"

char data[] = "Messaggio di prova, speriamo vadI";

int main(int argc, char ** argv){
  Frame frame(1, data, strlen(data));

  boost::asio::io_service io_service;
  boost::asio::ip::udp::endpoint sender_endpoint(boost::asio::ip::udp::v4(), 0);
  boost::asio::ip::udp::socket socket(io_service, sender_endpoint);

  boost::asio::ip::udp::resolver resolver(io_service);
  boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), argv[1], argv[2]);
  boost::asio::ip::udp::resolver::iterator i = resolver.resolve(query);

  char * payload = new char [1024];

  size_t n_byte = frame.serialize(payload);
  
  socket.send_to(boost::asio::buffer(payload, n_byte), *i);
}

