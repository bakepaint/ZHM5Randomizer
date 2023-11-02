#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_NPC_SLEEPY_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_NPC_SLEEPY_H__

#include "src/randomizers/Randomizer.h"
#include "src/Config.h"

namespace hitman_randomizer {

class SleepyNPCRandomization : public RandomizationStrategy {
 public:
 SleepyNPCRandomization(std::shared_ptr<Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
  bool exception_assigned;
};

} // namespace hitman_randomizer

#endif // __ZHM5RANDOMIZER_SRC_RANDOMIZERS_NPC_SLEEPY_H__
