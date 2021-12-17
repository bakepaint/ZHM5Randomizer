#include <memory>
#include <vector>

#include "ZHM5Randomizer/src/randomizers/Randomizer.h"
#include "ZHM5Randomizer/src/DefaultItemPool.h"
#include "ZHM5Randomizer/src/RepositoryID.h"
#include "ZHM5Randomizer/src/Scenario.h"

namespace hitman_randomizer {

class CustomNPCStrategy : public RandomizationStrategy {

public:
  CustomNPCStrategy(std::shared_ptr<hitman_randomizer::Config> config,std::shared_ptr<RandomDrawRepository> repo)
      : RandomizationStrategy(config, repo) {}
  const RepositoryID *randomize(const RepositoryID *in_out_ID) override final;
  void initialize(Scenario scen,
                  const DefaultItemPool *const default_pool) override final;

private:
  std::vector<const RepositoryID*> item_pool_;

};

} // namespace hitman_randomizer
