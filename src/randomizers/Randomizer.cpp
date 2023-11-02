#include "Randomizer.h"

#include <algorithm>
#include <random>

#include "src/Config.h"
#include "src/Console.h"
#include "src/DefaultItemPool.h"
#include "src/Item.h"
#include "src/Offsets.h"
#include "src/RNG.h"
#include "src/Repository.h"

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