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

bool Worm::haveSameBrightness(const EnergyPool& sources) const {
  if (sources.empty()) {
    return false;
  }
  int value = (*sources.begin())->value();
  for (const auto& source : sources) {
    if (source->value() != value) {
      return false;
    }
  }
  return true;
}

EntityPtr Worm::brightestEnergySource() const {
  if (haveSameBrightness(energySources_)) {
    return nullptr;
  }
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
  LOG(INFO) << "Drawing worm at position (" << position().y() << "," << position().x() << ")";
  Gfx::instance().drawch(position(), 'W');
  std::string energy {"Energy: "};
  energy.append(std::to_string(energy_));
  Gfx::instance().drawstr(position().y() - 2, position().x(), energy);
}

void Worm::update() {
  LOG(INFO) << "Updating worm";
  updateBrain();
  updatePosition();
}

void Worm::updateBrain() {
  if (energy_ > 0) {
    // We have some energy, let's create a neuron!
    EntityPtr energySource = brightestEnergySource();
    if (energySource == nullptr) {
      LOG(INFO) << "All sources have same brightness, doing nothing";
      return;
    }
    EntityPtr output = std::make_shared<Entity>();
    LOG(INFO) << "Brightest energy source x pos: " << std::to_string(energySource->x());
    output->direction(energySource->x() > x() ? Direction::right : Direction::left);
    createNeuron(energySource, output);
  }
}

void Worm::updatePosition() {
  Direction dir = brain_.direction();
  if (dir == Direction::right) {
    x(position().x() + 1);
    LOG(INFO) << "Worm moving to RIGHT";
  } else if (dir == Direction::left) {
    x(position().x() - 1);
    LOG(INFO) << "Worm moving to LEFT";
  } else {
    LOG(INFO) << "Worm not moving";
  }
}

void Worm::createNeuron(EntityPtr in, EntityPtr out) {
  NeuronPtr neuron = std::make_shared<Neuron>();
  neuron->input(in);
  neuron->output(out);
  brain_.addNeuron(neuron);
  --energy_;
}

}
