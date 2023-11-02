#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_STASH_DEFAULT_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_STASH_DEFAULT_H__

#include "src/randomizers/Randomizer.h"
#include "src/RepositoryID.h"

namespace hitman_randomizer {

class DefaultStashRandomization : public RandomizationStrategy {
 public:
 DefaultStashRandomization(std::shared_ptr<hitman_randomizer::Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
};

} // namespace hitman_randomizer

#endif // __ZHM5RANDOMIZER_SRC_RANDOMIZERS_STASH_DEFAULT_H__
