#include <glog/logging.h>

#include "brain.h"


namespace worm {

void Brain::addNeuron(NeuronPtr& neuron) {
  neurons_.push_back(neuron);
  LOG(INFO) << "Neuron added in direction "
            << (neuron->output() == Direction::right ? "[RIGHT]" : "[LEFT]");
}

void Brain::destroyAllNeurons() {
 neurons_.clear();
 LOG(INFO) << "All neurons destroyed";
}

void Brain::destroyNeuronsConnectedTo(const EntityPtr& entity) {
  if (size() == 0) {
    return;
  }
  for (auto it = neurons_.begin(); it != neurons_.end(); ) {
    if ((*it)->isConnectedTo(entity)) {
      it = neurons_.erase(it);
      LOG(INFO) << "Neuron destroyed";
    } else {
      ++it;
    }
  }
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

int Brain::numberOfNeuronsInDirection(Direction dir) const {
  int num {0};
  for (const auto& neuron : neurons_) {
    if (neuron->output() == dir) {
      ++num;
    }
  }
  return num;
}

Direction Brain::direction() const {
  int direction {0};
  for (const auto& neuron : neurons_) {
    if (neuron->output() == Direction::right) {
      ++direction;
    } else if (neuron->output() == Direction::left) {
      --direction;
    }
  }
  if (direction > 0) {
    return Direction::right;
  } else if (direction < 0) {
    return Direction::left;
  } else {
    return Direction::none;
  }
}

bool Brain::isConnectedTo(const EntityPtr& entity) const {
  bool connected {false};
  for (const auto& neuron : neurons_) {
    if (*(neuron->input()) == *entity) {
      connected = true;
    }
  }
  return connected;
}

}
