#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_TREASURE_HUNT_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_TREASURE_HUNT_H__

#include <queue>
#include <random>
#include <type_traits>
#include <unordered_map>

#include "ZHM5Randomizer/src/Repository.h"
#include "ZHM5Randomizer/src/Scenario.h"
#include "ZHM5Randomizer/src/Config.h"
#include "ZHM5Randomizer/src/randomizers/world/default.h"

namespace hitman_randomizer {

class DefaultItemPool;

class TreasureHuntWorldInventoryRandomization
    : public DefaultWorldRandomization {
 public:
 TreasureHuntWorldInventoryRandomization(std::shared_ptr<hitman_randomizer::Config> config,std::shared_ptr<RandomDrawRepository> repo) : DefaultWorldRandomization(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
  void initialize(Scenario scen,
                  const DefaultItemPool* const default_pool) override final;
};

}  // namespace hitman_randomizer

#endif  // __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_TREASURE_HUNT_H__