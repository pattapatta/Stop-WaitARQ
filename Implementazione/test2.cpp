#include <iostream>

#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <stdio.h>
#include <string>

using namespace std;

class file_reader
{
    private:

        string nome_file;

        FILE* stream;

        // privato non implementato, occorre specificare una stringa
        file_reader();

    public:

        file_reader(string Nome);

        char* read_next_bytes(size_t i);

        bool file_ended();

        ~file_reader();
};


#endif // FILEREADER_H

file_reader::file_reader()
{
    stream = fopen(nome_file,"r");
}

file_reader::~file_reader()
{
    fclose(nome_file);
}

char* file_reader::read_next_bytes(size_t i)
{
    char buffer[i];
    int control = fread(buffer, sizeof(char), i, stream);
    return buffer;
}

bool FileReader::file_ended(){
    char c[1];
    FILE* current = stream;
    if(!fread(c,sizeof(char),1,current)){
        return false;
    }
    else{
        return true;
    }
}


using namespace std;

int main(int argc, char* args[]){

    file_reader fr("mio_file");
    size_t t = 1;



    int i = 0;
    while(fr.file_ended()){
        cout << fr.read_next_bytes(2) << endl;
    }

}
