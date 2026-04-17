#ifndef SIO_H_
#define SIO_H_

#include "../io.hpp"

#include <string>

struct StringIO: virtual IO {
  StringIO(std::string& src):
      src(&src){};

protected:
  StringIO(){};
  std::string* src;
  size_t pos;
};

#endif
