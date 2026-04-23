#ifndef FR_H_
#define FR_H_

#include "../reader.hpp"
#include "fio.hpp"

#include <cstdio>
#include <cstdlib>

struct FileReader: virtual FileIO,
                   virtual Reader {
  FileReader(FILE*);

protected:
  FileReader(){};
  int peekChar() override;
  void shift() override;
};

inline FileReader::FileReader(FILE* src):
    FileIO(src) {}

inline int FileReader::peekChar() {
  int c = getc(this->src);
  if (c == EOF)
    setstate(eofbit);
  else
    ungetc(c, this->src);
  return c;
}

inline void FileReader::shift() {
  getc(this->src);
}

#endif
