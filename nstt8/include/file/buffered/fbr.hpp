#ifndef FBR_H_
#define FBR_H_

#include "../../buffered/breader.hpp"
#include "../fr.hpp"

#include <cstdio>

template<std::size_t buffer_size = 32>
struct FileBufferedReader: virtual FileReader,
                           virtual BufferedReader<buffer_size> {
  FileBufferedReader(FILE*);

  virtual void shift() override;
  virtual int peekChar() override;

  // ~FileBufferedReader() { close(); }

protected:
  FileBufferedReader(){};

  virtual int peekCharSrc() override;
  virtual void shiftSrc() override;
};

template<std::size_t buffer_size>
inline FileBufferedReader<buffer_size>::FileBufferedReader(FILE* src):
    FileIO(src), BufferedIO<buffer_size>() {}

template<std::size_t buffer_size>
inline int FileBufferedReader<buffer_size>::peekChar() {
  return BufferedReader<buffer_size>::peekChar();
}

template<std::size_t buffer_size>
inline int FileBufferedReader<buffer_size>::peekCharSrc() {
  return FileReader::peekChar();
}

template<std::size_t buffer_size>
inline void FileBufferedReader<buffer_size>::shift() {
  BufferedReader<buffer_size>::shift();
}

template<std::size_t buffer_size>
inline void FileBufferedReader<buffer_size>::shiftSrc() {
  FileReader::shift();
}


#endif
