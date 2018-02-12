#pragma once

#include <memory>
#include <set>

#include "entity.h"
#include "gfx.h"


namespace worm {

class Neuron {
 public:
  Neuron();
  void input(EntityPtr& in) {input_.insert(in);}
  void output(EntityPtr& out) {output_.insert(out);}
  Direction output() const;
  bool active() const {return active_;}
  int energy() const {return energy_;}

 private:
  std::set<EntityPtr> input_ {};
  std::set<EntityPtr> output_ {};
  bool active_ {false};
  int energy_ {0};
};

using NeuronPtr = std::shared_ptr<Neuron>;

}
