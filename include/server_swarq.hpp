#ifndef SERVERSWARQ_HPP
#define SERVERSWARQ_HPP

#include <algorithm> // std::copy
#include <cstdlib>
#include <ctime>
#include <cstdlib>

#include <stdint.h> // UINT32_MAX

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>

#include "frame.hpp"

class ServerSWARQ{
public:

  ServerSWARQ(boost::asio::io_service & io_service,
	      const unsigned short & port);
  size_t receive_frame(Frame &frame);
  template<typename OIter>
  OIter receive_nbyte(OIter out, size_t nbyte);

private:
  uint32_t frame_counter;
  boost::asio::ip::udp::socket socket;
  static const size_t max_length = 1024;
};

#include "server_swarq_templates.hpp"

#endif // SERVERSWARQ_HPP
