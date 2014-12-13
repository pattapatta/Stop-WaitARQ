#ifndef CLIENT_SWARQ_HPP
#define CLIENT_SWARQ_HPP

#include <cstdlib>
#include <iostream>
#include <string>

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include "frame.hpp"
#include "file_reader.hpp"

/* Classe client_swarq
 * 
 * Incapsula i servizi necessari per la comunicazine
 * utilizzando il protocollo di stop & wait ARQ.
 *
 */
class client_swarq{
public:
  client_swarq(boost::asio::io_service & io_service, 
	     const std::string & server, 
	     const std::string & port, 
	     boost::posix_time::seconds t);

  /* Funzione che spedisce un frame (composto da <num, msg>)
   * sul socket. Resta in attesa per l'ack di risposta e 
   * rispedisce in caso di timeout.
   *
   * Al termine ritorna la dimensione del frame spedito
   */
  std::size_t send_to(const Frame & frame);


private:
  /* Funzione che effettua il check del timeout 
   */
  void check_deadline(boost::system::error_code * ec);
  

  /* Funzione richiamata alla ricezione di qualcosa sul socket
   */
  static void handle_receive(const boost::system::error_code& ec, 
			   std::size_t length,
			   boost::system::error_code* out_ec, 
			   std::size_t* out_length){
  *out_ec = ec;
  *out_length = length;
}
  
  boost::asio::ip::udp::endpoint server_endpoint; // ip e porta del server
  boost::asio::io_service & io_service;
  boost::asio::ip::udp::socket socket;
  boost::asio::deadline_timer timer;
  boost::posix_time::time_duration timeout;
  static const size_t max_length = 1024;  // dimensione massima buffer in spedizione
};

#endif // CLIENT_SWARQ_HPP
