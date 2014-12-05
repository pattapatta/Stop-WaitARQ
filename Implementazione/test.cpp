#include <iostream>
#include "include/FileReader.h"
using namespace std;

int main(int argc, char* args[]){

    file_reader fr("mio_file");
    size_t t = 1;



    int i = 0;
    while(fr.file_ended()){
        cout << fr.read_next_bytes(2) << endl;
    }

}
