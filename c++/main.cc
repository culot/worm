#include <glog/logging.h>
#include <ncurses.h>
#include <csignal>
#include <memory>
#include <thread>
#include <chrono>
#include <set>

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

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  std::signal(SIGINT, sigHandler);
  Gfx::instance().update();

  CavePtr cave;
  WormPtr w0rm;
  PowerhousePtr nrg1, nrg2;

  LOG(INFO) << "Starting...";
  try {
    cave = std::make_shared<Cave>();
    Position pos;
    pos.x(cave->x() - 5).y(cave->y());
    nrg1 = std::make_shared<Powerhouse>(pos);
    pos.x(cave->x() + cave->width() + 5).y(cave->y());
    nrg2 = std::make_shared<Powerhouse>(pos);
    w0rm = std::make_shared<Worm>();
    w0rm->y(cave->y());
    w0rm->x((cave->x() + cave->width()) / 2);

    std::set<EntityPtr> sources = {nrg1, nrg2};
    w0rm->energySources(sources);
    w0rm->energy(5);

    int ch;
    do {
      LOG(INFO) << "Updating...";
      cave->draw();
      nrg1->update();
      nrg1->draw();
      nrg2->update();
      nrg2->draw();
      w0rm->updateBrain();
      w0rm->draw();
      Gfx::instance().update();
      std::this_thread::sleep_for(std::chrono::seconds(1));
      ch = getch();
    } while (ch != 'q');

  } catch (const std::exception& e) {
    LOG(ERROR) << "Aborting due to following error: " << e.what();
    return 1;
  }

  return 0;
}
