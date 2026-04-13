#include <cstddef>
#include <stdexcept>

template<typename Derived, std::size_t N = 0>
class Limited {
  static std::size_t alive;

  void increment() {
    if (alive >= N)
      throw std::runtime_error("There's too many of 'em, retreat!");
    ++alive;
  }

protected:
  Limited() { increment(); };

  Limited(const Limited&) { increment(); };

  Limited(Limited&&) { increment(); };

  Limited& operator=(const Limited&) { return *this; }

  Limited& operator=(Limited&&) { return *this; }

  ~Limited() { --alive; }
};

template<typename Derived, std::size_t N>
std::size_t Limited<Derived, N>::alive = 0;
