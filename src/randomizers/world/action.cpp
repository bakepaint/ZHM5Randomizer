#include "src/randomizers/world/action.h"

#include <queue>
#include <random>
#include <type_traits>
#include <unordered_map>

#include "src/Config.h"
#include "src/Console.h"
#include "src/Repository.h"
#include "src/Scenario.h"
#include "src/DefaultItemPool.h"

namespace hitman_randomizer {

const RepositoryID *ActionWorldRandomization::randomize(
    const RepositoryID *in_out_ID) {
  return DefaultWorldRandomization::randomize(in_out_ID);
}

void ActionWorldRandomization::initialize(
    Scenario scen, const DefaultItemPool *const default_pool) {
  int default_item_pool_size = default_pool->size();

  std::vector<int> weapon_slots;
  default_pool->getPosition(weapon_slots, &Item::isWeapon);

  std::vector<int> essential_items;
  default_pool->getPosition(essential_items, &Item::isEssential);

  for (int i = 0; i < default_item_pool_size; i++) {
    auto found = std::find(weapon_slots.begin(), weapon_slots.end(), i);
    if (found != weapon_slots.end()) {
      item_queue.push_back(
          repo_->getStablePointer(*repo_->getRandom(&Item::isWeapon)));
    } else if (std::find(essential_items.begin(), essential_items.end(), i) !=
               essential_items.end()) {
      auto original_item = RepositoryID("00000000-0000-0000-0000-000000000000");
      default_pool->getIdAt(original_item, i);
      item_queue.push_back(
          repo_->getStablePointer(RepositoryID(original_item.toString())));
    } else {
      int j = rand() % 100;
      if (j < 10) {
        item_queue.push_back(
            repo_->getStablePointer(*repo_->getRandom(&Item::isCoin)));
      } else if (j >= 10 && j < 50) {
        item_queue.push_back(
            repo_->getStablePointer(*repo_->getRandom(&Item::isExplosive)));
      } else if (j >= 50 && j < 90) {
        item_queue.push_back(
            repo_->getStablePointer(*repo_->getRandom(&Item::isWeapon)));
      } else {
        auto original_item =
            RepositoryID("00000000-0000-0000-0000-000000000000");
        default_pool->getIdAt(original_item, i);
        item_queue.push_back(
            repo_->getStablePointer(RepositoryID(original_item.toString())));
      }
    }
  }
}

}  // namespace hitman_randomizer