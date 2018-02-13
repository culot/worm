#pragma once

#include <memory>

#include "drawable.h"
#include "gfx.h"


namespace worm {

class Cave : public Drawable {
 public:
  Cave();
  int width() const {return width_;}
  void width(int w) {width_ = w;}
  Position leftBoundary() const;
  Position rightBoundary() const;
  void draw() const;

 private:
  int width_ {0};
};

using CavePtr = std::shared_ptr<Cave>;

}
