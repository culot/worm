#include <glog/logging.h>
#include <ncurses.h>

#include "cave.h"


namespace worm {

Cave::Cave() : Drawable() {
  x(20);
  y(10);
}

Position Cave::leftBoundary() const {
  Position boundary;
  boundary.x(x()).y(y());
  return boundary;
}

Position Cave::rightBoundary() const {
  Position boundary;
  boundary.x(x() + width()).y(y());
  return boundary;
}

void Cave::draw() const {
  LOG(INFO) << "Drawing cave";
  Gfx::instance().drawstr(position(), ")");
  Gfx::instance().drawstr(position().y(), position().x() + width_, "(");
  int xmin = position().x() + 1;
  int xmax = position().x() + width_;
  for (int x = xmin; x < xmax; ++x) {
    Gfx::instance().drawch(position().y(), x, '_');
  }
}

}
