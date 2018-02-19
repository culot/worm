#pragma once

#include <memory>

#include "entity.h"
#include "gfx.h"


namespace worm {

class Neuron {
 public:
  Neuron();
  void input(EntityPtr& in) {input_ = in;}
  EntityPtr input() const {return input_;}
  void output(EntityPtr& out) {output_ = out;}
  Direction output() const;
  bool active() const {return active_;}
  int energy() const {return energy_;}
  bool isConnectedTo(const EntityPtr& entity) const;

 private:
  EntityPtr input_ {};
  EntityPtr output_ {};
  bool active_ {false};
  int energy_ {0};
};

using NeuronPtr = std::shared_ptr<Neuron>;

}
