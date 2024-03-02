#ifndef Y0CCUTIL_OPTIMIZATION_TIME
#define Y0CCUTIL_OPTIMIZATION_TIME

#include <chrono>

class Timer {
  private:
    std::chrono::system_clock::time_point start_;

  public:
    Timer() : start_(std::chrono::system_clock::time_point::min()) {}

    void clear() {
      start_ = std::chrono::system_clock::time_point::min();
    }

    bool is_started() const {
      return (start_.time_since_epoch() !=
               std::chrono::system_clock::duration(0));
    }

    void start() {
      start_ = std::chrono::system_clock::now();
    }

    unsigned long get_elapsed_time_ms() {
      if (!is_started()) return 0;

      std::chrono::system_clock::duration diff;
      diff = std::chrono::system_clock::now() - start_;

      return static_cast<unsigned>(std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());
    }
};
#endif
