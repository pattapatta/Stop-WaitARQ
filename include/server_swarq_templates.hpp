#ifndef SERVER_SWARQ_TEMPLATE_HPP
#define SERVER_SWARQ_TEMPLATE_HPP

/* funzione che dato un numero di byte da leggere,
 * riceve pacchetti dalla rete attraverso il protocollo
 * stop and wait ARQ. Accoda i pacchetti ricevuti in un
 * output iterator per comporre l'insieme di dati completo.
 *
 * ritorna la posizione dell'ultimo byte scritto nell'output
 * itearator
 */
template<typename OIter>
OIter ServerSWARQ::receive_nbyte(OIter out, unsigned & nbyte_recv){
  nbyte_recv = 0;

  Frame frame(0, "", 0);

  do{
    // riempio il frame con header e payload ricevuti
    receive_frame(frame);

    //controllo se il frame ricevuto è doppio
    if(frame_counter != frame.get_num() && frame.get_data_len()){
      // accetto il frame e lo accodo nell'output
      char * begin = frame.get_data();
      char * end = begin + frame.get_data_len();
      out = std::copy(begin, end, out);

      // aggiorno il frame_counter (modulo UINT32 MAX per
      // evitare overflow)
      frame_counter = (frame_counter + 1) % UINT32_MAX;

      nbyte_recv = nbyte_recv + frame.get_data_len();
    }
  }while(frame.get_data_len());

  return out;
}

#endif // SERVERSWARQ_TEMPLATES_HPP
