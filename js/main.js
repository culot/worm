"use strict";


let ctx = new Phaser.Game(1600, 1200, Phaser.AUTO, 'worm', {preload: preload, create: create});

// Objects requiring an update in the event loop
let cave, worm, nrg1, nrg2;


function preload() {
  ctx.load.image('background', 'img/cave.jpg');
  ctx.load.image('worm', 'img/worm.png');
}

function create() {
  ctx.stage.backgroundColor = 'black';
  let background = ctx.add.tileSprite(0, 300, 1600, 1200, 'background');

  cave = new Cave(ctx);
  worm = new Worm(ctx);
  nrg1 = new Powerhouse(ctx, 100, 100);
  nrg2 = new Powerhouse(ctx, ctx.width - 100, 100);

  cave.draw();
  worm.draw();
  nrg1.draw();
  nrg2.draw();

  ctx.time.events.loop(Phaser.Timer.SECOND, update, this);
}

function update() {
  cave.draw();
  nrg1.update();
  nrg1.draw();
  nrg2.update();
  nrg2.draw();

  // for debugging purposes
  if (nrg1.intensity() > nrg2.intensity()) {
    worm.direction(Direction.LEFT);
  } else {
    worm.direction(Direction.RIGHT);
  }
  worm.draw();
}
