#pragma once

#include <memory>

#include "drawable.h"
#include "gfx.h"


namespace worm {

class Entity : public Drawable {
 public:
  Entity() : Drawable() {}
  Entity(Position& pos) : Drawable(pos) {}
  virtual int value() const {return 0;}
};

using EntityPtr = std::shared_ptr<Entity>;

}
