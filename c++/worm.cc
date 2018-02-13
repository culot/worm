#include <glog/logging.h>
#include <memory>
#include <cmath>

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
  std::string metabolism {"Metabolism: "};
  metabolism.append(std::to_string(basalMetabolism()));
  Gfx::instance().drawstr(position().y() - 3, position().x(), metabolism);
  std::string availableNrg {"Available energy: "};
  availableNrg.append(std::to_string(availableEnergy()));
  Gfx::instance().drawstr(position().y() - 4, position().x(), availableNrg);
}

void Worm::update() {
  LOG(INFO) << "Updating worm";
  updateBrain();
  updateEnergy();
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

// Energy level varies based on two mechanisms:
//   - the worm's basal metabolism, function of the number of neurons in the brain:
//       E -= aN, with N being the number of neurons
//   - the distance d to an energy source, with:
//       E += a * exp(-b * d)
void Worm::updateEnergy() {
  float nrg = availableEnergy();
  LOG(INFO) << "Energy absorbed by worm: " << nrg;
  energy_ += std::floor(nrg);

  float metabolism = basalMetabolism();
  LOG(INFO) << "Basal metabolism consumed by worm: " << metabolism;
  energy_ -= std::floor(metabolism);
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
}

float Worm::availableEnergy() {
  float nrg {0.};
  for (const auto source : energySources_) {
    int distance = std::abs(source->x() - x());
    nrg += 5 * std::exp(-0.1 * distance);
  }
  return nrg;
}

float Worm::basalMetabolism() {
  float basalMetabolism {0.1f * brain_.size()};
  return basalMetabolism;
}

}
