#include "src/RandomizationMan.h"

#include <filesystem>
#include <map>
#include <memory>

#include "src/Config.h"
#include "src/Console.h"
#include "src/MemoryUtils.h"
#include "src/Offsets.h"
#include "src/RNG.h"
#include "src/SSceneInitParameters.h"
#include "src/Scenario.h"
#include "src/randomizers/Randomizer.h"
#include "src/randomizers/Custom.h"
#include "src/randomizers/world/Action.h"
#include "src/randomizers/world/AllExplosives.h"
#include "src/randomizers/world/Custom.h"
#include "src/randomizers/world/Debug.h"
#include "src/randomizers/world/Default.h"
#include "src/randomizers/world/Identity.h"
#include "src/randomizers/world/Roulette.h"
#include "src/randomizers/world/TreasureHunt.h"
#include "src/randomizers/world/NoItems.h"
#include "src/randomizers/npc/Default.h"
#include "src/randomizers/npc/ChainReaction.h"
#include "src/randomizers/npc/Custom.h"
#include "src/randomizers/npc/Hard.h"
#include "src/randomizers/npc/Sleepy.h"
#include "src/randomizers/npc/Unlimited.h"
#include "src/randomizers/stash/Default.h"
#include "src/randomizers/hero/Default.h"
#include "src/randomizers/Identity.h"
#include "spdlog/spdlog.h"

#ifdef DEFAULTPOOLEXPORT
#include "DefaultPoolExport.h"
#endif

