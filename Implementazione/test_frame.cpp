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

class Frame{
private:
  uint32_t num;
  std::string data;
public:
  Frame(boost::asio::const_buffer buffer, size_t len){
    
  }

  Frame(const uint32_t & n, const std::string & d) 
    : num(n), data(d) { }
  
  uint32_t getNum(){
    return num;
  }

  std::string getData(){
    return data;
  }

  std::pair<uint32_t, std::string> serialize(){
    std::pair<uint32_t, std::string> payload(num, data);
    return payload;
  }
};

void handler(const boost::system::error_code& e,
	     std::size_t num_byte){

}

int main(int argc, char ** argv){

  Frame frame(1, "Prova");

  std::pair<uint32_t, std::string> payload = frame.serialize();

  boost::asio::io_service io_service;
  boost::asio::ip::udp::endpoint sender_endpoint(boost::asio::ip::udp::v4(), 0);
  boost::asio::ip::udp::socket socket(io_service, sender_endpoint);

  boost::asio::ip::udp::resolver resolver(io_service);
  boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), argv[1], argv[2]);
  boost::asio::ip::udp::resolver::iterator i = resolver.resolve(query);
  for(uint32_t n = 0; n < 999999; ++n){
    char c [4];
    memset(c, 0, 4);
    memcpy(c, &n, sizeof(uint32_t));
  
    socket.send_to(boost::asio::buffer(c), *i);

    usleep(100);
  }
}

