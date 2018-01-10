class Neuron {
  constructor() {
    this._active = false;
    this._energy = 0;
    this._inputs = new Set();
    this._outputs = new Set();
  }

  input(input) {
    this._inputs.add(input);
  }

  output(out) {
    this._outputs.add(out);
  }

  output() {
    let outputValue = 0;
    this._outputs.forEach(function(out) {
      outputValue += out;
    });
    return outputValue;
  }

  isActive() {
    return this._active;
  }

  getEnergyLevel() {
    return this._energy;
  }
}
