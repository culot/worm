class Neuron {
  constructor() {
    this._active = false;
    this._energy = 0;
    this._inputs = new Set();
    this._outputs = new Set();
  }

  isActive() {
    return this._active;
  }

  getEnergyLevel() {
    return this._energy;
  }
}
