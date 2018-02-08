#pragma once

#include <vector>
#include <memory>

#include "neuron.h"
#include "gfx.h"


namespace worm {

class Brain {
 public:
  void addNeuron(NeuronPtr& neuron) {neurons_.push_back(neuron);}
  int size() const {return neurons_.size();}
  int numberOfActiveNeurons() const;
  Direction direction() const;

 private:
  std::vector<NeuronPtr> neurons_ {};
};

using BrainPtr = std::shared_ptr<Brain>;

}
