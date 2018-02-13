#pragma once

#include <memory>
#include <vector>

#include "brain.h"
#include "entity.h"
#include "drawable.h"
#include "gfx.h"


namespace worm {

using EnergyPool = std::vector<EntityPtr>;

class Worm : public Drawable {
 public:
  Worm();
  void boundaries(const Position& min, const Position& max) {minPos_ = min; maxPos_ = max;}
  void energy(int e) {energy_ = e;}
  int energy() const {return energy_;}
  void energySources(const EnergyPool& sources) {energySources_ = sources;}
  EntityPtr brightestEnergySource() const;
  void createNeuron(EntityPtr in, EntityPtr out);
  void update();
  void metabolismCoef(float alpha);
  void absorptionCoef(float beta);
  void absorptionMultiplicator(float gamma);
  void draw() override;

 private:
  Position minPos_ {Position::Label::topLeft};
  Position maxPos_ {Position::Label::bottomRight};
  int energy_ {0};
  Brain brain_;
  EnergyPool energySources_ {};
  float metabolismCoefAlpha_;
  float absorptionCoefBeta_;
  float absorptionMultiplicatorGamma_;

  void updateBrain();
  void updateEnergy();
  void updatePosition();
  bool haveSameBrightness(const EnergyPool& sources) const;
  float availableEnergy();
  float basalMetabolism();
};

using WormPtr = std::shared_ptr<Worm>;

}
