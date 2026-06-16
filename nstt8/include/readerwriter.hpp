#ifndef READERWRITER_H_
#define READERWRITER_H_

#include "reader.hpp"
#include "writer.hpp"

struct ReaderWriter: virtual Reader,
                     virtual Writer {
};

#endif
