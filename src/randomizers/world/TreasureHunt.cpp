#include "src/randomizers/world/TreasureHunt.h"

#include <queue>
#include <random>
#include <type_traits>
#include <unordered_map>

#include "src/Repository.h"
#include "src/Scenario.h"
#include "src/Config.h"
#include "src/Console.h"
#include "src/DefaultItemPool.h"
#include "src/randomizers/world/default.h"

namespace hitman_randomizer {

const RepositoryID *TreasureHuntWorldInventoryRandomization::randomize(
    const RepositoryID *in_out_ID) {
  return DefaultWorldRandomization::randomize(in_out_ID);
}

void TreasureHuntWorldInventoryRandomization::initialize(
    Scenario scen, const DefaultItemPool *const default_pool) {
  std::vector<const RepositoryID *> new_item_pool;

  auto gold_idol = RepositoryID("ed45f927-589d-4bad-ac1b-67e41c32e5ee");
  auto bust = RepositoryID("a6bcac8b-9772-424e-b2c4-3bdb4da0e349");
  std::vector<int> gold_idol_possible_slots;
  std::vector<int> gold_idol_final_slots;
  default_pool->getPosition(gold_idol_possible_slots,
                            &Item::isGoodTreasureLocation);
  std::vector<int> used_idxes;
  int idx;
  for (int i = 0; i < 10; i++) {
    do {
      idx = rand() % gold_idol_possible_slots.size();
    } while (std::find(used_idxes.begin(), used_idxes.end(), idx) !=
             used_idxes.end());
    gold_idol_final_slots.push_back(gold_idol_possible_slots[idx]);
    used_idxes.push_back(idx);
  }

  for (int i = 0; i < default_pool->size(); i++) {
    auto item = RepositoryID("00000000-0000-0000-0000-000000000000");
    if (std::find(gold_idol_final_slots.begin(), gold_idol_final_slots.end(),
                  i) != gold_idol_final_slots.end()) {
      item = gold_idol;
    } else {
      default_pool->getIdAt(item, i);
      if (item == gold_idol) {
        item = bust;
      }
    }
    item_queue.push_back(repo_->getStablePointer(item));
  }
}

}  // namespace hitman_randomizer