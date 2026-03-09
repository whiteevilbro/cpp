#ifndef CSP_H_
#define CSP_H_

#include <concepts>

template<std::copy_constructible T>
class CopyingScopedPointer {
  T* pointer;

public:
  CopyingScopedPointer<T>(T* p):
      pointer(p) {}

  CopyingScopedPointer<T>(const CopyingScopedPointer<T>& p) {
    pointer = new T(*p.pointer);
  }

  CopyingScopedPointer<T>& operator=(const CopyingScopedPointer<T>& p) {
    if (this == &p)
      return *this;
    delete pointer;
    pointer = new T(*p.pointer);
    return *this;
  }

  CopyingScopedPointer<T>(CopyingScopedPointer<T>&&)            = delete;
  CopyingScopedPointer<T>& operator=(CopyingScopedPointer<T>&&) = delete;

  ~CopyingScopedPointer<T>() {
    delete pointer;
  }

  T& operator*() {
    return *pointer;
  }
};
#endif
