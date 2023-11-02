#include "src/randomizers/npc/Hard.h"

#include "src/Console.h"
#include "src/Item.h"
#include "src/RepositoryID.h"

namespace hitman_randomizer {

const RepositoryID *
HardNPCRandomization::randomize(const RepositoryID *in_out_ID) {
  if (!repo_->contains(*in_out_ID)) {
    log::info(
        "DefaultNPCRandomization::randomize: skipped (not in repo) [{}]",
        in_out_ID->toString().c_str());
    return in_out_ID;
  }

  auto in_item = repo_->getItem(*in_out_ID);

  // flash grenades -> frag grenades
  if ((*in_out_ID == RepositoryID("042fae7b-fe9e-4a83-ac7b-5c914a71b2ca"))) {
    return repo_->getStablePointer(
        RepositoryID("3f9cf03f-b84f-4419-b831-4704cff9775c"));
  }

  // Only NPC weapons are randomized here, return original item if item isn't a
  // weapon
  if (!in_item->isWeapon()) {
    log::info(
        "DefaultNPCRandomization::randomize: skipped (not a weapon) [{}]",
        repo_->getItem(*in_out_ID)->string().c_str());
    return in_out_ID;
  }

  auto shotgun = repo_->getStablePointer(
      RepositoryID("901a3b51-51a0-4236-bdf2-23d20696b358"));
  auto rifle = repo_->getStablePointer(
      RepositoryID("d8aa6eba-0cb7-4ed4-ab99-975f2793d731"));
  auto sniper = repo_->getStablePointer(
      RepositoryID("43d15bea-d282-4a91-b625-8b7ba85c0ad5"));
  auto pistol = repo_->getStablePointer(
      RepositoryID("304fd49f-0624-4691-8506-149a4b16808e"));
  auto smg = repo_->getStablePointer(
      RepositoryID("e206ed81-0559-4289-9fec-e6a3e9d4ee7c"));

  if (in_item->isPistol()) {
    int i = rand() % 10;
    if (i == 0) {
      return pistol;
    } else {
      return smg;
    }
  }

  int i = rand() % 100;
  if (i >= 0 && i < 45) {
    return shotgun;
  } else if (i >= 45 && i < 90) {
    return rand() % 2 == 0 ? smg : rifle;
  } else {
    return sniper;
  }
}

} // namespace hitman_randomizer
