#include <glog/logging.h>
#include <random>

#include "powerhouse.h"


namespace worm {

int Powerhouse::getIntBetween(int minimum, int maximum) const {
  std::random_device rd;
  std::uniform_int_distribution<int> dist(minimum, maximum);
  return dist(rd);
}

void Powerhouse::updateIntensity() {
  int delta = getIntBetween(-1, 1);
  intensity_ += delta;
}

void Powerhouse::update() {
  updateIntensity();
}

void Powerhouse::draw() {
  // TODO implement
}

}
