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
OIter ServerSWARQ::receive_nbyte(OIter out, size_t nbyte){
  size_t nbyte_recv = 0;

  Frame frame(0, "", 0);

  do{
    // riempio il frame con header e payload ricevuti
    /*nbyte_recv = */receive_frame(frame);

    nbyte_recv = frame.get_data_len();

    //controllo se il frame ricevuto è doppio
    if(frame_counter != frame.get_num() && nbyte_recv){
      // accetto il frame e lo accodo nell'output
      char * begin = frame.get_data();
      char * end = begin + frame.get_data_len();
      out = std::copy(begin, end, out);

      //frame.get_data()[frame.get_data_len()] = '\0';
      /*
      for(int i=0; i<frame.get_data_len(); ++i)
	std::cout << (int)frame.get_data()[i] << " ";

      char c;
      std::cin >> c;
      */
      //*out = std::string(1, frame.get_data()[0]);
      //std::cout << "rcv: "<< frame.get_data_len() << std::endl;
      /*std::cout << "rcv: "
		<< std::string(1, frame.get_data()[0]) << std::endl;
      */
      //++out;

      // aggiorno il frame_counter (modulo UINT32 MAX per
      // evitare overflow
      frame_counter = (frame_counter + 1) % UINT32_MAX;

      // aggiorno il counter dei byte ricevuti con la grandezza
      // del payload del frame
      // nbyte_recv = nbyte_recv + frame.get_data_len();
    }

    //std::cout << "nbyte_recv = " << nbyte_recv << std::endl;
  }while(nbyte_recv);

  return out;
}

#endif // SERVERSWARQ_TEMPLATES_HPP
