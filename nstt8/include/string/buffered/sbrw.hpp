#ifndef SBRW_H_
#define SBRW_H_

#include "../../buffered/breaderwriter.hpp"
#include "sbr.hpp"
#include "sbw.hpp"

template<std::size_t buffer_size = 32>
struct StringBufferedReaderWriter: virtual StringBufferedWriter<buffer_size>,
                                   virtual StringBufferedReader<buffer_size>,
                                   virtual BufferedReaderWriter<buffer_size> {
  StringBufferedReaderWriter(std::string&);
};

template<std::size_t buffer_size>
inline StringBufferedReaderWriter<buffer_size>::StringBufferedReaderWriter(std::string& src):
    StringIO(src), BufferedIO<buffer_size>() {}

#endif
