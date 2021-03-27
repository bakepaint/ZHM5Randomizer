#pragma once
#include <functional>
#include <vector>

#include "..\thirdparty\json.hpp"
#include "RepositoryID.h"

using json = nlohmann::json;

namespace hitman_randomizer {

class Item;

// Represents a list of items distributed in a level of a given Senario. Default
// item pools are nessecary for the generation of suitable randomized item
// pools.
class DefaultItemPool {
private:
  std::vector<RepositoryID> ids;

public:
  DefaultItemPool(json &json);

  size_t size() const;

  void get(std::vector<const RepositoryID *> &out,
           bool (Item::*fn)() const) const;

  void getPosition(std::vector<int> &out, bool (Item::*fn)() const) const;
  size_t getCount(bool (Item::*fn)() const) const;
  size_t getCount(const RepositoryID &) const;
  void getIdAt(RepositoryID &repoId, int position) const;

  void print() const;
};

}  // namespace hitman_randomizer