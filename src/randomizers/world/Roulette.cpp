#include "src/randomizers/world/Roulette.h"

#include <string>
#include <vector>
#include <unordered_set>

#include "src/DefaultItemPool.h"
#include "src/Item.h"
#include "src/RepositoryID.h"
#include "src/Scenario.h"
#include "src/randomizers/Custom.h"


namespace hitman_randomizer {

const RepositoryID *RouletteWorldStrategy::randomize(
    const RepositoryID *in_out_ID) {
  return DefaultWorldRandomization::randomize(in_out_ID);
}

void RouletteWorldStrategy::initialize(
    Scenario scen, const DefaultItemPool *const default_pool) {
  int default_item_pool_size = default_pool->size();
  std::vector<const RepositoryID *> item_pool;

  std::unordered_set<std::string> required_items;

  for (int i = 0; i < default_pool->size(); i++) {
    auto item = RepositoryID("00000000-0000-0000-0000-000000000000");
    default_pool->getIdAt(item, i);
    required_items.insert(item.toString());
  }

  log::info("RouletteWorldStrategy:: {} unique items out of {} default items.", required_items.size(), default_item_pool_size);

  // What I think we want to do is first fill the queue with random items
  // And then place all the items for the default pool over random indexes
  // in the randomized queue
  repo_->AllMatches(item_pool, default_pool->size(), [this, &required_items](Item it){
    return it.isItemAcceptableDefaultItem();
  });

  for (int i = 0; i < default_item_pool_size; i++) {
    auto result = *select_randomly(item_pool.begin(), item_pool.end());
    item_queue.push_back(
        repo_->getStablePointer(RepositoryID(result->toString())));
  }

  std::unordered_set<int> used_indexes;
  for (auto iter = required_items.begin(); iter != required_items.end(); ++iter) {
    bool valid = false;
    int replaced_idx = -1;
    do {
      replaced_idx = rand() % default_item_pool_size;
      auto search = used_indexes.find(replaced_idx);
      if (search == used_indexes.end()) {
        used_indexes.insert(replaced_idx);
        valid = true;
      }
    } while (!valid);
    item_queue[replaced_idx] = new RepositoryID(*iter);
    log::info("RouletteWorldStrategy:: Replacing item at index {} with required item {}.", replaced_idx, *iter);
  }

  log::info("RouletteWorldStrategy::initialize complete with {} items.",
            item_pool.size());
}

}  // namespace hitman_randomizer