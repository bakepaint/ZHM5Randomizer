#include "src/randomizers/npc/ChainReaction.h"

#include "src/RepositoryID.h"
#include "src/Console.h"

namespace hitman_randomizer {

const RepositoryID *
ChainReactionNPCRandomization::randomize(const RepositoryID *in_out_ID) {
  auto shotgun1 = repo_->getStablePointer(
      RepositoryID("0af419f5-e6d3-488d-b133-6ce0964b0770"));
  auto shotgun2 = repo_->getStablePointer(
      RepositoryID("d5728a0f-fe8d-4e2d-9350-03cf4243c98e"));
  auto rifle1 = repo_->getStablePointer(
      RepositoryID("6e4afb04-417e-4cfc-aaa2-43f3ecca9037"));
  auto rifle2 = repo_->getStablePointer(
      RepositoryID("e206ed81-0559-4289-9fec-e6a3e9d4ee7c"));
  auto sniper = repo_->getStablePointer(
      RepositoryID("370580fc-7fcf-47f8-b994-cebd279f69f9"));

  if (!repo_->contains(*in_out_ID)) {
    log::info(
        "ChainReactionNPCRandomization::randomize: skipped (not in repo) [{}]",
        in_out_ID->toString().c_str());
    return in_out_ID;
  }

  auto in_item = repo_->getItem(*in_out_ID);

  if (!in_item->isWeapon()) {
    return in_out_ID;
  }

  // flash grenades -> octane booster
  if ((*in_out_ID == RepositoryID("042fae7b-fe9e-4a83-ac7b-5c914a71b2ca")))
    return repo_->getStablePointer(
        RepositoryID("c82fefa7-febe-46c8-90ec-c945fbef0cb4"));

  int i = rand() % 10;
  if (i >= 0 && i < 4) {
    // Cure coin
    return repo_->getStablePointer(
        RepositoryID("6c3854f6-dbe0-410c-bd01-ddc35b402d0c"));
  } else if (i >= 4 && i < 8) {
    // Octane booster
    return repo_->getStablePointer(
        RepositoryID("c82fefa7-febe-46c8-90ec-c945fbef0cb4"));
  } else {
    int i = rand() % 100;
    if (i >= 0 && i < 40) {
      return rand() % 2 == 0 ? shotgun1 : shotgun2;
    } else if (i >= 40 && i < 80) {
      return rand() % 2 == 0 ? rifle1 : rifle2;
    } else {
      return sniper;
    }
  }
}

} // namespace hitman_randomizer