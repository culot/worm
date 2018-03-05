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
  std::cerr << "Usage: worm [-h] [-w <cave_width>] [-a <metabolism_coef>] [-b <metabolism_constant>] [-g <absorption_multiplicator>] [-m max_intensity]" << std::endl;
  std::cerr << std::endl;
  std::cerr << "Energy level varies based on two mechanisms:" << std::endl;
  std::cerr << " - the worm's basal metabolism, function of the number of neurons in the brain:" << std::endl;
  std::cerr << "   E -= a * N + b, with N being the number of neurons" << std::endl;
  std::cerr << " - the distance d to an energy source of intensity i, with:" << std::endl;
  std::cerr << "   E += i * exp(-g * d)" << std::endl;
  std::cerr << "The energy sources' max intensity can be set using the -m flag" << std::endl;

  exit(1);
}

void wrongUsage(const std::string& errmsg) {
  Gfx::instance().terminate();
  std::cerr << errmsg << std::endl;
  usage();
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  std::signal(SIGINT, sigHandler);
  Gfx::instance().init(); // Needed here to get COLS value

  int caveWidth {COLS - 40};
  float alpha {.1f};
  float beta {.5f};
  float gamma {.1f};
  int maxIntensity {9};
  int opt;
  while ((opt = getopt(argc, argv, "hw:a:b:g:m:")) != -1) {
    switch (opt) {
      case 'w':
        try {
          caveWidth = std::stoi(optarg);
        } catch (...) {
          wrongUsage("Invalid cave width");
        }
        break;
      case 'a':
        try {
          alpha = std::stof(optarg);
        } catch (...) {
          wrongUsage("Invalid metabolism coefficient");
        }
        break;
      case 'b':
        try {
          beta = std::stof(optarg);
        } catch (...) {
          wrongUsage("Invalid metabolism constant");
        }
      case 'g':
        try {
          gamma = std::stof(optarg);
        } catch (...) {
          wrongUsage("Invalid absorption mulitplicator");
        }
        break;
      case 'm':
        try {
          maxIntensity = std::stoi(optarg);
        } catch (...) {
          wrongUsage("Invalid maximum intensity");
        }
        break;
      case 'h':
      default:
        Gfx::instance().terminate();
        usage();
    }
  }
  argc -= optind;
  argv += optind;

  CavePtr cave;
  WormPtr w0rm;
  PowerhousePtr nrg1, nrg2;

  LOG(INFO) << "Starting...";
  try {
    cave = std::make_shared<Cave>();
    cave->width(caveWidth);
    LOG(INFO) << "Cave created with width [" << caveWidth << "]";

    Position pos;
    pos.x(cave->x() - 5).y(cave->y());
    nrg1 = std::make_shared<Powerhouse>(pos, maxIntensity);
    pos.x(cave->x() + cave->width() + 5).y(cave->y());
    nrg2 = std::make_shared<Powerhouse>(pos, maxIntensity);

    w0rm = std::make_shared<Worm>();
    w0rm->boundaries(cave->leftBoundary(), cave->rightBoundary());
    w0rm->y(cave->y());
    w0rm->x(cave->width() / 2 + cave->x());
    w0rm->metabolismCoef(alpha);
    w0rm->metabolismConstant(beta);
    w0rm->absorptionMultiplicator(gamma);

    EnergyPool sources = {nrg1, nrg2};
    w0rm->energySources(sources);
    w0rm->energy(5.f);

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
