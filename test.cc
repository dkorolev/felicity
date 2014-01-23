// This test is to confirm the code compiles.

#include <gflags/gflags.h>

#include "all_with_gflags.h"

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
  safe_cout << "Sleeping for three seconds.\n";
  std::this_thread::sleep_for(std::chrono::seconds(3));
  safe_cout << "Done.\n";
}
