class Worm {
  constructor(ctx) {
    this._ctx = ctx;
    this._direction = Direction.RIGHT;
    this._x = this._ctx.world.centerX;
    this._y = 20;
    this._energy = 0;
  }

  draw() {
    let worm = this._ctx.add.sprite(this._x, this._y, 'worm');
  }
}
