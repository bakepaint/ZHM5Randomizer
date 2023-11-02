#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_DEFAULT_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_DEFAULT_H__

#include <deque>
#include <queue>
#include <random>
#include <type_traits>
#include <unordered_map>

#include "src/Config.h"
#include "src/Repository.h"
#include "src/Scenario.h"
#include "src/randomizers/Randomizer.h"

namespace hitman_randomizer {

// This Randomization strategy is intended to be used to randomize world items
// during the initial load of a level. It's desiged to be as undistruptive to
// the game flow as possible.
class DefaultWorldRandomization : public RandomizationStrategy {
 protected:
  std::deque<const RepositoryID*> item_queue;

 public:
  DefaultWorldRandomization(std::shared_ptr<hitman_randomizer::Config> config,
                            std::shared_ptr<RandomDrawRepository> repo)
      : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override;
  void initialize(Scenario scen,
                  const DefaultItemPool* const default_pool) override;
};

}  // namespace hitman_randomizer

#endif  // __ZHM5RANDOMIZER_SRC_RANDOMIZERS_WORLD_DEFAULT_H__