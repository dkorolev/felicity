// date_now() returns the number of milliseconds elapsed since 1 January 1970 00:00:00 UTC.
// Mimics Date.now() from JavaScript/node.js.
//
// https://twitter.com/UniqueDima/status/420274974373343232

#ifndef FELICITY_DATE_NOW_H
#define FELICITY_DATE_NOW_H

#include <chrono>

namespace felicity {

int64_t date_now() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

}  // namespace felicity

#endif
