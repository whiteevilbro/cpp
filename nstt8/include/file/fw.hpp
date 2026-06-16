#ifndef FW_H_
#define FW_H_

#include "../writer.hpp"
#include "fio.hpp"

#include <cstdio>

struct FileWriter: virtual FileIO,
                   virtual Writer {
  FileWriter(const std::string&);
  FileWriter(FILE*);

protected:
  // FileWriter(){};
  int putChar(char) override;
};

inline FileWriter::FileWriter(const std::string& path):
    FileWriter(nullptr) { src = fopen(path.c_str(), "w"); }

inline FileWriter::FileWriter(FILE* src):
    FileIO(src) { std::cerr << "fw\n"; }

inline int FileWriter::putChar(char c) {
  return fputc(c, this->src);
}

#endif
