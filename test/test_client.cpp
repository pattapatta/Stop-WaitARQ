#include "frame.hpp"
#include "file_reader.hpp"
#include "client_swarq.hpp"

int main(int argc, char ** argv){
  boost::asio::io_service io_service;

  client_swarq c(io_service, argv[1], argv[2], 
		 boost::posix_time::seconds(1));

  std::string fileout = "file_out.txt";
  std::string filein = "file_in.txt";

  const unsigned buffer_size = 1;

  Frame frame_file_name(0, fileout.c_str(), fileout.size()+1);
  c.send_to(frame_file_name);

  file_reader freader("file_in.txt");

  char * buffer = new char [buffer_size+1];

  uint32_t cnt = 0;

  std::cout << "ok" << std::endl;

  while(!freader.file_ended()){
    
    std::cout << "ok" << std::endl;
    
    size_t len = freader.read_next_bytes(buffer, buffer_size);
    
    std::cout << len << " "<< cnt << buffer << std::endl;
    
    Frame frame_file_bytes(cnt, buffer, len);

    cnt = cnt + 1;
    c.send_to(frame_file_bytes);
  }

  std::cout << "oksaas" << std::endl;

  Frame frame_stop("", 0);
  c.send_to(frame_stop);
}
