#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <stdio.h>
#include <string>

using namespace std;

class file_reader
{
    private:

        const char* nome_file;

        FILE* stream;

        char* main_buffer;

        // privato non implementato, occorre specificare una stringa
        file_reader();

    public:

        file_reader(string Nome);

        char* read_next_bytes(size_t i);

        bool file_ended();

        ~file_reader();
};


#endif // FILEREADER_H
