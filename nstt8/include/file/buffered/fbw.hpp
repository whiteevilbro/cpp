#ifndef FBW_H_
#define FBW_H_

#include "../../buffered/bwriter.hpp"
#include "../fw.hpp"

#include <cstdio>

template<std::size_t buffer_size = 32>
struct FileBufferedWriter: virtual FileWriter,
                           virtual BufferedWriter<buffer_size> {
  FileBufferedWriter(const std::string&);
  FileBufferedWriter(FILE*);

  ~FileBufferedWriter() {
    BufferedWriter<buffer_size>::flushBuffer();
    close();
  }

  int putChar(char) override;

protected:
  // FileBufferedWriter(){};

  int putCharSrc(char) override;
};

template<std::size_t buffer_size>
inline FileBufferedWriter<buffer_size>::FileBufferedWriter(const std::string& path):
    FileWriter(path) {}

template<std::size_t buffer_size>
inline FileBufferedWriter<buffer_size>::FileBufferedWriter(FILE* src):
    FileIO(src), FileWriter(src), BufferedWriter<buffer_size>() { std::cerr << "fbw\n"; }

template<std::size_t buffer_size>
inline int FileBufferedWriter<buffer_size>::putChar(char c) {
  return BufferedWriter<buffer_size>::putChar(c);
}

template<std::size_t buffer_size>
inline int FileBufferedWriter<buffer_size>::putCharSrc(char c) {
  return FileWriter::putChar(c);
}


#endif
