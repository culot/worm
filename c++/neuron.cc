#include <glog/logging.h>

#include "neuron.h"


namespace worm {

Neuron::Neuron() {
  LOG(INFO) << "Creating neuron";
}

Direction Neuron::output() const {
  int outputValue {0};
  for (const auto& output : output_) {
    if (output->direction() == Direction::right) {
      outputValue += 1;
    } else if (output->direction() == Direction::left) {
      outputValue -= 1;
    }
  }
  return outputValue > 0 ? Direction::right : Direction::left;
}

}
