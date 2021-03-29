#include "DefaultItemPool.h"

#include "..\thirdparty\json.hpp"
#include "Console.h"
#include "Repository.h"

namespace hitman_randomizer {

DefaultItemPool::DefaultItemPool(json &json, std::shared_ptr<RandomDrawRepository> repo) : repo_(repo) {
  for (json::iterator item = json.begin(); item != json.end(); ++item) {
    RepositoryID id(item.value().get<std::string>());

    if (repo_->contains(id))
      ids.push_back(id);
  }
}

size_t DefaultItemPool::size() const { return ids.size(); }

void DefaultItemPool::get(std::vector<const RepositoryID *> &out,
                          bool (Item::*fn)() const) const {
  for (const auto &id : ids) {
  if ((repo_->getItem(id)->*fn)())
      out.push_back(&id);
  }
}

void DefaultItemPool::getPosition(std::vector<int> &out,
                                  bool (Item::*fn)() const) const {
  int cnt = 0;
  for (const auto &id : ids) {
    if ((repo_->getItem(id)->*fn)())
      out.push_back(cnt);
    ++cnt;
  }
}

size_t DefaultItemPool::getCount(bool (Item::*fn)() const) const {
  int cnt = 0;
  for (const auto &id : ids) {
    if ((repo_->getItem(id)->*fn)())
      ++cnt;
  }
  return cnt;
}

size_t DefaultItemPool::getCount(const RepositoryID &id) const {
  return std::count(ids.begin(), ids.end(), id);
}

void DefaultItemPool::print() const {
  log::info("DefaultPool report:");
  for (const auto &id : ids) {
    repo_->getItem(id)->print();
  }
}

void DefaultItemPool::getIdAt(RepositoryID &repoId, int position) const {
  repoId = ids[position];
}

}  // namespace hitman_randomizer