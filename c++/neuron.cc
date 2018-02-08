#include <glog/logging.h>

#include "neuron.h"


namespace worm {

Direction Neuron::output() const {
  int outputValue {0};
  for (const auto& output : output_) {
    outputValue += output->value();
  }
  return outputValue > 0 ? Direction::right : Direction::left;
}

}
