#ifndef SBW_H_
#define SBW_H_

#include "../../buffered/bwriter.hpp"
#include "../sw.hpp"

#include <cstdio>

template<std::size_t buffer_size = 32>
struct StringBufferedWriter: virtual StringWriter,
                             virtual BufferedWriter<buffer_size> {
  StringBufferedWriter(std::string&);

  ~StringBufferedWriter() {
    BufferedWriter<buffer_size>::flushBuffer();
    close();
  }

  int putChar(char) override;

protected:
  StringBufferedWriter(){};

  int putCharSrc(char) override;
};

template<std::size_t buffer_size>
inline StringBufferedWriter<buffer_size>::StringBufferedWriter(std::string& src):
    StringIO(src) {}

template<std::size_t buffer_size>
inline int StringBufferedWriter<buffer_size>::putChar(char c) {
  return BufferedWriter<buffer_size>::putChar(c);
}

template<std::size_t buffer_size>
inline int StringBufferedWriter<buffer_size>::putCharSrc(char c) {
  return StringWriter::putChar(c);
}


#endif
