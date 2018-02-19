#include <glog/logging.h>
#include <memory>
#include <cmath>

#include "computils.h"
#include "powerhouse.h"
#include "neuron.h"
#include "worm.h"
#include "entity.h"


namespace worm {

Worm::Worm() {
  LOG(INFO) << "Creating worm";
}

void Worm::metabolismCoef(float alpha) {
  metabolismCoefAlpha_ = alpha;
  LOG(INFO) << "Worm's metabolism coefficient alpha set to [" << alpha << "]";
}

void Worm::absorptionMultiplicator(float gamma) {
  absorptionMultiplicatorGamma_ = gamma;
  LOG(INFO) << "Worm's absorption multiplicator gamma set to [" << gamma << "]";
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

EntityPtr Worm::randomEnergySource() const {
  int energySourcesNum = energySources_.size();
  int id = CompUtils::getIntBetween(0, energySourcesNum - 1);
  return energySources_[id];
}

void Worm::draw() {
  LOG(INFO) << "Drawing worm at position (" << position().y() << "," << position().x() << ")";
  Gfx::instance().drawch(position(), '@');
  int numRight = brain_.numberOfNeuronsInDirection(Direction::right);
  for (int i = 1; i <= numRight; ++i) {
    Gfx::instance().drawch(position().y(), position().x() + i, '/');
  }
  int numLeft = brain_.numberOfNeuronsInDirection(Direction::left);
  for (int i = 1; i <= numLeft; ++i) {
    Gfx::instance().drawch(position().y(), position().x() - i, '\\');
  }

  std::string energy {"Energy: "};
  energy.append(std::to_string(energy_));
  Gfx::instance().drawstr(position().y() - 2, position().x(), energy);
  std::string neuronsno {"Nb neurons: "};
  neuronsno.append(std::to_string(brain_.size()));
  Gfx::instance().drawstr(position().y() - 3, position().x(), neuronsno);
  std::string metabolism {"Metabolism: "};
  metabolism.append(std::to_string(basalMetabolism()));
  Gfx::instance().drawstr(position().y() - 4, position().x(), metabolism);
  std::string availableNrg {"Absorbable energy: "};
  availableNrg.append(std::to_string(absorbableEnergy()));
  Gfx::instance().drawstr(position().y() - 5, position().x(), availableNrg);
}

void Worm::update() {
  LOG(INFO) << "Updating worm";
  updateBrain();
  updateEnergy();
  updatePosition();
}

void Worm::updateBrain() {
  // When worm does absorb enough energy, it stays put
  // and destroys all neurons (not needed to move anymore)
  if (absorbableEnergy() > 1.f) {
    brain_.destroyAllNeurons();
  } else {
    // When worm does not get enough stimulus from one energy source,
    // it destroys neurons linked to it
    for (const auto& source : energySources_) {
      if (absorbableEnergy(source) < 0.5f) {
        brain_.destroyNeuronsConnectedTo(source);
      }
    }
  }

  if (energy_ > 0 && absorbableEnergy() < 1.f) {
    EntityPtr input = brightestEnergySource();
    if (input != nullptr && !brain_.isConnectedTo(input)) {
      EntityPtr output = std::make_shared<Entity>();
      output->direction(input->x() > x() ? Direction::right : Direction::left);
      createNeuron(input, output);
    }
  }
}

void Worm::updateEnergy() {
  float nrg = absorbableEnergy();
  LOG(INFO) << "Energy absorbed by worm: " << nrg;
  energy_ += std::floor(nrg);

  float metabolism = basalMetabolism();
  LOG(INFO) << "Basal metabolism consumed by worm: " << metabolism;
  energy_ -= std::floor(metabolism);
}

void Worm::updatePosition() {
  if (absorbableEnergy() > 1.f) {
    return;
  }

  Direction dir = brain_.direction();
  if (dir == Direction::right) {
    x(position().x() + 1);
    LOG(INFO) << "Worm trying to move RIGHT";
  } else if (dir == Direction::left) {
    x(position().x() - 1);
    LOG(INFO) << "Worm trying to move LEFT";
  } else {
    LOG(INFO) << "Worm not moving";
  }

  if (x() > maxPos_.x()) {
    x(maxPos_.x());
    LOG(INFO) << "Worm reached cave right boundary";
  }
  if (x() < minPos_.x()) {
    x(minPos_.x());
    LOG(INFO) << "Worm reached cave left boundary";
  }
}

void Worm::createNeuron(EntityPtr in, EntityPtr out) {
  NeuronPtr neuron = std::make_shared<Neuron>();
  neuron->input(in);
  neuron->output(out);
  brain_.addNeuron(neuron);
}

float Worm::absorbableEnergy(EntityPtr source) const {
  int distance = std::abs(source->x() - x());
  float nrg = source->value() * std::exp(-1 * absorptionMultiplicatorGamma_ * distance);

  return nrg;
}

float Worm::absorbableEnergy() {
  float nrg {0.};
  for (const auto source : energySources_) {
    nrg += absorbableEnergy(source);
  }
  return nrg;
}

float Worm::basalMetabolism() {
  float basalMetabolism {metabolismCoefAlpha_ * brain_.size()};
  return basalMetabolism;
}

}
