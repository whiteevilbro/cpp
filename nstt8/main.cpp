#include "file/buffered/fbr.hpp"    // IWYU pragma: keep
#include "file/buffered/fbrw.hpp"   // IWYU pragma: keep
#include "file/buffered/fbw.hpp"    // IWYU pragma: keep
#include "file/fr.hpp"              // IWYU pragma: keep
#include "file/frw.hpp"             // IWYU pragma: keep
#include "file/fw.hpp"              // IWYU pragma: keep
#include "string/buffered/sbr.hpp"  // IWYU pragma: keep
#include "string/buffered/sbrw.hpp" // IWYU pragma: keep
#include "string/buffered/sbw.hpp"  // IWYU pragma: keep
#include "string/sr.hpp"            // IWYU pragma: keep
#include "string/srw.hpp"           // IWYU pragma: keep
#include "string/sw.hpp"            // IWYU pragma: keep

#include "gtest/gtest.h"
#include <cstdio>   // IWYU pragma: keep
#include <iostream> // IWYU pragma: keep

TEST(FIOTest, TestReader) {
  // FILE* f;
  std::string str;

  for (int i = 0; i < 2; i++) {
    // f = fopen("write.txt", "ra");
    std::string path = "write.txt";

    FileBufferedReaderWriter<>* ob = new FileBufferedReaderWriter(path, false);

    ob->read(str);
    ASSERT_EQ(str, "barfoofoo");

    delete ob;
  }
}

TEST(SIOTest, TestReader) {
  std::string str, str_s("foo");

  StringBufferedReaderWriter ob = StringBufferedReaderWriter(str_s);

  ob.read(str);
  ASSERT_EQ(str, str_s);
}

TEST(SIOTest, TestWriter) {
  std::string str("barbaz"), str_s("foo");
  {
    StringBufferedReaderWriter ob = StringBufferedReaderWriter(str_s);

    ob.write(str);
  }
  ASSERT_EQ(str, str_s);
}

// struct A {
//   int a;

//   A():
//       a(42) { std::cout << "pum" << '\n'; }
// };

// struct B: virtual A {
//   B():
//       A() {}
// };

// struct C: virtual A {
//   C():
//       A() {}
// };

// struct D: virtual B,
//           virtual C {
//   D():
//       B(), C() {}
// };

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

  // D c = D();
  // std::cout << c.a << '\n';

  // FILE* f;
  // std::string str;

  // for (int i = 0; i < 2; i++) {
  //   f                = fopen("write.txt", "ra");
  //   std::string path = "write.txt";

  //   // FileBufferedReaderWriter<>* ob = new FileBufferedReaderWriter(f);
  //   auto* ob = new FileBufferedReaderWriter(path, false);

  //   ob->read(str);
  //   std::cout << str << '\n';
  //   // ASSERT_EQ(str, "barfoofoo");

  //   delete ob;
  // }
}
