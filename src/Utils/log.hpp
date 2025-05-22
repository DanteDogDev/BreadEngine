/// @file   Log.hpp
/// @author Xein
/// @date   13/04/25
/// @brief  The logger class is in charge of displaying messages to the console

#pragma once

#include <spdlog/spdlog.h>

class TOAST_API Log {
public:
  static void Init(spdlog::level::level_enum level = spdlog::level::trace);

  enum Level : char {
    Trace = 0,
    Info,
    Warning,
    Error,
    Critical
  };

  /// @return A shared pointer to the engine log console
  [[nodiscard]]
  static std::shared_ptr<spdlog::logger>& GetEngine();

  /// @return A shared pointer to the client log console
  [[nodiscard]]
  static std::shared_ptr<spdlog::logger>& GetClient();

  /// Select the severity of the displayed messages
  /// @param logger Console to be changed
  /// @param level Least level to be logged to the console (trace means all messages will be printed)
  static void ChangeLevel(std::shared_ptr<spdlog::logger>& logger, Level level);

private:
  static std::shared_ptr<spdlog::logger> m_engineLogger;
  static std::shared_ptr<spdlog::logger> m_clientLogger;
};

#pragma region Toast Log macros

/// @def TOAST_ASSERT(condition, ...)
/// @brief Asserts a condition and logs a critical error if it fails.
/// @param condition The condition to assert.
/// @param ... The message to log if the assertion fails.
#define TOAST_ASSERT(condition, ...)           \
  {                                            \
    if (!(condition)) {                        \
      Log::GetEngine()->critical(__VA_ARGS__); \
      assert(condition);                       \
    }                                          \
  }

/// @def TOAST_ERROR(...)
/// @brief Logs an error message from the engine logger
/// @param ... The message to log.
#define TOAST_ERROR(...) Log::GetEngine()->error(__VA_ARGS__);

/// @def TOAST_WARN(...)
/// @brief Logs a warning message from the engine logger.
/// @param ... The message to log.
#define TOAST_WARN(...) Log::GetEngine()->warn(__VA_ARGS__);

/// @def TOAST_INFO(...)
/// @brief Logs an informational message from the engine logger.
/// @param ... The message to log.
#define TOAST_INFO(...) Log::GetEngine()->info(__VA_ARGS__);

/// @def TOAST_TRACE(...)
/// @brief Logs a trace (debug-level) message from the engine logger.
/// @param ... The message to log.
#define TOAST_TRACE(...) Log::GetEngine()->trace(__VA_ARGS__);

#pragma endregion

#pragma region Client Log macros

/// @def CLIENT_ASSERT(condition, ...)
/// @brief Asserts a condition and logs a critical error from the client logger if it fails.
/// @param condition The condition to assert.
/// @param ... The message to log if the assertion fails.
#define CLIENT_ASSERT(condition, ...)          \
  {                                            \
    if (!condition) {                          \
      Log::GetClient()->critical(__VA_ARGS__); \
      assert(condition);                       \
    }                                          \
  }

/// @def CLIENT_ERROR(...)
/// @brief Logs an error message from the client logger
/// @param ... The message to log.
#define CLIENT_ERROR(...) Log::GetClient()->error(__VA_ARGS__);

/// @def CLIENT_WARN(...)
/// @brief Logs a warning message from the client logger.
/// @param ... The message to log.
#define CLIENT_WARN(...) Log::GetClient()->warn(__VA_ARGS__);

/// @def CLIENT_INFO(...)
/// @brief Logs an informational message from the client logger.
/// @param ... The message to log.
#define CLIENT_INFO(...) Log::GetClient()->info(__VA_ARGS__);

/// @def CLIENT_TRACE(...)
/// @brief Logs a trace (debug-level) message from the client logger.
/// @param ... The message to log.
#define CLIENT_TRACE(...) Log::GetClient()->trace(__VA_ARGS__);

#pragma endregion

// Removes asserts on release builds
#ifdef NDEBUG
#undef TOAST_ASSERT
#undef CLIENT_ASSERT
#define TOAST_ASSERT(condition, ...) \
  { (void)condition; }
#define CLIENT_ASSERT(condition, ...) \
  { (void)condition; }
#endif

/// @brief Base exception class
///
/// This is a exception that also logs as an error its content
/// Use this instead of @c std::runtime_error for basic exception cases
class ToastException : public std::exception {
  std::string m_message;

public:
  ToastException(const std::string& message) : m_message(message) {
    TOAST_ERROR("Exception: {0}", m_message);
  }

  const char* what() const noexcept override {
    return m_message.c_str();
  }
};
