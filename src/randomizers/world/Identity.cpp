#include "ZHM5Randomizer/src/randomizers/world/Identity.h"

#include "ZHM5Randomizer/src/RepositoryID.h"

namespace hitman_randomizer {

const RepositoryID *
WorldIdentityRandomization::randomize(const RepositoryID *in_out_ID) {
  log::info("WorldIdentityRandomization {}", in_out_ID->toString().c_str());
  return in_out_ID;
}

} // namespace hitman_randomizer
