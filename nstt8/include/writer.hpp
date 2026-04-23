#ifndef WRITER_H_
#define WRITER_H_

#include "io.hpp"

#include <concepts>
#include <string>

struct Writer: virtual IO {
  // virtual ~Writer();

  template<std::integral T>
  int write(T src) {
    std::string res;

    if (src == 0) {
      putChar('0');
      return 0;
    }

    if (src < 0) {
      src = -src;
      putChar('-');
    }

    char r;
    while (src) {
      r = src % 10;
      src /= 10;
      res.push_back(r);
    }

    for (std::string::reverse_iterator it = res.rbegin(); it != res.rend(); ++it) { // auto is for cowards
      if (putChar(*it) == EOF)
        return EOF;
    }

    return 0;
  }

  int write(std::string& src) {
    for (char c : src) {
      if (putChar(c) == EOF)
        return EOF;
    }
    return 0;
  }

protected:
  virtual int putChar(char) = 0;
};

#endif
