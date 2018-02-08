#pragma once

#include "gfx.h"


namespace worm {

class Drawable {
 public:
   Drawable(Position pos = Position::Label::topLeft, Direction dir = Direction::none) : pos_(pos), dir_(dir) {}
   int x() const {return pos_.x();}
   void x(int posX) {pos_.x(posX);}
   int y() const {return pos_.y();}
   void y(int posY) {pos_.y(posY);}
   Direction direction() const {return dir_;}
   void direction(Direction dir) {dir_ = dir;}
   virtual void draw() {}

 private:
  Position pos_;
  Direction dir_;
};

}
