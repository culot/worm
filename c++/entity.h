#pragma once

#include <memory>
#include <stdexcept>

#include "drawable.h"
#include "gfx.h"


namespace worm {

class Entity : public Drawable {
 public:
  Entity() : Drawable() {}
  Entity(Position& pos) : Drawable(pos) {}
  virtual int value() const {throw std::runtime_error("Must specialize value()");}
};

using EntityPtr = std::shared_ptr<Entity>;

}
