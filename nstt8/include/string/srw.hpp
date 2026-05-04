#ifndef SRW_H_
#define SRW_H_

#include "../readerwriter.hpp"
#include "sio.hpp"
#include "sr.hpp"
#include "sw.hpp"

struct StringReaderWriter: virtual StringReader,
                           virtual StringWriter,
                           virtual ReaderWriter {
  StringReaderWriter(std::string&);
};

inline StringReaderWriter::StringReaderWriter(std::string& src):
    StringIO(src) {}

#endif
