#ifndef FW_H_
#define FW_H_

#include "../writer.hpp"
#include "fio.hpp"

#include <cstdio>

struct FileWriter: virtual FileIO,
                   virtual Writer {
  FileWriter(FILE*);

protected:
  FileWriter(){};
  int putChar(char) override;
};

inline FileWriter::FileWriter(FILE* src):
    FileIO(src) {}

inline int FileWriter::putChar(char c) {
  return fputc(c, this->src);
}

#endif
