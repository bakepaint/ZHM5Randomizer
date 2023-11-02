#ifndef __ZHM5_RANDOMIZER_SRC_ITEM_H__
#define __ZHM5_RANDOMIZER_SRC_ITEM_H__

#include <string>
#include <sstream>
#include <ostream>

#include "src/Console.h"
#include "..\thirdparty\json.hpp"
#include "spdlog/spdlog.h"

using json = nlohmann::json;

namespace hitman_randomizer {

// Stolen from https://stackoverflow.com/questions/874134/
bool hasEnding (std::string const &fullString, std::string const &ending);

bool findStringIC(const std::string &strHaystack,
                  const std::string &strNeedle);

enum class ICON {
  MELEE,
  KEY,
  EXPLOSIVE,
  QUESTITEM,
  TOOL,
  SNIPERRIFLE,
  ASSAULTRIFLE,
  REMOTE,
  SHOTGUN,
  SUITCASE,
  PISTOL,
  INVALID_CATEGORY_ICON,
  DISTRACTION,
  POISON,
  CONTAINER,
  SMG,
};

enum class CHEAT_GROUP {
  NONE,
  DEVICES,
  SNIPERS,
  ASSAULTRIFLES,
  PISTOLS,
  SHOTGUNS,
  EXOTICS,
  SMGS,
};

enum class THROW_TYPE {
  NONE,
  PACIFY_LIGHT,
  PACIFY_HEAVY,
  DEADLY_LIGHT,
  DEADLY_HEAVY,
};

enum class SILENCE_RATING {
  NONE,
  NOT_SILENCED,
  SILENCED,
  SUPER_SILENCED,
};

class Item {
public:
  Item();
  Item(const json &config);

  bool isEssential() const;
  bool isNotEssential() const;
  bool isKey() const;
  bool isQuestItem() const;
  bool isWeapon() const;
  bool isPistol() const;
  bool isSmg() const;
  bool isAssaultRifle() const;
  bool isShotgun() const;
  bool isSniper() const;
  bool isMelee() const;
  bool isExplosive() const;
  bool isTool() const;
  bool isSuitcase() const;
  bool isDistraction() const;
  bool isNotEssentialAndNotWeapon() const;
  bool isPoison() const;
  bool isGoodTreasureLocation() const;
  bool isCoin() const;
  bool isDecorativeMeleeItem() const {
    return (!isWeapon()) && name_LOC().rfind("ui_prop_melee", 0) == 0;
  }
  bool isItemAcceptableDefaultItem() const {
    if (!isNotEssentialAndNotWeapon()) {
      return false;
    }
    // "MK 2" branded items
    if (hasEnding(title(), "S2")) {
      return false;
    }

    // if (isTool()) {
    //   // Default crowbar
    //   if (GetId() == "01ed6d15-e26e-4362-b1a6-363684a7d0fd") {
    //     return true;
    //   }
    //   // Default screwdriver
    //   if (GetId() == "12cb6b51-a6dd-4bf5-9653-0ab727820cac") {
    //     return true;
    //   }
    //   // Default wrench
    //   if (GetId() == "6adddf7e-6879-4d51-a7e2-6a25ffdca6ae") {
    //     return true;
    //   }
    //   // Pristine lockpick
    //   if (GetId() == "2b2bdde8-19d2-40de-a2fa-f2ddf225d040") {
    //     return true;
    //   }
    //   // Keycard hacker
    //   if (GetId() == "b970a355-4296-4acc-9ec9-584e69a79eed") {
    //     return true;
    //   }
    //   return false;
    // }
    return true;
  }

  const std::string& GetId() const {
    return id_;
  }

  const std::string IconString() const {
    std::string icon_name;
    for (const auto &i : icon_map) {
      if (i.second == getType()) {
        return i.first;
        break;
      }
    }
    log::error(
        "Could not find matching icon for type {}", getType());
    throw "Could not find matching icon";
  }

  const std::string &title() const { return title_; }
  const std::string &string() const;
  const std::string &name_LOC() const { return name_LOC_; }
  const ICON &getType() const;
  const THROW_TYPE &getThrowType() const;
  const SILENCE_RATING &getSilenceRating() const;

  void print() const;

  const std::string toString() const {
        std::stringstream fmt;
    fmt << "Item{" << GetId() << ", " << string() << ", " << IconString() << "}";
    return fmt.str();
  }

  std::unordered_map<std::string, ICON> icon_map{
      {"melee", ICON::MELEE},
      {"key", ICON::KEY},
      {"explosives", ICON::EXPLOSIVE},
      {"questitem", ICON::QUESTITEM},
      {"tool", ICON::TOOL},
      {"sniperrifle", ICON::SNIPERRIFLE},
      {"assaultrifle", ICON::ASSAULTRIFLE},
      {"remote", ICON::REMOTE},
      {"QuestItem", ICON::QUESTITEM},
      {"shotgun", ICON::SHOTGUN},
      {"suitcase", ICON::SUITCASE},
      {"pistol", ICON::PISTOL},
      {"INVALID_CATEGORY_ICON", ICON::INVALID_CATEGORY_ICON},
      {"distraction", ICON::DISTRACTION},
      {"poison", ICON::POISON},
      {"Container", ICON::CONTAINER},
      {"smg", ICON::SMG},
  };
  
  private:

    ICON icon;
    CHEAT_GROUP cheat_group;
    THROW_TYPE throw_type;
    SILENCE_RATING silence_rating;

    std::string common_name;
    std::string title_;
    std::string name_LOC_;
    bool isCoin_;
    std::string id_;

};


} // namespace hitman_randomizer

#endif  // __ZHM5_RANDOMIZER_SRC_ITEM_H__