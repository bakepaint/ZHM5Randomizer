#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZERS_IDENTITY_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZERS_IDENTITY_H__

#include <memory>

#include "src/randomizers/Randomizer.h"
#include "src/RepositoryID.h"

namespace hitman_randomizer {

class IdentityRandomization : public RandomizationStrategy {
 public:
  IdentityRandomization(std::shared_ptr<hitman_randomizer::Config> config,std::shared_ptr<RandomDrawRepository> repo) : RandomizationStrategy(config, repo) {}
  const RepositoryID* randomize(const RepositoryID* in_out_ID) override final;
};

}

#endif // __ZHM5RANDOMIZER_SRC_RANDOMIZERS_IDENTITY_H__
