#include "src/randomizers/npc/Custom.h"

#include "src/DefaultItemPool.h"
#include "src/randomizers/Custom.h"
#include "src/RepositoryID.h"
#include "src/Scenario.h"

namespace hitman_randomizer {

void CustomNPCStrategy::initialize(Scenario scen,
                                   const DefaultItemPool *const default_pool) {
  repo_->AllMatches(item_pool_, default_pool->size(), [this](Item it) {
    return config_->custom_npc_rules_.ShouldPermit(it);
  });
  if (item_pool_.size() == 0) {
    log::error("CustomNPCStrategy::randomize: could not find any matching items. Game will probably crash.");
  }

  log::info("CustomNPCStrategy::initialize complete with {} items.", item_pool_.size());
}

const RepositoryID *
CustomNPCStrategy::randomize(const RepositoryID *in_out_ID) {
  if (!repo_->contains(*in_out_ID)) {
    log::info("CustomNPCStrategy::randomize: skipped (not in repo) [{}]", in_out_ID->toString());
    return in_out_ID;
  }

  auto in_item = repo_->getItem(*in_out_ID);

  if (in_item->isEssential()) {
    log::info("CustomNPCStrategy::randomize: skipped (essential) [{}]", repo_->getItem(*in_out_ID)->string());
    return in_out_ID;
  }
  auto result = *select_randomly(item_pool_.begin(), item_pool_.end());
  return result;
}

} // namespace hitman_randomizer