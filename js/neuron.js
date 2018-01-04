class Neuron {
  constructor() {
    this._active = false;
    this._energy = 0;

    // inputs + outputs links
  }

  isActive() {
    return this._active;
  }

  getEnergyLevel() {
    return this._energy;
  }
}
