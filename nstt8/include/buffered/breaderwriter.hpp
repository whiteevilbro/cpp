#ifndef BRW_H_
#define BRW_H_

#include "../readerwriter.hpp"
#include "breader.hpp"
#include "bwriter.hpp"

#include <cstddef>

template<std::size_t buffer_size>
struct BufferedReaderWriter: virtual BufferedReader<buffer_size>,
                             virtual BufferedWriter<buffer_size>,
                             virtual ReaderWriter {
  // protected:
  //   virtual int flushBuffer();
  //   virtual int fillBuffer();
};

// performance-wise, there should be an override to fill/flush buffer functions
// to make them fill/flush only half of buffer, but im too tired and this task is already long enough

// template<std::size_t buffer_size>
// int BufferedReaderWriter<buffer_size>::fillBuffer() {
//   return 0;
// }

// template<std::size_t buffer_size>
// int BufferedReaderWriter<buffer_size>::flushBuffer() {
//   return 0;
// }


#endif
