class Brain {
  constructor() {
    this._neurons = new Array();
  }

  addNeuron(neuron) {
    this._neurons.push(neuron);
  }

  numberOfNeurons() {
    return this._neurons.length;
  }

  numberOfActiveNeurons() {
    let numActive = 0;
    let num = this.numberOfNeurons();
    for (let i = 0; i < num; i++) {
      if (this._neurons[i].isActive()) {
        numActive++;
      }
    }
    return numActive;
  }

  direction() {
    let direction = 0;
    let num = this.numberOfNeurons();
    for (let i = 0; i < num; i++) {
      direction += this._neurons[i].output();
    }
    return direction;
  }
}
