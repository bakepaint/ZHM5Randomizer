#pragma once
#include <queue>
#include <random>
#include <type_traits>
#include <unordered_map>

#include "ZHM5Randomizer/src/Repository.h"
#include "ZHM5Randomizer/src/Scenario.h"
#include "ZHM5Randomizer/src/Config.h"
#include "ZHM5Randomizer/src/Console.h"

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

class IdentityRandomization : public RandomizationStrategy {
 public:
  IdentityRandomization(std::shared_ptr<hitman_randomizer::Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
};

class DefaultNPCRandomization : public RandomizationStrategy {
 public:
 DefaultNPCRandomization(std::shared_ptr<hitman_randomizer::Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
};

/*
This Randomization stratgy is intended to be used to randomize 47's starting
inventory. To preserve some intentionallity the randomizer will only randomize
items within their own category as defined by the InventoryCategoryIcon key in
the item repository. Those categories are: melee, key, explosives, questitem,
tool, sniperrifle, assaultrifle, remote, QuestItem, shotgun, suitcase, pistol,
distraction, poison, Container and smg.
*/
class DefaultHeroRandomization : public RandomizationStrategy {
 public:
 DefaultHeroRandomization(std::shared_ptr<hitman_randomizer::Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
};

class DefaultStashRandomization : public RandomizationStrategy {
 public:
 DefaultStashRandomization(std::shared_ptr<hitman_randomizer::Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
};

// Randomizes all NPC weapons without type restrictions and replaces flash
// grenades with frag grenades.
class HardNPCRandomization : public RandomizationStrategy {
 public:
 HardNPCRandomization(std::shared_ptr<hitman_randomizer::Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
};

class UnlimitedNPCRandomization : public RandomizationStrategy {
 public:
 UnlimitedNPCRandomization(std::shared_ptr<hitman_randomizer::Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
};


class SleepyNPCRandomization : public RandomizationStrategy {
 public:
 SleepyNPCRandomization(std::shared_ptr<hitman_randomizer::Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
  bool exception_assigned;
};

class ChainReactionNPCRandomization : public RandomizationStrategy {
 public:
 ChainReactionNPCRandomization(std::shared_ptr<hitman_randomizer::Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
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