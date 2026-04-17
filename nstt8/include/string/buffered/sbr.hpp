#ifndef SBR_H_
#define SBR_H_

#include "../../buffered/breader.hpp"
#include "../sr.hpp"

template<std::size_t buffer_size = 32>
struct StringBufferedReader: virtual StringReader,
                             virtual BufferedReader<buffer_size> {
  StringBufferedReader(std::string&);

  virtual void shift() override;
  virtual int peekChar() override;

  // ~StringBufferedReader() { close(); }

protected:
  StringBufferedReader(){};

  virtual int peekCharSrc() override;
  virtual void shiftSrc() override;
};

template<std::size_t buffer_size>
inline StringBufferedReader<buffer_size>::StringBufferedReader(std::string& src):
    StringIO(src), BufferedIO<buffer_size>() {}

template<std::size_t buffer_size>
inline int StringBufferedReader<buffer_size>::peekChar() {
  return BufferedReader<buffer_size>::peekChar();
}

template<std::size_t buffer_size>
inline int StringBufferedReader<buffer_size>::peekCharSrc() {
  return StringReader::peekChar();
}

template<std::size_t buffer_size>
inline void StringBufferedReader<buffer_size>::shift() {
  BufferedReader<buffer_size>::shift();
}

template<std::size_t buffer_size>
inline void StringBufferedReader<buffer_size>::shiftSrc() {
  StringReader::shift();
}


#endif
