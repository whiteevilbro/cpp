#ifndef SW_H_
#define SW_H_

#include "../writer.hpp"
#include "sio.hpp"

struct StringWriter: virtual StringIO,
                     virtual Writer {
  StringWriter(std::string&);

protected:
  StringWriter(){};
  int putChar(char) override;
};

inline StringWriter::StringWriter(std::string& src):
    StringIO(src) {}

inline int StringWriter::putChar(char c) {
  std::string& src = *this->src;
  if (src.length() <= this->pos)
    src.push_back(c);
  else
    src.at(this->pos) = c;
  ++this->pos;
  return 0;
}

#endif
