#ifndef SERVERSWARQ_HPP
#define SERVERSWARQ_HPP

#include <algorithm> // std::copy

#include "frame.hpp"

template<typename OIter>
class ServerSWARQ{
public:
  ServerSWARQ(boost::asio::io_service io_service, 
	      const unsigned short & p);
  OIter receive_nbyte(OIter out, size_t nbyte);
  Frame receive_frame();
private:
  uint32_t frame_counter;
  boost::asio::io_service & io_service;
  boost::asio::ip::udp::socket socket;
  static const size_t max_length = 1024;
};

#include "server_swarq_templates.hpp"

#endif // SERVERSWARQ_HPP
