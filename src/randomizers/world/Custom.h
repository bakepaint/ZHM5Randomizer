#include "src/Config.h"
#include "src/DefaultItemPool.h"
#include "src/Repository.h"
#include "src/Scenario.h"
#include "src/randomizers/world/Default.h"

namespace hitman_randomizer {

class CustomWorldStrategy : public DefaultWorldRandomization {
public:
  CustomWorldStrategy(std::shared_ptr<Config> config, std::shared_ptr<RandomDrawRepository> repo)
      : DefaultWorldRandomization(config, repo) {}
  const RepositoryID *randomize(const RepositoryID *in_out_ID) override final;
  void initialize(Scenario scen,
                  const DefaultItemPool *const default_pool) override final;
};

} // namespace hitman_randomizer