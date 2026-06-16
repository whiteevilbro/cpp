#ifndef SR_H_
#define SR_H_

#include "../reader.hpp"
#include "sio.hpp"

struct StringReader: virtual StringIO,
                     virtual Reader {
  StringReader(std::string&);

protected:
  StringReader(){};
  int peekChar() override;
  void shift() override;
};

inline StringReader::StringReader(std::string& src):
    StringIO(src) {}

inline int StringReader::peekChar() {
  if (this->pos >= src->length())
    return EOF;
  return this->src->at(this->pos);
}

inline void StringReader::shift() {
  this->pos++;
}

#endif
