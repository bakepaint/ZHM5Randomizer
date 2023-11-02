#include "src/randomizers/hero/Default.h"

#include "src/Console.h"
#include "src/Item.h"
#include "src/RepositoryID.h"

namespace hitman_randomizer {

const RepositoryID *
DefaultHeroRandomization::randomize(const RepositoryID *in_out_ID) {
  if (!repo_->contains(*in_out_ID)) {
    log::info(
        "DefaultHeroRandomization::randomize: skipped (not in repo) [{}]",
        in_out_ID->toString().c_str());
    return in_out_ID;
  }

  auto in_item = repo_->getItem(*in_out_ID);

  auto sameType = [&in_item](const Item &item) {
    return in_item->getType() == item.getType() &&
    (item.isItemAcceptableDefaultItem() || item.isWeapon());
  };

  auto randomized_item = repo_->getRandom(sameType);
  log::info("DefaultHeroRandomization::randomize: {} -> {}",
               repo_->getItem(*in_out_ID)->string().c_str(),
               repo_->getItem(*randomized_item)->string().c_str());

  return randomized_item;
};

}  // namespace hitman_randomizer