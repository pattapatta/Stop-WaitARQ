#include <fstream>

#include "frame.hpp"
#include "server_swarq.hpp"

int main(int argc, char ** argv){
  boost::asio::io_service io_service;
  ServerSWARQ s(io_service, atoi(argv[1]));
 
  Frame nome_file_frame;
  unsigned len = s.receive_frame(nome_file_frame);
  
  std::cout << "#Receive " << len << " bytes: " << std::endl
	    << " data: " << nome_file_frame.get_data() << std::endl
	    << " len: " << nome_file_frame.get_data_len() << std::endl
	    << " num: " << nome_file_frame.get_num() << std::endl
            << "-------------------------------------------"
	    << std::endl;

  std::ofstream file(nome_file_frame.get_data());

  std::ostream_iterator<std::string> out(file);

  s.receive_nbyte(out, 1000);

  return 0;
}
