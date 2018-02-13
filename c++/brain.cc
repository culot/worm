#include <glog/logging.h>

#include "brain.h"


namespace worm {

void Brain::addNeuron(NeuronPtr& neuron) {
  neurons_.push_back(neuron);
  LOG(INFO) << "Neuron added in direction "
            << (neuron->output() == Direction::right ? "[RIGHT]" : "[LEFT]");
}

int Brain::numberOfActiveNeurons() const {
  int numActive {0};
  for (const auto& neuron : neurons_) {
    if (neuron->active()) {
      ++numActive;
    }
  }
  return numActive;
}

Direction Brain::direction() const {
  int direction {0};
  for (const auto& neuron : neurons_) {
    direction += neuron->output() == Direction::right ? 1 : -1;
  }
  if (direction > 0) {
    return Direction::right;
  } else if (direction < 0) {
    return Direction::left;
  } else {
    return Direction::none;
  }
}

}