namespace hitman_randomizer {

std::unique_ptr<Randomizer> RandomizationMan::world_inventory_randomizer =
    nullptr;
std::unique_ptr<Randomizer> RandomizationMan::npc_item_randomizer = nullptr;
std::unique_ptr<Randomizer> RandomizationMan::hero_inventory_randomizer =
    nullptr;
std::unique_ptr<Randomizer> RandomizationMan::stash_item_randomizer = nullptr;

template <typename T>
RandomizationStrategy *createInstance(
    std::shared_ptr<hitman_randomizer::Config> config,
    std::shared_ptr<RandomDrawRepository> repo) {
  return new T(config, repo);
}

std::unordered_map<
    std::string,
    RandomizationStrategy *(*)(std::shared_ptr<hitman_randomizer::Config>,
                               std::shared_ptr<RandomDrawRepository>)>
    worldRandomizers{
        {"NONE", &createInstance<WorldIdentityRandomization>},
        {"DEFAULT", &createInstance<DefaultWorldRandomization>},
        {"OOPS_ALL_EXPLOSIVES",
         &createInstance<OopsAllExplosivesWorldInventoryRandomization>},
        {"TREASURE_HUNT",
         &createInstance<TreasureHuntWorldInventoryRandomization>},
        {"NO_ITEMS", &createInstance<NoItemsWorldInventoryRandomization>},
        {"ACTION", &createInstance<ActionWorldRandomization>},
        {"CUSTOM", &createInstance<CustomWorldStrategy>},
        {"ROULETTE", &createInstance<RouletteWorldStrategy>},
        {"DEBUG", &createInstance<WorldDebugRandomization>},
    };

std::unordered_map<
    std::string,
    RandomizationStrategy *(*)(std::shared_ptr<hitman_randomizer::Config>,
                               std::shared_ptr<RandomDrawRepository>)>
    npcRandomizers{
        {"NONE", &createInstance<IdentityRandomization>},
        {"DEFAULT", &createInstance<DefaultNPCRandomization>},
        {"UNLIMITED", &createInstance<UnlimitedNPCRandomization>},
        {"HARD", &createInstance<HardNPCRandomization>},
        {"SLEEPY", &createInstance<SleepyNPCRandomization>},
        {"CHAIN_REACTION", &createInstance<ChainReactionNPCRandomization>},
        {"CUSTOM", &createInstance<CustomNPCStrategy>},
    };

std::unordered_map<
    std::string,
    RandomizationStrategy *(*)(std::shared_ptr<hitman_randomizer::Config>,
                               std::shared_ptr<RandomDrawRepository>)>
    heroRandomizers{
        {"NONE", &createInstance<IdentityRandomization>},
        {"DEFAULT", &createInstance<DefaultHeroRandomization>},
    };

std::unordered_map<
    std::string,
    RandomizationStrategy *(*)(std::shared_ptr<hitman_randomizer::Config>,
                               std::shared_ptr<RandomDrawRepository>)>
    stashRandomizers{
        {"NONE", &createInstance<IdentityRandomization>},
        {"DEFAULT", &createInstance<DefaultStashRandomization>},
    };

void RandomizationMan::configureRandomizerCollection() {
  registerRandomizer(
      RandomizerSlot::WorldInventory,
      std::make_unique<Randomizer>(
          worldRandomizers[config_->world_inventory_randomizer()](config_,
                                                                  repo_)));
  registerRandomizer(
      RandomizerSlot::NPCInventory,
      std::make_unique<Randomizer>(
          npcRandomizers[config_->npc_inventory_randomizer()](config_, repo_)));
  registerRandomizer(RandomizerSlot::HeroInventory,
                     std::make_unique<Randomizer>(
                         heroRandomizers[config_->hero_inventory_randomizer()](
                             config_, repo_)));
  registerRandomizer(
      RandomizerSlot::StashInventory,
      std::make_unique<Randomizer>(
          stashRandomizers[config_->stash_inventory_randomizer()](config_,
                                                                  repo_)));
}

RandomizationMan::RandomizationMan(
    std::shared_ptr<hitman_randomizer::Config> config)
    : config_(config) {
  repo_ = std::make_shared<RandomDrawRepository>(config_);
  default_item_pool_repo = std::make_unique<DefaultItemPoolRepository>(
      config->BaseDirectory() + "\\Retail\\DefaultItemPools.json", repo_);
  hitman_randomizer::log::info("Read default item pool.");

  world_inventory_randomizer =
      std::make_unique<Randomizer>(new IdentityRandomization(config_, repo_));
  npc_item_randomizer =
      std::make_unique<Randomizer>(new IdentityRandomization(config_, repo_));
  hero_inventory_randomizer =
      std::make_unique<Randomizer>(new IdentityRandomization(config_, repo_));
  stash_item_randomizer =
      std::make_unique<Randomizer>(new IdentityRandomization(config_, repo_));
  hitman_randomizer::log::info("Created identity randomizers.");

  MemoryUtils::DetourCall(
      GameOffsets::instance()->getPushWorldInventoryDetour(),
      reinterpret_cast<const void *>(
          &pushItem1Detour<&world_inventory_randomizer>));
  MemoryUtils::DetourCall(
      GameOffsets::instance()->getPushNPCInventoryDetour(),
      reinterpret_cast<const void *>(&pushItem1Detour<&npc_item_randomizer>));
  MemoryUtils::DetourCall(GameOffsets::instance()->getPushHeroInventoryDetour(),
                          reinterpret_cast<const void *>(
                              &pushItem0Detour<&hero_inventory_randomizer>));
  MemoryUtils::DetourCall(
      GameOffsets::instance()->getPushStashInventoryDetour(),
      reinterpret_cast<const void *>(&pushItem0Detour<&stash_item_randomizer>));
  hitman_randomizer::log::info("Code detours applied.");
}

void RandomizationMan::registerRandomizer(RandomizerSlot slot,
                                          std::unique_ptr<Randomizer> rng) {
  switch (slot) {
    case RandomizerSlot::WorldInventory:
      world_inventory_randomizer = std::move(rng);
      break;
    case RandomizerSlot::NPCInventory:
      npc_item_randomizer = std::move(rng);
      break;
    case RandomizerSlot::HeroInventory:
      hero_inventory_randomizer = std::move(rng);
      break;
    case RandomizerSlot::StashInventory:
      stash_item_randomizer = std::move(rng);
      break;
  }
}

void RandomizationMan::initializeRandomizers(const SSceneInitParameters *sip) {
  auto scenario = std::hash<SSceneInitParameters>()(*sip);

  configureRandomizerCollection();

  auto seed = config_->rng_seed();
  if (seed == 0) seed = std::random_device{}();
  RNG::inst().seed(seed);

  auto default_pool = default_item_pool_repo->getDefaultPool(scenario);

  if (default_pool != nullptr || config_->world_inventory_randomizer() == "DEBUG") {
    world_inventory_randomizer->initialize(scenario, default_pool);
    npc_item_randomizer->initialize(scenario, default_pool);
    hero_inventory_randomizer->initialize(scenario, default_pool);
    stash_item_randomizer->initialize(scenario, default_pool);
  } else {
    world_inventory_randomizer->disable();
    npc_item_randomizer->disable();
    hero_inventory_randomizer->disable();
    stash_item_randomizer->disable();
  }
}

}  // namespace hitman_randomizer
