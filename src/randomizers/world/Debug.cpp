#include "src/randomizers/world/Debug.h"

#include "src/RepositoryID.h"
#include "Debug.h"

namespace hitman_randomizer {

const RepositoryID *
WorldDebugRandomization::randomize(const RepositoryID *in_out_ID) {
  log::info("\"{}\",", in_out_ID->toString().c_str());
  return in_out_ID;
}

void WorldDebugRandomization::initialize(
    Scenario scen, const DefaultItemPool *const default_pool) {
  log::info("WorldDebugRandomization\n{}: {{", scen);
}

} // namespace hitman_randomizer
