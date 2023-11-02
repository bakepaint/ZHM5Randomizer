#include "src/randomizers/npc/Sleepy.h"

#include "src/Console.h"
#include "src/RepositoryID.h"

namespace hitman_randomizer {

const RepositoryID *
SleepyNPCRandomization::randomize(const RepositoryID *in_out_ID) {
  if (!repo_->contains(*in_out_ID)) {
    log::info(
        "SleepyNPCRandomization::randomize: skipped (not in repo) [{}]",
        in_out_ID->toString().c_str());
    return in_out_ID;
  }

  auto in_item = repo_->getItem(*in_out_ID);

  if (!in_item->isWeapon()) {
    return in_out_ID;
  }

  return repo_->getStablePointer(
      RepositoryID("6c3854f6-dbe0-410c-bd01-ddc35b402d0c"));
}

} // namespace hitman_randomizer
