#include "src/randomizers/npc/Unlimited.h"

#include "src/Item.h"
#include "src/RepositoryID.h"

namespace hitman_randomizer {

const RepositoryID *
UnlimitedNPCRandomization::randomize(const RepositoryID *in_out_ID) {
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
    log::info(
        "DefaultNPCRandomization::randomize: skipped (not a weapon) [{}]",
        repo_->getItem(*in_out_ID)->string().c_str());
    return in_out_ID;
  }

  auto randomized_item = repo_->getRandom(&Item::isWeapon);
  return randomized_item;
}

} // namespace hitman_randomizer