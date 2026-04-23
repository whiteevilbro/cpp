#ifndef BR_H_
#define BR_H_

#include "../reader.hpp"
#include "bio.hpp"

#include <cstddef>

template<std::size_t buffer_size>
struct BufferedReader: virtual BufferedIO<buffer_size>,
                       virtual Reader {
protected:
  virtual void shift() override;
  virtual int peekChar() override;

  virtual void shiftSrc()   = 0;
  virtual int peekCharSrc() = 0;

  virtual int fillBuffer();
};

template<std::size_t buffer_size>
int BufferedReader<buffer_size>::peekChar() {
  if (!this->pos) {
    if (fillBuffer() == EOF) {
      setstate(eofbit);
      return EOF;
    }
  }
  return this->buffer[this->pos - 1];
}

template<std::size_t buffer_size>
int BufferedReader<buffer_size>::fillBuffer() {
  iostate state = rdstate();
  int c         = peekCharSrc();

  if (c == EOF)
    return EOF;

  char buf[buffer_size];
  size_t i;

  for (i = 0; i < buffer_size && c != EOF; i++) {
    buf[i] = (char) c;
    shiftSrc();
    c = peekCharSrc();
  }
  if (c == EOF && !(state & eofbit))
    clear();

  this->pos = i;

  for (; i > 0; --i) {
    this->buffer[i - 1] = buf[this->pos - i];
  }

  return 0;
}

template<std::size_t buffer_size>
void BufferedReader<buffer_size>::shift() {
  --this->pos;
}

#endif
