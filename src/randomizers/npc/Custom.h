#include <memory>
#include <vector>

#include "src/randomizers/Randomizer.h"
#include "src/DefaultItemPool.h"
#include "src/RepositoryID.h"
#include "src/Scenario.h"

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
