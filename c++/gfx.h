#pragma once

#include <mutex>
#include <string>
#include <ncurses.h>


namespace worm {

enum class Direction {
  none,
  left,
  right
};

struct Position {
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


struct Style {

  enum class Alignment {
    left,
    center,
    right
  };

  enum Color {
    none,
    black,
    cyan,
    magenta,
    red,
    yellow,
    blue,
    cyanOnBlue
  };

  bool bold {false};
  bool reverse {false};
  bool underline {false};
  bool highlight {false};
  bool borders {false};
  Alignment align {Alignment::left};
  Color color {Color::none};

  int cursesAttrs() const {
    int s = A_NORMAL;
    s |= bold ? A_BOLD : 0;
    s |= reverse ? A_REVERSE : 0;
    s |= underline ? A_UNDERLINE : 0;
    s |= highlight ? A_STANDOUT : 0;
    return s;
  };
};


class Gfx {
 public:
  static Gfx& instance() {static Gfx instance_; return instance_;}

  void clear();
  void drawstr(const Position& pos, const std::string& str);
  void drawstr(int y, int x, const std::string& str);
  void drawch(const Position&, const chtype ch);
  void drawch(int y, int x, const chtype ch);
  void update();

 private:
  std::mutex mutex_;
  WINDOW* win_;

  Gfx();
  ~Gfx();
  Gfx(const Gfx&) = delete;
  void operator=(const Gfx&) = delete;
};

}
