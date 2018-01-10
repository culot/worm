function getIntBetween0And(max) {
  return Math.floor(Math.random() * (max + 1));
}

class Powerhouse {
  constructor(ctx, posX, posY) {
    this._ctx = ctx;
    this._x = posX;
    this._y = posY;
    this._intensity = getIntBetween0And(9);
    this._source = new Phaser.Circle(posX, posY, 50);
  }

  intensity() {
    return this._intensity;
  }

  intensity(value) {
    this._intensity = value;
  }

  posX() {
    return this._x;
  }

  updateIntensity() {
    let sign = Math.random() > 0.5 ? 1 : -1;
    let delta = sign * getIntBetween0And(1);
    this._intensity = this._intensity + delta;

    // Let's bound the intensity between 0 and 9,
    // so that the discrete colouring scheme works properly.
    if (this._intensity > 9) {
      this._intensity = 9;
    }
    if (this._intensity < 0) {
      this._intensity = 0;
    }
  }

  update() {
    this.updateIntensity();
  }

  brightness() {
   return BrightnessLevel[this.intensity()];
  }

  draw() {
    this._ctx.debug.geom(this._source, this.brightness());
    this._ctx.debug.text("intensity: " + this.intensity(),
			 this._x - 50,
			 this._y + this._source.diameter);
  }

}
