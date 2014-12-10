#include "server_swarq.hpp"

ServerSWARQ::ServerSWARQ(boost::asio::io_service & io_service,
	    const unsigned short & port) 
  : socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)){
	  
}

/*
 * Riceve dati da un endpoint, li legge sul socket e li scrive sul buffe con la
 * receive from.
 */
size_t ServerSWARQ::receive_frame(Frame & frame){

  // l'endpoint rappresenta il client con cui dialogo
  boost::asio::ip::udp::endpoint remote_endpoint;


  // Buffer temporaneo, poi uso quello di boost
  // ci metto dentro i dati che ricevo dal socket

  // Buffer temporaneo, poi uso quello di boost
  char rcv_buffer[max_length];

  boost::system::error_code error;

  // lunghezza del frame letto
  size_t length;
  length = socket.receive_from(boost::asio::buffer(rcv_buffer, max_length), remote_endpoint, 0 , error);

  Frame recv_frame(rcv_buffer, length);
  frame.swap(recv_frame);

  char ack_buffer[max_length];
  Frame ack_frame(frame.get_num(), "ACK", strlen("ACK")+1);

  size_t ack_buffer_size;
  ack_buffer_size = ack_frame.serialize(ack_buffer);

  // ispirato da esempio http://www.boost.org/doc/libs/1_35_0/doc/html/boost_asio/tutorial/tutdaytime5.html
  boost::system::error_code ignored_error;

  socket.send_to(boost::asio::buffer(ack_buffer, ack_buffer_size),
		 remote_endpoint, 0, ignored_error);
  std::cout << "ACK sent" << std::endl;

  return length;
}

#include "server_swarq_templates.hpp"
