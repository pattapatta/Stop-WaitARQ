#include <fstream>

#include "frame.hpp"
#include "server_swarq.hpp"

void print_usage(){
  std::cout << "test_client <port>" << std::endl
	    << "     port: port to listen;" << std::endl
	    << std::endl;

  std::cout << "     example:" << std::endl
	    << "          $./test_server 25000"
	    << std::endl;
}

int main(int argc, char ** argv){
  boost::asio::io_service io_service;

  if(argc < 2){
    print_usage();
    exit(1);
  }
  

  do{

    ServerSWARQ s(io_service, atoi(argv[1]));
 
    Frame nome_file_frame;
    unsigned len = s.receive_frame(nome_file_frame);
  
    std::ofstream file(nome_file_frame.get_data());

    std::ostreambuf_iterator<char> out (file.rdbuf());

    unsigned nbyte_recv = 0;

    time_t time_begin, time_end;

    const clock_t begin_time = clock();
    s.receive_nbyte(out, nbyte_recv);
    const clock_t end_time = clock();

    double time = (double)(end_time - begin_time)/CLOCKS_PER_SEC;

    std::cout << "#received file: " << nome_file_frame.get_data()
	      << " of " << nbyte_recv << " bytes in "
	      << (float)(end_time - begin_time)/CLOCKS_PER_SEC
	      << " seconds [" << (nbyte_recv/1024)/time << " KB/s]" 
	      << std::endl;

  }while(true);

  return 0;
}
