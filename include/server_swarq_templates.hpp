#ifndef SERVERSWAQR_TEMPLATES_HPP
#define SERVERSWARQ_TEMPLATES_HPP

template<typename OIter>
ServerSWARQ::ServerSWARQ(boost::asio::io_service,
			 const unsigned short & port)
  : port(p){

    socket = udp::socket socket(io_service, udp::endpoint(udp::v4(), port));
    frame_counter = 0;
}

/*
 * Riceve dati da un endpoint, li legge sul socket e li scrive sul buffe con la
 * receive from.
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

/* funzione che dato un numero di byte da leggere,
 * riceve pacchetti dalla rete attraverso il protocollo
 * stop and wait ARQ. Accoda i pacchetti ricevuti in un
 * output iterator per comporre l'insieme di dati completo.
 *
 * ritorna la posizione dell'ultimo byte scritto nell'output
 * itearator 
 */
template<typename OIter>
OIter ServerSWARQ<OIter>::ServeSWARQ(OIter out, size_t nbyte){
  size_t nbyte_recv = 0;
  
  while(nbyte_recv < nbyte){
    Frame frame();

    // riempio il frame con header e payload ricevuti
    receive_frame(frame);
    
    //controllo se il frame ricevuto è doppio
    if(frame_counter != frame.get_num()){
      // accetto il frame e lo accodo nell'output
      char * begin = frame.get_data();
      char * end = begin + frame.get_data_len();
      out = std::copy(begin, end, out);

      // aggiorno il frame_counter (modulo UINT32 MAX per
      // evitare overflow
      frame_counter = (frame_counter + 1) % UINT_32_MAX;

      // aggiorno il counter dei byte ricevuti con la grandezza
      // del payload del frame
      n_byte_recv += frame.get_data_len();
    }
  }
} 

#endif // SERVERSWARQ_TEMPLATES_HPP
