#ifndef BUFFEREDIO_H_
#define BUFFEREDIO_H_

#include "../io.hpp"

#include <cstddef>

template<std::size_t buffer_size>
struct BufferedIO: virtual IO {
  BufferedIO();

  void virtual close() override;

  virtual ~BufferedIO() override;

protected:
  char* buffer;
  size_t pos;
};

template<std::size_t buffer_size>
BufferedIO<buffer_size>::BufferedIO():
    pos(0) {
  buffer = new char[buffer_size]();
}

template<std::size_t buffer_size>
void BufferedIO<buffer_size>::close() {
  delete[] buffer;
  buffer = nullptr;
  IO::close();
}

template<std::size_t buffer_size>
BufferedIO<buffer_size>::~BufferedIO<buffer_size>() {
  close();
}

#endif
