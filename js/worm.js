class Worm {
  constructor(ctx) {
    this._ctx = ctx;
    this._direction = Direction.RIGHT;
    this._x = this._ctx.world.centerX;
    this._y = 20;
    this._energy = 0;
    this._worm = this._ctx.add.sprite(this._x, this._y, 'worm');
    this._worm.anchor.setTo(0.5, 0);
  }

  direction(dir) {
    this._direction = dir;
  }

  draw() {
    this._worm.x += 1 * this._direction;
  }
}
