#include "src/Config.h"

#include <Windows.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "src/Console.h"
#include "src/Item.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include "toml.hpp"

namespace hitman_randomizer {

void Config::Load() {
  std::ostringstream writer;

  if (is_loaded_) {
    return;
  }

  base_directory_ =
      std::filesystem::current_path().generic_string(); //..\\HITMAN2

  auto ini_path = base_directory_ + "\\Retail\\hitman_randomizer.toml";
  toml::table tbl;

  try {
    std::ifstream t(ini_path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    tbl = toml::parse(buffer.str());
    log::info("Success reading toml.");
  } catch (const toml::parse_error &err) {
    writer << "Failed to load file: " << ini_path << ", err: " << err;
    log::info(writer.str());
    ExitProcess(0);
  } catch (...) {
    log::error("Unknown error reading toml.");
    ExitProcess(0);
  }

  world_inventory_randomizer_ =
      tbl["ZHM5Randomizer"]["worldInventoryRandomizer"].value_or("NONE");
  hero_inventory_randomizer_ =
      tbl["ZHM5Randomizer"]["heroInventoryRandomizer"].value_or("NONE");
  npc_inventory_randomizer_ =
      tbl["ZHM5Randomizer"]["npcInventoryRandomizer"].value_or("NONE");
  stash_inventory_randomizer_ =
      tbl["ZHM5Randomizer"]["stashInventoryRandomizer"].value_or("NONE");

  RNGSeed = tbl["ZHM5Randomizer"]["RNGSeed"].value_or(0);
  is_loaded_ = true;

  auto custom_world = tbl["Custom"]["World"];
  auto custom_npc = tbl["Custom"]["NPC"];

  if (toml::array *arr = custom_world["allowed_words"].as_array()) {
    for (toml::node &elem : *arr) {
      elem.visit([this](auto &&el) noexcept {
        if constexpr (toml::is_string<decltype(el)>) {
          if (el != "") {
            this->custom_world_rules_.allowed_words_.insert(*el);
          }
        }
      });
    }
  }
  if (toml::array *arr = custom_world["ignored_words"].as_array()) {
    for (toml::node &elem : *arr) {
      elem.visit([this](auto &&el) noexcept {
        if constexpr (toml::is_string<decltype(el)>) {
          if (el != "") {
            this->custom_world_rules_.ignored_words_.insert(*el);
          }
        }
      });
    }
  }

  // I KNOW I'M SO FUCKING LAZY
  if (toml::array *arr = custom_npc["allowed_words"].as_array()) {
    for (toml::node &elem : *arr) {
      elem.visit([this](auto &&el) noexcept {
        if constexpr (toml::is_string<decltype(el)>) {
          if (el != "") {
            this->custom_npc_rules_.allowed_words_.insert(*el);
          }
        }
      });
    }
  }
  if (toml::array *arr = custom_npc["ignored_words"].as_array()) {
    for (toml::node &elem : *arr) {
      elem.visit([this](auto &&el) noexcept {
        if constexpr (toml::is_string<decltype(el)>) {
          if (el != "") {
            this->custom_npc_rules_.ignored_words_.insert(*el);
          }
        }
      });
    }
  }
}

} // namespace hitman_randomizer
