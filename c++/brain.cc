#include <glog/logging.h>

#include "brain.h"


namespace worm {

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
  return direction > 0 ? Direction::right : Direction::left;
}

}
