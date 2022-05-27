#include "ZHM5Randomizer/src/randomizers/world/AllExplosives.h"

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

void OopsAllExplosivesWorldInventoryRandomization::initialize(
    Scenario scen, const DefaultItemPool *const default_pool) {
  std::vector<const RepositoryID *> new_item_pool;

  // Key and quest items
  default_pool->get(new_item_pool, &Item::isEssential);
  unsigned int essential_item_count = new_item_pool.size();

  size_t default_item_pool_weapon_count =
      default_pool->getCount(&Item::isWeapon);
  int default_item_pool_size = default_pool->size();
  unsigned int random_item_count = default_item_pool_size -
                                   new_item_pool.size() -
                                   default_item_pool_weapon_count;

  repo_->getRandom(new_item_pool, random_item_count,
                 [](Item it) { return it.isExplosive(); });

  // Shuffle item pool
  std::shuffle(new_item_pool.begin(), new_item_pool.end(),
               *RNG::inst().getEngine());

  // Insert weapons
  std::vector<const RepositoryID *> weapons;
  repo_->getRandom(weapons, default_item_pool_weapon_count, &Item::isExplosive);

  std::vector<int> weapon_slots;
  default_pool->getPosition(weapon_slots, &Item::isWeapon);
  for (int i = 0; i < weapon_slots.size(); i++) {
    new_item_pool.insert(new_item_pool.begin() + weapon_slots[i], weapons[i]);
  }

  // fill queue
  for (const auto &id : new_item_pool)
    item_queue.push_back(id);

  // TODO: Move this print code
  log::info("ItemPool report:");
  log::info("total size: %d(%d)", default_item_pool_size,
               static_cast<int>(new_item_pool.size()));
  log::info("\tessentials: %d", essential_item_count);
  log::info("\tweapons: %d",
               static_cast<int>(default_item_pool_weapon_count));
  log::info("\trandom: %d", random_item_count);
}

const RepositoryID *OopsAllExplosivesWorldInventoryRandomization::randomize(
    const RepositoryID *in_out_ID) {
  return DefaultWorldRandomization::randomize(in_out_ID);
}

}