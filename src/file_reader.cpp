#include "file_reader.hpp"
#include <stdio.h>
#include <string.h>
#include <iostream>

file_reader::file_reader(string file)
{
    main_buff_size = 0;
    main_buffer = NULL;
    nome_file = file.c_str();
    stream = fopen(nome_file,"r");
}

file_reader::~file_reader()
{
    fclose(stream);
}

size_t file_reader::read_next_bytes(char * main_buffer, size_t i)
{
    char buffer[i];
    int control = fread(buffer, sizeof(char), i, stream);
    if(control){
       last_read_bytes = i;
       main_buff_size = control;
       for(int i = 0; i<main_buff_size; i++)
            main_buffer[i] = buffer[i];
       return control;
    }
    else
        return 0;
}

/*
    Scrive i dati letti dalla fread su un buffer specificato
     semplicemente copiandoil puntatore nel parametro main_buff.
     Se il main buff è vuoto non fa nulla.

*/
char* file_reader::print_bytes(char* out_buffer){

    if(main_buffer){
        for( int i = 0; i<main_buff_size; i++)
            out_buffer[i]=main_buffer[i];
        return out_buffer;
    }
    else{
        std::cout << " il main buff è vuoto " << std::endl;
        return out_buffer;
    }
}

char* file_reader::print_bytes(ostream &dest){
    for( int i = 0; i<main_buff_size ; i++)
        dest << (char)main_buffer[i] << endl;
}

char* file_reader::print_bytes(FILE* file){

}
/*
    fread restituisce il numero di dati letti.
    Se il tentativo di lettura del prossimo dato restituisce 0
    allora siamo alla fine del file
*/
bool file_reader::file_ended(){
    char c[1];
    FILE* current = stream;
    
    if(fread(c,sizeof(char),1,current)){
        return true;
    }
    else{
        return false;
    }
}

int file_reader::get_buff_size(){
    return main_buff_size;
}
