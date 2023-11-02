#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_ALL_EXPLOSIVES_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_ALL_EXPLOSIVES_H__

#include <queue>
#include <random>
#include <type_traits>
#include <unordered_map>

#include "src/Repository.h"
#include "src/Scenario.h"
#include "src/Config.h"
#include "src/Console.h"
#include "src/DefaultItemPool.h"
#include "src/randomizers/world/default.h"

namespace hitman_randomizer {

class OopsAllExplosivesWorldInventoryRandomization
    : public DefaultWorldRandomization {
 public:
 OopsAllExplosivesWorldInventoryRandomization(std::shared_ptr<hitman_randomizer::Config> config,std::shared_ptr<RandomDrawRepository> repo) : DefaultWorldRandomization(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
  void initialize(Scenario scen,
                  const DefaultItemPool* const default_pool) override final;
};

}

#endif  // __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_ALL_EXPLOSIVES_H__