#ifndef FRW_H_
#define FRW_H_

#include "../readerwriter.hpp"
#include "fio.hpp"
#include "fr.hpp"
#include "fw.hpp"

struct FileReaderWriter: virtual FileReader,
                         virtual FileWriter,
                         virtual ReaderWriter {
  FileReaderWriter(const std::string&, bool = false);
  FileReaderWriter(FILE*);
};

inline FileReaderWriter::FileReaderWriter(const std::string& path, bool destroy):
    FileReaderWriter(nullptr) { src = fopen(path.c_str(), destroy ? "w+" : "r+"); }

inline FileReaderWriter::FileReaderWriter(FILE* src):
    FileIO(src), FileReader(src), FileWriter(src), ReaderWriter() { std::cerr << "frw\n"; }


#endif
