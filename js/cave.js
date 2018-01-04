class Cave {
  constructor(ctx) {
    this._ctx = ctx;
    this._width = ctx.world.width;
  }

  width() {
    return this._width;
  }

  draw() {
    let entryHole = new Phaser.Ellipse(200, 100, 50, 100);
    let exitHole = new Phaser.Ellipse(this._width - 200, 100, 50, 100);

    this._ctx.debug.geom(entryHole, 'grey');
    this._ctx.debug.geom(exitHole, 'grey');
  }
}
