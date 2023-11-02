#ifndef __ZHM5RANDOMIZER_SRC_RANDOMIZATIONMAN_H__
#define __ZHM5RANDOMIZER_SRC_RANDOMIZATIONMAN_H__

#include "src/DefaultItemPoolRepository.h"
#include "src/Offsets.h"
#include "src/Scenario.h"
#include "src/randomizers/Randomizer.h"

using pushItem0_t = __int64(__fastcall*)(__int64*,
                                         const hitman_randomizer::RepositoryID*,
                                         __int64, void*, __int64, __int64,
                                         __int64*, void*, char*, char);
using pushItem1_t = __int64(__fastcall*)(signed __int64*,
                                         const hitman_randomizer::RepositoryID*,
                                         void*, __int64, __int64, __int64*,
                                         __int64*);

namespace hitman_randomizer {

enum class RandomizerSlot {
  WorldInventory,
  NPCInventory,
  HeroInventory,
  StashInventory
};

class RandomizationMan {
 private:
  std::unique_ptr<DefaultItemPoolRepository> default_item_pool_repo;

  static std::unique_ptr<Randomizer> world_inventory_randomizer;
  static std::unique_ptr<Randomizer> npc_item_randomizer;
  static std::unique_ptr<Randomizer> hero_inventory_randomizer;
  static std::unique_ptr<Randomizer> stash_item_randomizer;

  // This function template is called by external game code
  // Don't touch the signature of this function.
  template <std::unique_ptr<Randomizer>* rnd>
  static __int64 __fastcall pushItem0Detour(__int64* worldInventory,
                                            const RepositoryID* repoId,
                                            __int64 a3, void* a4, __int64 a5,
                                            __int64 a6, __int64* a7, void* a8,
                                            char* a9, char a10) {
    const RepositoryID* id = (*rnd)->randomize(repoId);
    const auto push =
        reinterpret_cast<pushItem0_t>(GameOffsets::instance()->getPushItem0());
    return push(worldInventory, id, a3, a4, a5, a6, a7, a8, a9, a10);
  };

  // This function template is called by external game code
  // Don't touch the signature of this function.
  template <std::unique_ptr<Randomizer>* rnd>
  static __int64 __fastcall pushItem1Detour(signed __int64* a1,
                                            const RepositoryID* repoId,
                                            void* a3, __int64 a4, __int64 a5,
                                            __int64* a6, __int64* a7) {
    const RepositoryID* id = (*rnd)->randomize(repoId);
    const auto push =
        reinterpret_cast<pushItem1_t>(GameOffsets::instance()->getPushItem1());
    return push(a1, id, a3, a4, a5, a6, a7);
  }

  void configureRandomizerCollection();

  std::shared_ptr<hitman_randomizer::Config> config_;
  std::shared_ptr<RandomDrawRepository> repo_;

 public:
  RandomizationMan(std::shared_ptr<hitman_randomizer::Config> config);

  void registerRandomizer(RandomizerSlot slot, std::unique_ptr<Randomizer> rng);
  void initializeRandomizers(const SSceneInitParameters* scen);
};

}  // namespace hitman_randomizer

#endif // __ZHM5RANDOMIZER_SRC_RANDOMIZATIONMAN_H__
