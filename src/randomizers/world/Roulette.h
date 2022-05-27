#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_ROULETTE_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_ROULETTE_H__

#include "ZHM5Randomizer/src/Config.h"
#include "ZHM5Randomizer/src/DefaultItemPool.h"
#include "ZHM5Randomizer/src/RepositoryID.h"
#include "ZHM5Randomizer/src/randomizers/world/Default.h"
#include "ZHM5Randomizer/src/Scenario.h"

namespace hitman_randomizer {

class RouletteWorldStrategy : public DefaultWorldRandomization {
public:
  RouletteWorldStrategy(std::shared_ptr<Config> config, std::shared_ptr<RandomDrawRepository> repo)
      : DefaultWorldRandomization(config, repo) {}
  const RepositoryID *randomize(const RepositoryID *in_out_ID) override final;
  void initialize(Scenario scen,
                  const DefaultItemPool *const default_pool) override final;
};

}

#endif // __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_ROULETTE_H__
