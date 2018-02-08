#pragma once

#include <curses.h>


namespace worm {

enum class Direction {
  none,
  left,
  right
};

class Position {
 public:
  enum class Label {
    topLeft,
    topRight,
    bottomLeft,
    bottomRight,
    center
  };

  Position() {}
  Position(Label label) {
    switch (label) {
    case Label::topLeft:
      x_ = 0;
      y_ = 0;
      break;
    case Label::topRight:
      x_ = COLS;
      y_ = 0;
      break;
    case Label::bottomLeft:
      x_ = 0;
      y_ = LINES;
      break;
    case Label::bottomRight:
      x_ = COLS;
      y_ = LINES;
      break;
    case Label::center:
      x_ = COLS / 2;
      y_ = LINES / 2;
      break;
    }
  }

  Position& x(int posX) {x_ = posX; return *this;}
  Position& y(int posY) {y_ = posY; return *this;}
  void reset() {x_ = 0; y_ = 0;}
  bool isNull() const {return x_ == 0 && y_ == 0;}
  int x() const {return x_;}
  int y() const {return y_;}

  bool operator==(const Position& other) const {
    return y() == other.y() && x() == other.x();
  }
  bool operator!=(const Position& other) const {return !(*this == other);}

 private:
  int x_ {0};
  int y_ {0};
};

}
