#include "src/Item.h"

#include <unordered_map>
#include <string>

namespace hitman_randomizer {

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

bool findStringIC(const std::string &strHaystack,
                  const std::string &strNeedle) {
  auto it =
      std::search(strHaystack.begin(), strHaystack.end(), strNeedle.begin(),
                  strNeedle.end(), [](char ch1, char ch2) {
                    return std::toupper(ch1) == std::toupper(ch2);
                  });
  return (it != strHaystack.end());
}

inline ICON operator|(ICON i, ICON j) {
  using T = std::underlying_type_t<ICON>;
  return static_cast<ICON>(static_cast<T>(i) | static_cast<T>(j));
}

inline ICON operator&(ICON i, ICON j) {
  using T = std::underlying_type_t<ICON>;
  return static_cast<ICON>(static_cast<T>(i) & static_cast<T>(j));
}

std::unordered_map<std::string, CHEAT_GROUP> cheat_group_map{
    {"eCGNone", CHEAT_GROUP::NONE},
    {"eCGDevices", CHEAT_GROUP::DEVICES},
    {"eCGSniper", CHEAT_GROUP::SNIPERS},
    {"eCGAssaultRifles", CHEAT_GROUP::ASSAULTRIFLES},
    {"eCGPistols", CHEAT_GROUP::PISTOLS},
    {"eCGShotguns", CHEAT_GROUP::SHOTGUNS},
    {"eCGExotics", CHEAT_GROUP::EXOTICS},
    {"eCGSMGs", CHEAT_GROUP::SMGS}};

std::unordered_map<std::string, THROW_TYPE> throw_type_map{
    {"THROW_NONE", THROW_TYPE::NONE},
    {"THROW_PACIFY_LIGHT", THROW_TYPE::PACIFY_LIGHT},
    {"THROW_PACIFY_HEAVY", THROW_TYPE::PACIFY_HEAVY},
    {"THROW_DEADLY_LIGHT", THROW_TYPE::DEADLY_LIGHT},
    {"THROW_DEADLY_HEAVY", THROW_TYPE::DEADLY_HEAVY},
};

std::unordered_map<std::string, SILENCE_RATING> SILENCE_RATING_map{
    {"NONE", SILENCE_RATING::NONE},
    {"eSR_NotSilenced", SILENCE_RATING::NOT_SILENCED},
    {"eSR_Silenced", SILENCE_RATING::SILENCED},
    {"eSR_SuperSilenced", SILENCE_RATING::SUPER_SILENCED},
};

Item::Item() {}

Item::Item(const json& config) {
  if (!config.is_object()) throw "Item repository corrupted";

  try {
    icon = icon_map[config["InventoryCategoryIcon"].get<std::string>()];
    cheat_group = cheat_group_map[config["CheatGroup"].get<std::string>()];
    common_name = config["CommonName"].get<std::string>();
    throw_type = throw_type_map[config["ThrowType"].get<std::string>()];
    name_LOC_ = config["Name_LOC"].get<std::string>();
    title_ = config["Title"].get<std::string>();
    isCoin_ = config["IsCoin"].get<bool>();
    id_ = config["ID_"].get<std::string>();

    if (config.find("ActorConfiguration") != config.end()) {
      for (auto& x : config["ActorConfiguration"].items()) {
        if (x.key() == "SilenceRating") {
          silence_rating = SILENCE_RATING_map[x.value()];
        }
      }
    } else {
      silence_rating = SILENCE_RATING::NONE;
    }
  } catch (...) {
    // There doesn't seem to be a convinient way to tell if a key exists in the
    // json object. The repository builder should ensure that all keys are
    // present!
    throw "ItemConfig(const json& config): Some key is missing from constructor json";
  }
}

bool Item::isEssential() const { return isKey() || isQuestItem(); }

bool Item::isNotEssential() const { return !isEssential(); }

bool Item::isKey() const { return icon == ICON::KEY; }

bool Item::isQuestItem() const { return icon == ICON::QUESTITEM; }

bool Item::isWeapon() const {
  return isPistol() || isSmg() || isShotgun() || isAssaultRifle() || isSniper();
}

bool Item::isPistol() const { return icon == ICON::PISTOL; }

bool Item::isSmg() const { return icon == ICON::SMG; }

bool Item::isAssaultRifle() const { return icon == ICON::ASSAULTRIFLE; }

bool Item::isShotgun() const { return icon == ICON::SHOTGUN; }

bool Item::isSniper() const { return icon == ICON::SNIPERRIFLE; }

bool Item::isMelee() const { return icon == ICON::MELEE; }

bool Item::isExplosive() const { return icon == ICON::EXPLOSIVE; }

bool Item::isTool() const { return icon == ICON::TOOL; }

bool Item::isSuitcase() const { return icon == ICON::SUITCASE; }

bool Item::isDistraction() const { return icon == ICON::DISTRACTION; }

bool Item::isPoison() const { return icon == ICON::POISON; }

bool Item::isCoin() const { return isCoin_; }

bool Item::isGoodTreasureLocation() const {
  if (isCoin()) {
    return true;
  }
  if (isQuestItem()) {
    return false;
  }
  if (isKey()) {
    return false;
  }
  if (isEssential()) {
    return false;
  }
  if (isPoison()) {
    return false;  // poison can spawn as e.g. frogs or flowers which don't look
                   // like their actual item
    // TODO: See if there's a way to pin down what emetic rat poisons are
  }
  if (isPistol()) {
    return false;  // pistols can be locked in safes
  }
  if (isMelee()) {
    return true;
  }
  if (isTool()) {
    return true;
  }
  if (isDistraction()) {
    return true;
  }
  return false;
}

bool Item::isNotEssentialAndNotWeapon() const {
  return !isEssential() && !isWeapon();
}

const std::string& Item::string() const { return common_name; }

const ICON& Item::getType() const { return icon; }

const THROW_TYPE& Item::getThrowType() const { return throw_type; }

const SILENCE_RATING& Item::getSilenceRating() const { return silence_rating; }

void Item::print() const {
  // inefficient but it's only for debug printing so shouldn't matter
  std::string icon_name;
  for (const auto& i : icon_map)
    if (i.second == getType()) {
      icon_name = i.first;
      break;
    }
    log::info("{} ({}) : isEssential = {}", string().c_str(), icon_name.c_str(), isEssential());
}

}  // namespace hitman_randomizer