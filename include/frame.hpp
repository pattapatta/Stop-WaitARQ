#ifndef FRAME_HPP
#define FRAME_HPP

#include <iostream> // new
#include <cstddef>  //size_t

#include <stdint.h> // uint32_t
#include <stdio.h>  // 
#include <string.h> // memcpy

class Frame{
private:
  uint32_t num;
  char * data;
  size_t data_len;
public:
  Frame();
  Frame(const char * buffer, const size_t & len);
  Frame(const uint32_t & n, const char * d, const size_t & len);
  ~Frame();
  Frame(const Frame & f);

  uint32_t get_num() const;
  char * get_data() const;
  size_t get_data_len() const;

  size_t serialize(char * byte_array) const;
  void swap(Frame & x);
  Frame & operator=(const Frame & x);
};

#endif // FRAME_HPP
