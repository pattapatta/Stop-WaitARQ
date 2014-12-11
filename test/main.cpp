
#include <iostream>
#include "file_reader.hpp"

using namespace std;

int main(int argc, char* args[]){

    file_reader fr = file_reader("mio_file");

    fr.read_next_bytes(5);

    char* buff = new char(fr.get_buff_size());

    // Questa dà problemini..
    buff = fr.print_bytes(buff);

    std::cout <<  buff[1] << " " << std::endl;
    std::cout <<  buff[2] << " " << std::endl;
    std::cout <<  buff[3] << " " << std::endl;


    int a = sizeof(buff);
    std::cout << " size of a " << a << std::endl;

    fr.print_bytes(std::cout);


    for(int i = 0; i<fr.get_buff_size(); i++){
       std::cout <<  buff[i] << " " << std::endl;
    }

}
