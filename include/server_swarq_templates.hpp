#ifndef SERVERSWAQR_TEMPLATES_HPP
#define SERVERSWARQ_TEMPLATES_HPP

#include <boost/asio>
#include "frame.hpp"
#include <cstdlib>

template<typename OIter>
ServerSWARQ::ServerSWARQ(boost::asio::io_service,
			 const unsigned short & port)
  : port(p){

    socket = udp::socket socket(io_service, udp::endpoint(udp::v4(), port));
    frame_counter = 0;
}

/*
    Riceve dati da un endpoint, li legge sul socket e li scrive sul buffe con la
      receive from.
*/
size_t ServerSWARQ::receive_frame(Frame &frame){

    // l'endpoint rappresenta il client con cui dialogo
    udp::endpoint remote_endpoint;

    // Buffer temporaneo, poi uso quello di boost
    char[max_length] rcv_buffer;

    boost::system::error_code error;

    // lunghezza del frame letto
    size_t lenght;
    lenght = this->socket.receive_from(rcv_buffer, enpoint, 0 , error);

    char ack_buffer[max_length];
    Frame ack_frame(frame.get_num, "ACK");

    size_t ack_buffer_size;
    ack_buffer_size = ack_frame.serialize(ack_buffer);

    // ispirato da esempio http://www.boost.org/doc/libs/1_35_0/doc/html/boost_asio/tutorial/tutdaytime5.html
    boost::system::error_code ignored_error;
    socket.send_to(boost::asio::buffer(ack_buffer, ack_buffer_size),
                   remote_endpoint, 0, ignored_error, )

    Frame temp(rcv_buffer, lenght);
    frame.swap(temp);
}



#endif // SERVERSWARQ_TEMPLATES_HPP
