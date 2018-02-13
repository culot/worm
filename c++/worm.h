#pragma once

#include <memory>
#include <set>

#include "brain.h"
#include "entity.h"
#include "drawable.h"
#include "gfx.h"


namespace worm {

using EnergyPool = std::vector<EntityPtr>;

class Worm : public Drawable {
 public:
  Worm();
  void energy(int e) {energy_ = e;}
  int energy() const {return energy_;}
  void energySources(const EnergyPool& sources) {energySources_ = sources;}
  EntityPtr brightestEnergySource() const;
  void createNeuron(EntityPtr in, EntityPtr out);
  void update();
  void draw() override;

 private:
  int energy_ {0};
  Brain brain_;
  EnergyPool energySources_ {};

  void updateBrain();
  void updatePosition();
  bool haveSameBrightness(const EnergyPool& sources) const;
};

using WormPtr = std::shared_ptr<Worm>;

}
