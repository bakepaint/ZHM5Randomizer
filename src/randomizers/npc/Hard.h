#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_NPC_HARD_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_NPC_HARD_H__

#include "src/randomizers/Randomizer.h"
#include "src/Config.h"


namespace hitman_randomizer {

// Randomizes all NPC weapons without type restrictions and replaces flash
// grenades with frag grenades.
class HardNPCRandomization : public RandomizationStrategy {
 public:
 HardNPCRandomization(std::shared_ptr<Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
};

} // namespace hitman_randomizer

#endif // __ZHM5RANDOMIZER_SRC_RANDOMIZERS_NPC_HARD_H__
