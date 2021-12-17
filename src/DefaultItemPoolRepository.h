#ifndef __ZHM5RANDOMIZER_SRC_DEFAULTITEMPOOLREPOSITORY_H__
#define __ZHM5RANDOMIZER_SRC_DEFAULTITEMPOOLREPOSITORY_H__

#include <memory>
#include <unordered_map>

#include "DefaultItemPool.h"
#include "Scenario.h"

namespace hitman_randomizer {

class DefaultItemPoolRepository {
 private:
  std::unordered_map<Scenario, std::unique_ptr<DefaultItemPool>> item_pools;

 public:
  DefaultItemPoolRepository(std::string path,std::shared_ptr<RandomDrawRepository> repo);

  DefaultItemPool* getDefaultPool(Scenario);
};

}  // namespace hitman_randomizer

#endif // __ZHM5RANDOMIZER_SRC_DEFAULTITEMPOOLREPOSITORY_H__
