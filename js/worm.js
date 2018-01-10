class Worm {
  constructor(ctx) {
    this._ctx = ctx;
    this._direction = Direction.RIGHT;
    this._x = this._ctx.world.centerX;
    this._y = 20;
    this._energy = 0;
    this._energySources = new Set();
    this._brain = new Brain();
    this._worm = this._ctx.add.sprite(this._x, this._y, 'worm');
    this._worm.anchor.setTo(0.5, 0);
  }

  energy(e) {
    this._energy = e;
  }

  energy() {
    return this._energy;
  }

  energySources(set) {
    this._energySources = set;
  }

  /*
  energyOrigin() {
    let totalEnergy = 0;
    this.__energySources.forEach(function(nrg) {
      if (nrg.posX > this._x) {
        totalEnergy += nrg.intensity();
      } else {
	totalEnergy -= nrg.intensity();
      }
    });
    return totalEnergy >= 0 ? Direction.RIGHT : Direction:LEFT;
  }
  */

  brightestEnergySource() {
    let brightest = new Powerhouse(this._ctx, 0, 0);
    brightest.intensity(-1);
    this._energySources.forEach(function(value) {
      if (value.intensity() > brightest.intensity()) {
        brightest = value;
      }
    });
    return brightest;
  }

  direction(dir) {
    this._direction = dir;
  }

  direction() {
    return this._brain.direction();
  }

  draw() {
    this._worm.x += this.direction();
  }

  updateBrain() {
    if (this._energy > 0) {
      // We have some power, let's create a neuron!
      let energySource = this.brightestEnergySource();
      let direction = energySource.posX() > this._x ? Direction.RIGHT : Direction.LEFT;
      this.createNeuron(energySource, direction);
    }
  }

  createNeuron(input, output) {
    neuron = new Neuron();
    neuron.input(input);
    neuron.output(output);
    this._brain.addNeuron(neuron);
  }
}
