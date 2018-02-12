#include "gfx.h"


using namespace worm;

Gfx::Gfx() {
  win_ = initscr();

  if (has_colors() && start_color() == OK) {
    use_default_colors();
    init_pair(Style::Color::none, -1, -1);
    init_pair(Style::Color::black, COLOR_BLACK, -1);
    init_pair(Style::Color::cyan, COLOR_CYAN, -1);
    init_pair(Style::Color::magenta, COLOR_MAGENTA, -1);
    init_pair(Style::Color::red, COLOR_RED, -1);
    init_pair(Style::Color::yellow, COLOR_YELLOW, -1);
    init_pair(Style::Color::blue, COLOR_BLUE, -1);
    init_pair(Style::Color::cyanOnBlue, COLOR_CYAN, COLOR_BLUE);
  } else {
    // XXX Need to deal with B&W terminals
    throw std::runtime_error("Sorry, B&W terminals not supported yet");
  }

  raw();
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);

  box(win_, 0, 0);
  wrefresh(win_);

  refresh();
}

Gfx::~Gfx() {
  clear();
  endwin();
}

void Gfx::drawstr(const Position& pos, const std::string& str) {
  drawstr(pos.y(), pos.x(), str);
}

void Gfx::drawstr(int y, int x, const std::string& str) {
  mvwaddstr(win_, y, x, str.c_str());
  wrefresh(win_);
}

void Gfx::drawch(const Position& pos, const chtype ch) {
  drawch(pos.y(), pos.x(), ch);
}

void Gfx::drawch(int y, int x, const chtype ch) {
  mvwaddch(win_, y, x, ch);
  wrefresh(win_);
}

// The curses library fails to handle two concurrent threads trying to
// update the display at the same time. This creates a single point of
// entry that prevents this case from happening.
void Gfx::update() {
  mutex_.lock();
  doupdate();
  mutex_.unlock();
}
