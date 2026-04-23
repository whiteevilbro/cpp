#ifndef SRW_H_
#define SRW_H_

#include "sio.hpp"
#include "sr.hpp"
#include "sw.hpp"

struct StringReaderWriter: virtual StringReader,
                           virtual StringWriter {
  StringReaderWriter(std::string&);
};

inline StringReaderWriter::StringReaderWriter(std::string& src):
    StringIO(src) {}

#endif
