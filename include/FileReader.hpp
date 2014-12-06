#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <cstdio>
#include <string>

using namespace std;

class file_reader
{
    private:

        // attributo settato dall'ultima read_next_bytes
        size_t last_read_bytes;

        // file aperto in lettura
        const char* nome_file;

        // indicatore interno della posizione del file
        FILE* stream;

        // dimensione del main buffer
        int main_buff_size;

        // array contenente glu ultimi last_read_bytes letti
        char* main_buffer;

        // privato non implementato, occorre specificare una stringa
        file_reader();

    public:

        // apro un file di nome Nome
        file_reader(string Nome);

        // Leggo i prossimi i bytes
        char* read_next_bytes(size_t i);

        // controllo se sono alla fine del file
        bool file_ended();

        // chiudo il file
        ~file_reader();

        int get_buff_size();


        char* print_bytes(char* out_buffer);
        char* print_bytes(ostream &dest); // TODO
        char* print_bytes(FILE* file);  // TODO


};


#endif // FILEREADER_H
