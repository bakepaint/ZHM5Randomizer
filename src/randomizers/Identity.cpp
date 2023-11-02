#include "src/randomizers/Identity.h"

#include "src/RepositoryID.h"

namespace hitman_randomizer {

const RepositoryID *
IdentityRandomization::randomize(const RepositoryID *in_out_ID) {
  return in_out_ID;
}

} // namespace hitman_randomizer
