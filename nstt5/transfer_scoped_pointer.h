#ifndef TSP_H_
#define TSP_H_

#include <concepts>

template<std::constructible_from<> T>
class TransferScopedPointer {
  T* pointer;

public:
  TransferScopedPointer<T>(T* p):
      pointer(p) {}

  TransferScopedPointer<T>(const TransferScopedPointer<T>&) = delete;

  TransferScopedPointer<T>& operator=(const TransferScopedPointer<T>&) = delete;

  TransferScopedPointer<T>(TransferScopedPointer<T>&& p) {
    // std::swap(pointer, p.pointer);
    // sadly, upper variant doesn't work due to compiler shenanigans
    pointer   = p.pointer;
    p.pointer = nullptr;
  }

  TransferScopedPointer<T>& operator=(TransferScopedPointer<T>&& p) {
    std::swap(pointer, p.pointer);
    return *this;
  }

  ~TransferScopedPointer<T>() {
    delete pointer;
  }

  T& operator*() {
    return *pointer;
  }
};
#endif
