#pragma once

#include "entity.h"
#include "gfx.h"


namespace worm {

class Powerhouse : public Entity {
 public:
  Powerhouse(Position& pos) : Entity(pos) {intensity_ = getIntBetween(0, 9);}
  int value() const override {return intensity_;}
  void intensity(int value) {intensity_ = value;}
  void updateIntensity();
  void update();
  void draw();

 private:
  int intensity_ {0};

  int getIntBetween(int minimum, int maximum) const;
};

using PowerhousePtr = std::shared_ptr<Powerhouse>;

}
