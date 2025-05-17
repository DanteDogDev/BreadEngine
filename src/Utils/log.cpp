/// @file   Log.cpp
/// @author Xein

#include "log.hpp"

#include <spdlog/async.h>
#include <spdlog/async_logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Log::m_engineLogger;
std::shared_ptr<spdlog::logger> Log::m_clientLogger;

void Log::Init() {
  // Create and configure sinks (synchronous)
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
  console_sink->set_pattern("%^[%n] %v%$");

  std::ostringstream filename;
  auto t = std::time(nullptr);
  filename << "logs/" << std::put_time(std::localtime(&t), "%Y-%m-%d_%H-%M-%S") << ".log";
  auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_st>(filename.str(), true);
  file_sink->set_pattern("[%Y-%m-%d %T.%e] [%l] [%n] %v");

  // Create engine logger
  m_engineLogger = std::make_shared<spdlog::logger>("TOAST", spdlog::sinks_init_list { console_sink, file_sink });
  m_engineLogger->set_level(spdlog::level::trace);
  spdlog::register_logger(m_engineLogger);

  // Create client logger
  m_clientLogger = std::make_shared<spdlog::logger>("GAME", spdlog::sinks_init_list { console_sink, file_sink });
  m_clientLogger->set_level(spdlog::level::trace);
  spdlog::register_logger(m_clientLogger);
}

std::shared_ptr<spdlog::logger>& Log::GetEngine() {
  if (!m_engineLogger) { throw std::runtime_error("Logger not initialized"); }
  return m_engineLogger;
}

std::shared_ptr<spdlog::logger>& Log::GetClient() {
  if (!m_clientLogger) { throw std::runtime_error("Logger not initialized"); }
  return m_clientLogger;
}

void Log::ChangeLevel(std::shared_ptr<spdlog::logger>& logger, Level level) {
  switch (level) {
    case Level::Trace: logger->set_level(spdlog::level::trace); break;
    case Level::Info: logger->set_level(spdlog::level::info); break;
    case Level::Warning: logger->set_level(spdlog::level::warn); break;
    case Level::Error: logger->set_level(spdlog::level::err); break;
    case Level::Critical: logger->set_level(spdlog::level::critical); break;
  }
}
