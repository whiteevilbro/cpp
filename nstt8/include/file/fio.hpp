#ifndef FIO_H_
#define FIO_H_

#include "../io.hpp"

#include <cstdio>
#include <string>

struct FileIO: virtual IO {
  FileIO(const std::string&) = delete;

  FileIO(FILE* src):
      src(src){};

  virtual ~FileIO() override;

protected:
  FileIO(){};
  FILE* src;
};

inline FileIO::~FileIO() {
  fclose(this->src);
  this->src = nullptr;
}

#endif
