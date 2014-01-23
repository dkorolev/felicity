#ifndef FELICITY_WATCHDOG_H
#define FELICITY_WATCHDOG_H

#include <chrono>
#include <mutex>
#include <thread>

#include "../singleton.h"
#include "../safe_ostream.h"

#include <gflags/gflags.h>

DEFINE_int32(watchdog_startup_delay_ms, 1000 * 3, "Watchdog start-up timeout.");
DEFINE_int32(watchdog_period_ms, 1000 * 2, "Watchdog max. time between events.");
DEFINE_int32(watchdog_min_sleep_ms, 50, "Minimum time between watchdog awakenings.");
DEFINE_bool(watchdog_debug, false, "Print watchdog debug messages.");

namespace felicity {

class Watchdog {
 public:
  Watchdog() : deadline_(date_now() + FLAGS_watchdog_startup_delay_ms), thread_(&Watchdog::worker, this) {
    if (FLAGS_watchdog_debug) {
      safe_cerr << "Watchdog: Debug enabled.\n";
    }
  }
  void reset() {
    std::lock_guard<std::mutex> lock(mutex_);
    deadline_ = std::max(deadline_, date_now() + FLAGS_watchdog_period_ms);
  }
 private:
  int64_t get_deadline() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return deadline_;
  }
  void worker() {
    while (true) {
      const int64_t now = date_now();
      const int64_t deadline = get_deadline();
      if (now > deadline_) {
        if (FLAGS_watchdog_debug) {
          safe_cerr << "Watchdog: Terminating.\n";
        }
        // Not clean at all.
        exit(-1);
      }
      const int64_t sleep_ms = 1 + std::max(deadline_ - now, static_cast<int64_t>(FLAGS_watchdog_min_sleep_ms));
      if (FLAGS_watchdog_debug) {
        safe_cerr << "Watchdog: Sleeping for " << sleep_ms << " ms.\n";
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
    }
  }
  mutable std::mutex mutex_;
  int64_t deadline_;
  std::thread thread_;
};

inline void watchdog_reset() {
  singleton<Watchdog>::instance().reset();
}

}  // namespace felicity

#endif
