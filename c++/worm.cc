#include <memory>
#include <glog/logging.h>

#include "powerhouse.h"
#include "neuron.h"
#include "worm.h"
#include "entity.h"


namespace worm {

Worm::Worm() {
  LOG(INFO) << "Creating worm";
}

EntityPtr Worm::brightestEnergySource() const {
  EntityPtr brightest;
  int maxIntensity {-1};
  for (const auto source : energySources_) {
    if (source->value() > maxIntensity) {
      maxIntensity = source->value();
      brightest = source;
    }
  }
  return brightest;
}

void Worm::draw() {
  LOG(INFO) << "Drawing worm";
}

void Worm::updateBrain() {
  if (energy_ > 0) {
    // We have some energy, let's create a neuron!
    EntityPtr energySource = brightestEnergySource();
    EntityPtr output = std::make_shared<Entity>();
    output->direction(energySource->x() > x() ? Direction::right : Direction::left);
    createNeuron(energySource, output);
  }
}

void Worm::createNeuron(EntityPtr in, EntityPtr out) {
  NeuronPtr neuron = std::make_shared<Neuron>();
  neuron->input(in);
  neuron->output(out);
  brain_.addNeuron(neuron);
}

}
