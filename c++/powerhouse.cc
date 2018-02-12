#include <glog/logging.h>
#include <random>
#include <string>

#include "powerhouse.h"


namespace worm {

Powerhouse::Powerhouse(Position& pos) : Entity(pos) {
  intensity_ = getIntBetween(0, 9);
  LOG(INFO) << "Creating powerhouse with intensity [" << intensity_ << "]";
}

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
  LOG(INFO) << "Drawing powerhouse at (x,y) (" << x() << "," << y() << ")";
  Gfx::instance().drawstr(position(), ":O:");
  std::string info {"intensity ["};
  info.append(std::to_string(value()));
  info.append("]");
  Gfx::instance().drawstr(position().y() + 2, position().x(), info);
}

}
