#include <glog/logging.h>
#include <string>

#include "computils.h"
#include "powerhouse.h"


namespace worm {

Powerhouse::Powerhouse(Position& pos, int maxIntensity) : Entity(pos), maxIntensity_(maxIntensity) {
  intensity_ = CompUtils::getIntBetween(0, maxIntensity_);
  LOG(INFO) << "Creating powerhouse with intensity [" << intensity_ << "]";
}

void Powerhouse::updateIntensity() {
  int delta = CompUtils::getIntBetween(-1, 1);
  intensity_ += delta;
  if (intensity_ < 0) {
    intensity_ = 0;
  }
  if (intensity_ > maxIntensity_) {
    intensity_ = maxIntensity_;
  }
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
