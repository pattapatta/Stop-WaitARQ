#include "frame.hpp"
#include "file_reader.hpp"
#include "client_swarq.hpp"

void print_usage(){
  std::cout << "test_client <ip_addr> <port> <path_source_file> "
	    << "<path_dest_file> <buffer_size> <timeout>" << std::endl
	    << "     ip_addr: server address;" << std::endl
	    << "     port: server port;" << std::endl
	    << "     path_source_file: path of the file to send;" << std::endl
	    << "     path_dest_file: " << std::endl
	    << "     buffer_size: num byte per frame" << std::endl
	    << "     timeout: time to wait for ack in milliseconds;" << std::endl
	    << std::endl;

  std::cout << "     example:" << std::endl
	    << "          $./test_client 127.0.0.1 25000 /directory/file.txt /server_dir/new_file.txt 128 500"
	    << std::endl;
}

int main(int argc, char ** argv){
  boost::asio::io_service io_service;

  if(argc < 7){
    print_usage();
    exit(1);
  }

  client_swarq c(io_service, argv[1], argv[2], 
		 boost::posix_time::milliseconds(500));

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
