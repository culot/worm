#include <random>

#include "computils.h"


namespace worm {
namespace CompUtils {

int getIntBetween(int minimum, int maximum) {
  std::random_device rd;
  std::uniform_int_distribution<int> dist(minimum, maximum);
  return dist(rd);
}

}
}
