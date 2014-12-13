#include "frame.hpp"
#include "file_reader.hpp"
#include "client_swarq.hpp"

int main(int argc, char ** argv){
  boost::asio::io_service io_service;

  client_swarq c(io_service, argv[1], argv[2], 
		 boost::posix_time::seconds(1));

  std::string fileout = argv[4];
  std::string filein = argv[3];

  const unsigned buffer_size = atoi(argv[5]);

  Frame frame_file_name(0, fileout.c_str(), fileout.size()+1);
  c.send_to(frame_file_name);

  file_reader freader(filein);

  char * buffer = new char [buffer_size+1];

  uint32_t cnt = 0;

  size_t len;
  size_t nbyte_sent;

  do{     
    len = freader.read_next_bytes(buffer, buffer_size);

    Frame frame_file_bytes(cnt, buffer, len);

    cnt = cnt + 1;
    nbyte_sent = c.send_to(frame_file_bytes);    
  }while(len);

}
