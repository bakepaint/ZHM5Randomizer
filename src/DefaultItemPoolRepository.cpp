#include "DefaultItemPoolRepository.h"
#include <fstream>

#include "Console.h"

#include <memory>
#include <fstream>

namespace hitman_randomizer {

DefaultItemPoolRepository::DefaultItemPoolRepository(std::string path,std::shared_ptr<RandomDrawRepository> repo) {
  std::ifstream ifs(path);

  if (!ifs.is_open()) {
      log::info("Cannot find default item pool repository at {}", path);
  }

  json repository_json;
  ifs >> repository_json;
  ifs.close();

  for (const auto& it : repository_json.items()) {
    auto key = std::stoull(it.key(), nullptr, 0x10);
    item_pools[key] = std::make_unique<DefaultItemPool>(it.value(), repo);
  }

}

DefaultItemPool* DefaultItemPoolRepository::getDefaultPool(Scenario scen) {
  if (item_pools.count(scen)) return item_pools.at(scen).get();
  return nullptr;
}

}  // namespace hitman_randomizer
