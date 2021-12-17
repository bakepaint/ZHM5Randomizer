#include "ZHM5Randomizer/src/randomizers/world/NoItems.h"

#include <algorithm>
#include <random>

#include "ZHM5Randomizer/src/Config.h"
#include "ZHM5Randomizer/src/Console.h"
#include "ZHM5Randomizer/src/DefaultItemPool.h"
#include "ZHM5Randomizer/src/Item.h"
#include "ZHM5Randomizer/src/Offsets.h"
#include "ZHM5Randomizer/src/RNG.h"
#include "ZHM5Randomizer/src/Repository.h"

namespace hitman_randomizer {

const RepositoryID *NoItemsWorldInventoryRandomization::randomize(
    const RepositoryID *in_out_ID) {
  return DefaultWorldRandomization::randomize(in_out_ID);
}

/** Replaces all non-essential, non-quest items with coins, and all placed
 * weapons with a Hackl 9S. */
void NoItemsWorldInventoryRandomization::initialize(
    Scenario scen, const DefaultItemPool *const default_pool) {
  std::vector<int> essential_items;
  default_pool->getPosition(essential_items, &Item::isEssential);

  std::vector<int> weapon_slots;
  default_pool->getPosition(weapon_slots, &Item::isWeapon);

  std::vector<const RepositoryID *> new_item_pool;
  auto pistol = repo_->getStablePointer(
      RepositoryID("1e11fbea-cd51-48bf-8316-a050772d6135"));
  auto coin = repo_->getStablePointer(
      RepositoryID("dda002e9-02b1-4208-82a5-cf059f3c79cf"));

  for (int i = 0; i < default_pool->size(); i++) {
    if (std::find(weapon_slots.begin(), weapon_slots.end(), i) !=
        weapon_slots.end()) {
      new_item_pool.insert(new_item_pool.begin() + i, pistol);
    } else if (std::find(essential_items.begin(), essential_items.end(), i) !=
               essential_items.end()) {
      auto original_item = RepositoryID("00000000-0000-0000-0000-000000000000");
      default_pool->getIdAt(original_item, i);
      new_item_pool.insert(
          new_item_pool.begin() + i,
          repo_->getStablePointer(RepositoryID(original_item.toString())));
    } else {
      new_item_pool.insert(new_item_pool.begin() + i, coin);
    }
  }

  for (const auto &id : new_item_pool) item_queue.push(id);
}

}  // namespace hitman_randomizer