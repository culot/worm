#pragma once

#include <memory>


namespace worm {

class Cave {
 public:
  Cave(int width) : width_(width) {}
  int width() const {return width_;}
  void draw() const;

 private:
  int width_ {0};
};

using CavePtr = std::shared_ptr<Cave>;

}
