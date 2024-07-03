#include "src/randomizers/world/default.h"

#include <algorithm>
#include <random>

#include "src/Config.h"
#include "src/Console.h"
#include "src/DefaultItemPool.h"
#include "src/Item.h"
#include "src/Offsets.h"
#include "src/RNG.h"
#include "src/Repository.h"

namespace hitman_randomizer {

const RepositoryID *
DefaultWorldRandomization::randomize(const RepositoryID *in_out_ID) {
  if (repo_->contains(*in_out_ID) && item_queue.size()) {
    const RepositoryID *id = item_queue.front();
    item_queue.pop_front();
    // log::info(
    //     "DefaultWorldRandomization: {} ({}) -> {} ({})",
    //     repo_->getItem(*in_out_ID)->string().c_str(),
    //     repo_->getItem(*in_out_ID)->GetId().c_str(),
    //     repo_->getItem(*id)->string().c_str(),
    //     repo_->getItem(*id)->GetId().c_str());
    return id;
  } else {
    if (!item_queue.size()) {
      log::info("DefaultWorldRandomization::randomize: skipped (queue exhausted) [{}]", in_out_ID->toString());
    } else {
      log::info("DefaultWorldRandomization::randomize: skipped (not in repo) [{}]", in_out_ID->toString());
    }
    return in_out_ID;
  }
}

void DefaultWorldRandomization::initialize(
    Scenario scen, const DefaultItemPool *const default_pool) {
  std::vector<const RepositoryID *> new_item_pool;

  // Key and quest items
  default_pool->get(new_item_pool, &Item::isEssential);
  unsigned int essential_item_count = new_item_pool.size();

  // Fill remaining slots with random items
  size_t default_item_pool_weapon_count =
      default_pool->getCount(&Item::isWeapon);
  int default_item_pool_size = default_pool->size();
  unsigned int random_item_count = default_item_pool_size -
                                   new_item_pool.size() -
                                   default_item_pool_weapon_count;

  repo_->getRandom(new_item_pool, random_item_count,
                 &Item::isItemAcceptableDefaultItem);

  // Shuffle item pool
  std::shuffle(new_item_pool.begin(), new_item_pool.end(),
               *RNG::inst().getEngine());

  // Insert weapons
  std::vector<const RepositoryID *> weapons;
  repo_->getRandom(weapons, default_item_pool_weapon_count, &Item::isWeapon);

  std::vector<int> weapon_slots;
  default_pool->getPosition(weapon_slots, &Item::isWeapon);
  for (int i = 0; i < weapon_slots.size(); i++) {
    new_item_pool.insert(new_item_pool.begin() + weapon_slots[i], weapons[i]);
  }

  // fill queue
  for (const auto &id : new_item_pool)
    item_queue.push_back(id);
}

}  // namespace hitman_randomizer
