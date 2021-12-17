#include "Randomizer.h"

#include <algorithm>
#include <random>

#include "ZHM5Randomizer/src/Config.h"
#include "ZHM5Randomizer/src/Console.h"
#include "ZHM5Randomizer/src/DefaultItemPool.h"
#include "ZHM5Randomizer/src/Item.h"
#include "ZHM5Randomizer/src/Offsets.h"
#include "ZHM5Randomizer/src/RNG.h"
#include "ZHM5Randomizer/src/Repository.h"

namespace hitman_randomizer {

RandomizationStrategy::RandomizationStrategy(
    std::shared_ptr<Config> config, std::shared_ptr<RandomDrawRepository> repo)
    : repo_(repo), config_(config) {}

void RandomizationStrategy::initialize(Scenario, const DefaultItemPool *const) {}

Randomizer::Randomizer(RandomizationStrategy *strategy_) {
  strategy = std::unique_ptr<RandomizationStrategy>(strategy_);
}

const RepositoryID *Randomizer::randomize(const RepositoryID *id) {
  // printf("{}\n", id->toString().c_str());
  if (enabled)
    return strategy->randomize(id);
  else
    return id;
}

void Randomizer::initialize(Scenario scen,
                            const DefaultItemPool *const default_pool) {
  enabled = true;
  strategy->initialize(scen, default_pool);
}

void Randomizer::disable() { enabled = false; }

}  // namespace hitman_randomizer