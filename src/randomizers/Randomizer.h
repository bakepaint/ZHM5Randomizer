#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_RANDOMIZER_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_RANDOMIZER_H__

#include <queue>
#include <random>
#include <type_traits>
#include <unordered_map>

#include "src/Repository.h"
#include "src/Scenario.h"
#include "src/Config.h"
#include "src/Console.h"

namespace hitman_randomizer {

class DefaultItemPool;

class RandomizationStrategy {
 protected:
  std::shared_ptr<Config> config_;
  std::shared_ptr<RandomDrawRepository> repo_;

 public:
  RandomizationStrategy(std::shared_ptr<Config> config, std::shared_ptr<RandomDrawRepository> repo);

  // Takes Repository ID and returns a new ID according to the internal
  // Randomization strategy Item IDs that don't have a corresponding item
  // configuration in the Repository should be skipped.
  virtual const RepositoryID* randomize(const RepositoryID* in_out_ID) = 0;

  // Called on SceneLoad. This function is intended for stateful Randomization
  // strategies which might require knowledge of the next scene and/or default
  // item pool of that scene to setup their internal state in preparation for
  // item Randomization.
  virtual void initialize(Scenario, const DefaultItemPool* const);
};

class Randomizer {
 private:
  bool enabled;
  std::unique_ptr<RandomizationStrategy> strategy;

 public:
  Randomizer(RandomizationStrategy*);
  const RepositoryID* randomize(const RepositoryID* id);
  void initialize(Scenario, const DefaultItemPool* const);
  void disable();
};

}  // namespace hitman_randomizer

#endif // __ZHM5RANDOMIZER_SRC_RANDOMIZERS_RANDOMIZER_H__
