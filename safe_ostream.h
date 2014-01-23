// safe_cout, safe_cerr : Thread-safe std::cout and std::cerr respectively.
// Locks the mutex on construction, flushes the stream and releases the mutex on destruction.
// Do not support std::endl.

#ifndef FELICITY_SAFE_COUT_H
#define FELICITY_SAFE_COUT_H

#include <iostream>
#include <mutex>

namespace felicity {

struct safe_ostream {
  struct impl {
    impl(std::ostream& ostream, std::mutex& mutex) : ostream_(ostream), guard_(mutex) {}
    ~impl() {
      ostream_.flush();
    }
    template<typename T> impl& operator<<(const T& x) {
      ostream_ << x;
      return *this;
    }
    std::ostream& ostream_;
    std::lock_guard<std::mutex> guard_;
  };  
  explicit safe_ostream(std::ostream& ostream) : ostream_(ostream) {}
  template<typename T> impl& operator<<(const T& x) {
    return impl(ostream_, mutex_) << x;
  }
  std::ostream& ostream_;
  std::mutex mutex_;
};
safe_ostream safe_cout(std::cout);
safe_ostream safe_cerr(std::cerr);

}  // namespace felicity

#endif
