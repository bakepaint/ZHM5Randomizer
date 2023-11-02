#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_ROULETTE_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_ROULETTE_H__

#include "src/Config.h"
#include "src/DefaultItemPool.h"
#include "src/RepositoryID.h"
#include "src/randomizers/world/Default.h"
#include "src/Scenario.h"

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
