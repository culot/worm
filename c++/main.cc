#include <glog/logging.h>
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

  CavePtr cave;
  WormPtr w0rm;
  PowerhousePtr nrg1, nrg2;

  LOG(INFO) << "Starting...";
  try {
    cave = std::make_shared<Cave>(1000);
    Position pos;
    pos.x(100).y(100);
    nrg1 = std::make_shared<Powerhouse>(pos);
    pos.x(cave->width() - 100).y(100);
    nrg2 = std::make_shared<Powerhouse>(pos);
    w0rm = std::make_shared<Worm>();

    std::set<EntityPtr> sources = {nrg1, nrg2};
    w0rm->energySources(sources);

    w0rm->energy(5);
    cave->draw();
    w0rm->draw();
    nrg1->draw();
    nrg2->draw();

    for (;;) {
      LOG(INFO) << "Updating...";
      cave->draw();
      nrg1->update();
      nrg1->draw();
      nrg2->update();
      nrg2->draw();
      w0rm->updateBrain();
      w0rm->draw();
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

  } catch (const std::exception& e) {
    LOG(ERROR) << "Aborting due to following error: " << e.what();
    return 1;
  }

  return 0;
}
