#include "FileReader.h"

file_reader::file_reader(string file)
{
    nome_file = file.c.str();
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
    main_buffer = buffer;
    return main_buffer;
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
