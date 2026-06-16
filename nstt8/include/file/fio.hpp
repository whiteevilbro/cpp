#ifndef FIO_H_
#define FIO_H_

#include "../io.hpp"

#include <cstdio>
#include <iostream>
#include <string>

struct FileIO: virtual IO {
  FileIO(const std::string&) = delete;

  FileIO(FILE* src):
      src(src) { std::cerr << "fio\n"; };

  virtual ~FileIO() override;

protected:
  // FileIO() { std::cerr << "default fio\n"; };

  FILE* src;
};

inline FileIO::~FileIO() {
  fclose(this->src);
  this->src = nullptr;
}

#endif
