#include "src/Console.h"

#include <Windows.h>

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include "src/Config.h"

namespace hitman_randomizer {
namespace log {

std::shared_ptr<spdlog::logger> log_;

void spawn() {
  AllocConsole();
  FILE *stream;
  freopen_s(&stream, "CONOUT$", "w", stdout);
  // auto MFCConsole = spdlog::stdout_color_mt("MFCConsole");
  auto base_directory_ =
      std::filesystem::current_path().generic_string(); //..\\HITMAN2
  auto log_path = base_directory_ + "\\Retail\\ZHM5Randomizer.log";

  try {
  log_ = spdlog::basic_logger_mt("console", log_path, true);
  log_->flush_on(spdlog::level::debug);
  log_->set_level(spdlog::level::debug);
  log_->info("Log file initialized.");

  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log init failed: " << ex.what() << std::endl;
  }
}

}  // namespace log
}  // namespace hitman_randomizer
