#include <glog/logging.h>
#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <csignal>
#include <memory>
#include <thread>
#include <chrono>
#include <string>

#include "gfx.h"
#include "entity.h"
#include "cave.h"
#include "worm.h"
#include "powerhouse.h"

using namespace worm;


void sigHandler(int signal) {
  LOG(INFO) << "Received signal [" << signal << "], exiting...";
  exit(0);
}

void usage() {
  std::cerr << "Usage: worm [-h] [-w <cave_width>]" << std::endl;
  exit(1);
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  std::signal(SIGINT, sigHandler);

  int opt, caveWidth {0};
  while ((opt = getopt(argc, argv, "hw:")) != -1) {
    switch (opt) {
      case 'w':
        try {
          caveWidth = std::stoi(optarg);
        } catch (...) {
          usage();
        }
        break;
      case 'h':
      default:
        usage();
    }
  }

  CavePtr cave;
  WormPtr w0rm;
  PowerhousePtr nrg1, nrg2;

  LOG(INFO) << "Starting...";
  Gfx::instance().update();
  try {
    cave = std::make_shared<Cave>();
    if (caveWidth != 0) {
      cave->width(caveWidth);
      LOG(INFO) << "Cave width set to [" << caveWidth << "]";
    }
    Position pos;
    pos.x(cave->x() - 5).y(cave->y());
    nrg1 = std::make_shared<Powerhouse>(pos);
    pos.x(cave->x() + cave->width() + 5).y(cave->y());
    nrg2 = std::make_shared<Powerhouse>(pos);
    w0rm = std::make_shared<Worm>();
    w0rm->y(cave->y());
    w0rm->x(cave->width() / 2 + cave->x());

    EnergyPool sources = {nrg1, nrg2};
    w0rm->energySources(sources);
    w0rm->energy(5);

    int ch, tick {0};
    do {
      LOG(INFO) << "Updating...";
      Gfx::instance().clear();
      cave->draw();
      nrg1->update();
      nrg1->draw();
      nrg2->update();
      nrg2->draw();
      if (nrg1->value() > nrg2->value()) {
        LOG(INFO) << "Brighest energy source: LEFT";
      } else if (nrg1->value() < nrg2->value()) {
        LOG(INFO) << "Brighest energy source: RIGHT";
      } else {
        LOG(INFO) << "Energy sources are of equal brightness";
      }
      w0rm->update();
      w0rm->draw();
      Gfx::instance().drawstr(1,1, std::string("Ellapsed time: ").append(std::to_string(tick)));
      Gfx::instance().update();
      std::this_thread::sleep_for(std::chrono::seconds(1));
      ch = getch();
      ++tick;
    } while (ch != 'q' && w0rm->energy() > 0);

    if (w0rm->energy() <= 0) {
      LOG(INFO) << "Energy exhausted, worm dying :'(";
      LOG(INFO) << "Worm survived [" << tick << "] seconds";
    }

  } catch (const std::exception& e) {
    LOG(ERROR) << "Aborting due to following error: " << e.what();
    return 1;
  }

  return 0;
}
