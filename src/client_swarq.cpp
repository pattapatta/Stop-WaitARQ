#include "client_swarq.hpp"

/*
 */
client_swarq::client_swarq(boost::asio::io_service & io_service, 
			   const std::string & server, 
			   const std::string & port, 
			   boost::posix_time::seconds t) 

  : io_service(io_service), socket(io_service), 
    timer(io_service), timeout(t){

  boost::asio::ip::udp::resolver resolver(io_service);
  boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), 
					      server,
					      port);

  server_endpoint = *resolver.resolve(query);

  socket.open(boost::asio::ip::udp::v4());
}

/*
 */
std::size_t client_swarq::send_to(const Frame & frame){

  boost::system::error_code ec;

  char buffer[max_length];
  char recv_buffer[max_length];
  size_t buffer_size;
  size_t length = 0;

  Frame recv_frame(0, "", 0);

  //trasformo il frame in una serie di byte
  buffer_size = frame.serialize(buffer);   
 
  do{  

    do{
      socket.send_to(boost::asio::buffer(buffer, buffer_size), 
		     server_endpoint, 0, ec);
    
      // set del timer
      timer.expires_from_now(timeout);

      // set della funzione di check del time che verrà richiamata allo
      // scadere
      timer.async_wait(boost::bind(&client_swarq::check_deadline, this, &ec));
 
      // pongo la variabile d'errore al valore
      // "bloccante"
      ec = boost::asio::error::would_block;

      length = 0;

      // set della receive asinctrona
      // _1 e _2 sono dei segnaposto
      socket.async_receive(boost::asio::buffer(recv_buffer, max_length),
			   boost::bind(&client_swarq::handle_receive, 
				       _1, _2, &ec, &length));
    
      // aspetto di ricevere qualcosa
      do 
	io_service.run_one(); 
      while (ec == boost::asio::error::would_block);

  
    }while(ec == boost::asio::error::interrupted);

    // disattivo il timer
    timer.expires_at(boost::posix_time::pos_infin);
    
    // costruisco il frame ricevuto a partire da un
    // array di byte

    recv_frame = Frame(recv_buffer, length);
   
  }while(recv_frame.get_num() !=  frame.get_num()
	 && !strcmp(recv_frame.get_data(), "ACK"));

  return length;
}

/* Funzione abbinata al timer.
 * Viene richimata allo scadere di questo:
 * set della variabile d'errore ec al valore
 * "interrupted". Questo indica al programma principale che
 * il timer è scattato
 */ 
void client_swarq::check_deadline(boost::system::error_code * ec){
  if (timer.expires_at() <= boost::asio::deadline_timer::traits_type::now()){
    *ec = boost::asio::error::interrupted;
    timer.expires_at(boost::posix_time::pos_infin);
  }
}
