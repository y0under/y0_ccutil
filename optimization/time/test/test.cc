#include <algorithm>
#include <iostream>
#include "src/timer.h"

int main() {
  Timer timer;
  timer.start();

  for (size_t i = 0; i < 1'000'000'000; ++i);

  std::cout << timer.get_elapsed_time_ms() << std::endl;
}
