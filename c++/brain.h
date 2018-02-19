#pragma once

#include <vector>
#include <memory>

#include "entity.h"
#include "neuron.h"
#include "gfx.h"


namespace worm {

class Brain {
 public:
  void addNeuron(NeuronPtr& neuron);
  void destroyAllNeurons();
  void destroyNeuronsConnectedTo(const EntityPtr& entity);
  int size() const {return neurons_.size();}
  int numberOfActiveNeurons() const;
  int numberOfNeuronsInDirection(Direction dir) const;
  Direction direction() const;
  bool isConnectedTo(const EntityPtr& entity) const;

 private:
  std::vector<NeuronPtr> neurons_ {};
};

using BrainPtr = std::shared_ptr<Brain>;

}
