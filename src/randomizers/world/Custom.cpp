#include "src/randomizers/world/Custom.h"

#include "src/DefaultItemPool.h"
#include "src/Item.h"
#include "src/randomizers/Custom.h"
#include "src/RepositoryID.h"
#include "src/Scenario.h"

namespace hitman_randomizer {

const RepositoryID *
CustomWorldStrategy::randomize(const RepositoryID *in_out_ID) {
  return DefaultWorldRandomization::randomize(in_out_ID);
}

void CustomWorldStrategy::initialize(
    Scenario scen, const DefaultItemPool *const default_pool) {
  int default_item_pool_size = default_pool->size();
  std::vector<const RepositoryID*> item_pool;

  repo_->AllMatches(item_pool, default_pool->size(), [this](Item it) {
    return config_->custom_world_rules_.ShouldPermit(it);
  });

  if (item_pool.size() == 0) {
    log::error("CustomWorldStrategy::randomize: could not find any matching items. Game will probably crash.");
  }

  // Key and quest items
  std::vector<int> essential_items;
  default_pool->getPosition(essential_items, &Item::isEssential);

  std::vector<const RepositoryID*> new_item_pool;

  for (int i = 0; i < default_item_pool_size; i++) {
    if (std::find(essential_items.begin(), essential_items.end(), i) != essential_items.end()) {
      auto original_item = RepositoryID("00000000-0000-0000-0000-000000000000");
      default_pool->getIdAt(original_item, i);
      item_queue.push_back(repo_->getStablePointer(RepositoryID(original_item.toString())));
    } else {
      auto result = *select_randomly(item_pool.begin(), item_pool.end());
      item_queue.push_back(repo_->getStablePointer(RepositoryID(result->toString())));
    }
  }

  log::info("CustomWorldStrategy::initialize complete with {} items.", item_pool.size());
}

} // namespace hitman_randomizer