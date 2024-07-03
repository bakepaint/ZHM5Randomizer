#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_DEBUG_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_DEBUG_H__

#include <memory>

#include "src/randomizers/Randomizer.h"
#include "src/RepositoryID.h"

namespace hitman_randomizer {

class WorldDebugRandomization : public RandomizationStrategy {
 public:
  WorldDebugRandomization(std::shared_ptr<hitman_randomizer::Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
  void initialize(Scenario scen, const DefaultItemPool* const default_pool);
};
}

#endif // __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_DEBUG_H__
