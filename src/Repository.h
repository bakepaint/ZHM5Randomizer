#ifndef __ZHM5RANDOMIZER_SRC_REPOSITORY_H__
#define __ZHM5RANDOMIZER_SRC_REPOSITORY_H__

#include <random>
#include <unordered_map>
#include <unordered_set>

#include "..\thirdparty\json.hpp"
#include "src/Item.h"
#include "src/Config.h"
#include "src/RepositoryID.h"
#include "src/Scenario.h"

using json = nlohmann::json;

namespace hitman_randomizer {

// Repository holds information about all game items
class ItemRepository {
 private:
  std::unordered_set<RepositoryID> ids;
  std::unordered_map<RepositoryID, Item> items;

 public:
  ItemRepository(std::shared_ptr<Config> config);

  // Returns a pointer into the repository entry that matches the input ID.
  // This function is intended to be used to convert a const reference to a
  // RpoID into and id that can be passed to the game.
  const RepositoryID* getStablePointer(const RepositoryID&) const;
  const Item* getItem(const RepositoryID&) const;
  const std::unordered_set<RepositoryID>& getIds() const;
  bool contains(const RepositoryID&) const;

  protected:
  std::shared_ptr<Config> config_;
};

// Provides random access functionality to the ItemRepository
class RandomDrawRepository : public ItemRepository {
 private:
  std::mt19937* rng_engine;

  // TODO: fix memory
  std::unordered_map<void*, std::vector<const RepositoryID*>*> cache;

 public:
  RandomDrawRepository(std::shared_ptr<Config> config);

  // get random RepositoryID that satisfy the test function fn;
  // RepositoryID getRandom(bool(Item::* fn)()const) const;
  const RepositoryID* getRandom(std::function<bool(const Item& it)>);
  void getRandom(std::vector<const RepositoryID*>& item_set, unsigned int count,
                 bool (Item::*fn)() const);
  void getRandom(std::vector<const RepositoryID*>& item_set, unsigned int count,
                 std::function<bool(const Item& it)>);

void AllMatches(
    std::vector<const RepositoryID *> &item_set, unsigned int count,
    std::function<bool(const Item &)> fn);

};

}  // namespace hitman_randomizer

#endif // __ZHM5RANDOMIZER_SRC_REPOSITORY_H__
