#include "src/randomizers/npc/Default.h"

#include "src/Console.h"
#include "src/Item.h"
#include "src/RepositoryID.h"

namespace hitman_randomizer {

// TODO: factor this fn
const RepositoryID *
DefaultNPCRandomization::randomize(const RepositoryID *in_out_ID) {
  if (!repo_->contains(*in_out_ID)) {
    log::info(
        "DefaultNPCRandomization::randomize: skipped (not in repo) [{}]",
        in_out_ID->toString().c_str());
    return in_out_ID;
  }

  auto in_item = repo_->getItem(*in_out_ID);

  // Only NPC weapons are randomized here, return original item if item isn't a
  // weapon
  if (!in_item->isWeapon()) {
    // log::info(
    //     "DefaultNPCRandomization::randomize: skipped (not a weapon) [{}]",
    //     repo_->getItem(*in_out_ID)->string().c_str());
    return in_out_ID;
  }

  auto sameType = [&in_item](const Item &item) {
    return in_item->getType() == item.getType() &&
    (item.isItemAcceptableDefaultItem() || item.isWeapon());
  };

  auto randomized_item = repo_->getRandom(sameType);
  log::info("DefaultNPCRandomization::randomize: {} -> {} ({})",
               repo_->getItem(*in_out_ID)->string().c_str(),
               repo_->getItem(*randomized_item)->string().c_str(),
               repo_->getItem(*randomized_item)->GetId().c_str());

  return randomized_item;
}

} // namespace hitman_randomizer
