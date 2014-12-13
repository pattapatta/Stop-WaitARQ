#include "frame.hpp"

//
// Costruttori
//

/* costruttore senza parametri
*/
Frame::Frame() : num(0), data(0), data_len(0) { }

/* costruisce il frame a partire da un array di byte estraendo
 * il nunero del frame dall'header (4 byte) e il messaggio
 */
Frame::Frame(const char * buffer, const size_t & len){

  size_t num_size = sizeof(uint32_t);
  data_len = len - num_size;

  memcpy(&num, buffer, num_size);

  data = new char [data_len];
  memcpy(data, buffer + num_size, data_len);
}

/* costruisce il pacchetto a partire da un numero di frame ed
 * un messaggio in byte
 */
Frame::Frame(const uint32_t & n, const char * d, const size_t & len)
  : num(n), data_len(len) { 
  
  data = new char [data_len];
  memcpy(data, d, data_len);
}

//
// Distruttore
//
Frame::~Frame(){
  delete [] data;
}

//
// Costruttore di copia
//
Frame::Frame(const Frame & f){
  num = f.num;

  data_len = f.data_len;
  data = new char [data_len];
  memcpy(data, f.data, data_len);
}

uint32_t Frame::get_num() const{
  return num;
}

char* Frame::get_data() const{
  return data;
}

size_t Frame::get_data_len() const{
  return data_len;
}

/* metti in byte_array un array di byte che contengono
 * i 4 byte del numero di frame (header) seguiti dal
 * messaggio
 */
size_t Frame::serialize(char * byte_array) const{
  size_t num_size = sizeof(uint32_t);

  memcpy(byte_array, &num, num_size);
  memcpy(byte_array + num_size, data, data_len);

  return num_size + data_len;
}

void Frame::swap(Frame & x){
  std::swap(num, x.num);
  std::swap(data, x.data);
  std::swap(data_len, x.data_len);
}

Frame & Frame::operator=(const Frame & x){
  Frame tmp(x);
  swap(tmp);
  return *this;
}
