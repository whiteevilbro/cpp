#ifndef READER_H_
#define READER_H_

#include "io.hpp"

#include <concepts>
#include <string>

struct Reader: virtual IO {
  template<std::integral T>
  int read(T& dst) {
    T result;
    bool negative = false;

    if (eof())
      return EOF;

    int c = peekChar();
    if (std::is_signed<T>()) {
      if (c == '-') { // hope it'll be optimized
        negative = true;
        shift();
        c = peekChar();
      }
    }

    if (eof() || !std::isdigit(c)) {
      return EOF;
    }

    while (!eof() && std::isdigit(c)) {
      result *= 10;
      result += c - '0';
      shift();
      c = peekChar();
    }

    dst = negative ? -result : std::move(result);
    return 0;
  }

  int read(std::string& dst) {
    std::string result;

    int c;
    while (!eof() && (c = peekChar()) != EOF && !std::isspace(c)) {
      result.push_back(c);
      shift();
    }

    dst = std::move(result);
    return 0;
  }

protected:
  virtual int peekChar() = 0;
  virtual void shift()   = 0;
};

#endif
