#ifndef FRW_H_
#define FRW_H_

#include "fio.hpp"
#include "fr.hpp"
#include "fw.hpp"

struct FileReaderWriter: virtual FileReader,
                         virtual FileWriter {
  FileReaderWriter(FILE*);
};

inline FileReaderWriter::FileReaderWriter(FILE* src):
    FileIO(src) {}


#endif
