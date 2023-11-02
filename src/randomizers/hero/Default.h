#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_HERO_DEFAULT_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_HERO_DEFAULT_H__

#include "src/randomizers/Randomizer.h"

namespace hitman_randomizer {

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
 DefaultHeroRandomization(std::shared_ptr<Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
};

} // namespace hitman_randomizer

#endif // __ZHM5RANDOMIZER_SRC_RANDOMIZERS_HERO_DEFAULT_H__
