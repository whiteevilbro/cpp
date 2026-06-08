#ifndef FBRW_H_
#define FBRW_H_

#include "../../buffered/breaderwriter.hpp"
#include "../frw.hpp"
#include "fbr.hpp"
#include "fbw.hpp"

template<std::size_t buffer_size = 32>
struct FileBufferedReaderWriter: virtual FileReaderWriter,
                                 virtual FileBufferedWriter<buffer_size>,
                                 virtual FileBufferedReader<buffer_size>,
                                 virtual BufferedReaderWriter<buffer_size> {
  FileBufferedReaderWriter(FILE* src);
  FileBufferedReaderWriter(const std::string&, bool = false);
};

template<std::size_t buffer_size>
inline FileBufferedReaderWriter<buffer_size>::FileBufferedReaderWriter(const std::string& path, bool destroy):
    FileIO(nullptr), FileReader(nullptr), FileWriter(nullptr), FileReaderWriter(path, destroy), FileBufferedWriter<buffer_size>(src), FileBufferedReader<buffer_size>(src), BufferedReaderWriter<buffer_size>() {}

template<std::size_t buffer_size>
inline FileBufferedReaderWriter<buffer_size>::FileBufferedReaderWriter(FILE* src):
    FileIO(src), FileReader(src), FileWriter(src), FileReaderWriter(src), FileBufferedWriter<buffer_size>(src), FileBufferedReader<buffer_size>(src), BufferedReaderWriter<buffer_size>() { std::cerr << "fbrw\n"; }

#endif
