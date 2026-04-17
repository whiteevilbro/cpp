#ifndef FBRW_H_
#define FBRW_H_

#include "../../buffered/breaderwriter.hpp"
#include "fbr.hpp"
#include "fbw.hpp"

template<std::size_t buffer_size = 32>
struct FileBufferedReaderWriter: virtual FileBufferedWriter<buffer_size>,
                                 virtual FileBufferedReader<buffer_size>,
                                 virtual BufferedReaderWriter<buffer_size> {
  FileBufferedReaderWriter(FILE* src);
};

template<std::size_t buffer_size>
inline FileBufferedReaderWriter<buffer_size>::FileBufferedReaderWriter(FILE* src):
    FileIO(src), BufferedIO<buffer_size>() {}

#endif
