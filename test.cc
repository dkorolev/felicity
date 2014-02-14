// This test is to confirm the code compiles.

#include "all.h"

using namespace felicity;

struct foo {
  foo() {
    safe_cout << "foo::foo();\n";
  }
};

int main(int argc, char** argv) {
  if (!google::ParseCommandLineFlags(&argc, &argv, true)) {
    return -1;
  }
  watchdog_reset();
  safe_cout << "node.js Date.now() == " << date_now() << "\n";

  singleton<foo>::instance();

  safe_cout << "Testing for_each_unique_subset().\n";
  {
    enum class is_mobile { all = 0,  mobile, desktop };
    typedef std::tuple<int, is_mobile, std::string> TEST_TUPLE_TYPE;
    TEST_TUPLE_TYPE key(0, is_mobile::mobile, "test");
    int c = 0;
    felicity::for_each_unique_subset(key, [&c](const TEST_TUPLE_TYPE& value) { ++c; });
    assert(c == 4);
  }

  {
    enum class is_mobile { all = 0,  mobile, desktop };
    typedef std::tuple<int, is_mobile, std::string> TEST_TUPLE_TYPE;
    TEST_TUPLE_TYPE key(0, is_mobile::all, "test");
    int c = 0;
    felicity::for_each_unique_subset(key, [&c](const TEST_TUPLE_TYPE& value) { ++c; });
    assert(c == 2);
  }

  {
    enum class is_mobile { all = 0,  mobile, desktop };
    typedef std::tuple<int, is_mobile, std::string> TEST_TUPLE_TYPE;
    TEST_TUPLE_TYPE key(1, is_mobile::desktop, "test");
    int c = 0;
    felicity::for_each_unique_subset(key, [&c](const TEST_TUPLE_TYPE& value) { ++c; });
    assert(c == 8);
  }
  safe_cout << "Testing for_each_unique_subset(): OK.\n";

  safe_cout << "Sleeping for three seconds.\n";
  std::this_thread::sleep_for(std::chrono::seconds(3));
  safe_cout << "Done.\n";
}
