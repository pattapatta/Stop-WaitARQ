#ifndef SERVERSWAQR_TEMPLATES_HPP
#define SERVERSWARQ_TEMPLATES_HPP

template<typename OIter>
ServerSWARQ<OIter>::ServerSWARQ(boost::asio::io_service,
			 const unsigned short & p)
  : port(p){
  
  
  
  
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
