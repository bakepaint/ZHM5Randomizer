#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_NPC_UNLIMITED_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_NPC_UNLIMITED_H__

#include "ZHM5Randomizer/src/Config.h"
#include "ZHM5Randomizer/src/randomizers/Randomizer.h"
#include "ZHM5Randomizer/src/Repository.h"

namespace hitman_randomizer {

class UnlimitedNPCRandomization : public RandomizationStrategy {
 public:
 UnlimitedNPCRandomization(std::shared_ptr<Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
};

} // namespace hitman_randomizer

#endif // __ZHM5RANDOMIZER_SRC_RANDOMIZERS_NPC_UNLIMITED_H__
