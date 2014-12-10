#include "client_swarq.hpp"

client_swarq::client_swarq(boost::asio::io_service & io_service, const std::string & server, 
			   const std::string & port, boost::posix_time::seconds t) 
  : io_service(io_service), socket(io_service), timer(io_service), timeout(t){

  boost::asio::ip::udp::resolver resolver(io_service);
  boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), server,
					      port);

  server_endpoint = *resolver.resolve(query);

  socket.open(boost::asio::ip::udp::v4());
}
    
std::size_t client_swarq::send_to(const Frame & frame){
  boost::system::error_code ec;
  char buffer[max_length];
  char recv_buffer[max_length];
  size_t buffer_size;
  std::string s;
  size_t length = 0;

    
  buffer_size = frame.serialize(buffer);    
    
  do{
    socket.send_to(boost::asio::buffer(buffer, buffer_size), 
		   server_endpoint, 0, ec);
    
    timer.expires_from_now(timeout);
    timer.async_wait(boost::bind(&client_swarq::check_deadline, this, &ec));
 
    ec = boost::asio::error::would_block;

    length = 0;
    socket.async_receive(boost::asio::buffer(recv_buffer, max_length),
			 boost::bind(&client_swarq::handle_receive, _1, _2, &ec, &length));
    
    do 
      io_service.run_one(); 
    while (ec == boost::asio::error::would_block);

  }while(ec == boost::asio::error::interrupted);
  timer.expires_at(boost::posix_time::pos_infin);
    
  Frame recv_frame(recv_buffer, length);
    
  std::cout << recv_frame.get_num() << " " << recv_frame.get_data() << std::endl;
  /*
    s = recv_frame.get_data();
    }while(s != "ACK");
  */
  return length;
}


void client_swarq::check_deadline(boost::system::error_code * ec){
  if (timer.expires_at() <= boost::asio::deadline_timer::traits_type::now()){
    //socket.cancel();
    //std::cout << "timeout" << std::endl;
    *ec = boost::asio::error::interrupted;
    timer.expires_at(boost::posix_time::pos_infin);
  }
}