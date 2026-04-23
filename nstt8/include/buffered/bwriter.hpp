#ifndef BW_H_
#define BW_H_

#include "../writer.hpp"
#include "bio.hpp"

#include <cstddef>

template<std::size_t buffer_size>
struct BufferedWriter: virtual BufferedIO<buffer_size>,
                       virtual Writer {
  virtual void close() override;

protected:
  virtual int putChar(char) override;
  virtual int putCharSrc(char) = 0;

  virtual int flushBuffer();
};

template<std::size_t buffer_size>
int BufferedWriter<buffer_size>::putChar(char c) {
  if (this->pos == buffer_size) {
    if (flushBuffer() == EOF) {
      setstate(eofbit);
      return EOF;
    }
  }
  this->buffer[this->pos++] = c;
  return 0;
}

template<std::size_t buffer_size>
int BufferedWriter<buffer_size>::flushBuffer() {
  for (size_t i = 0; i < this->pos; i++) {
    if (putCharSrc(this->buffer[i]) == EOF) {
      return EOF;
    }
  }
  this->pos = 0;
  return 0;
}

template<std::size_t buffer_size>
void BufferedWriter<buffer_size>::close() {
  flushBuffer();
  BufferedIO<buffer_size>::close();
}

#endif
