/**
 * @file time.hpp
 * @author Dante Harper
 * @date 23/05/25
 */

#pragma once

class TOAST_API Time {
  using clock_t = std::chrono::high_resolution_clock;

public:
  static void Init() {
    Get();
  }

  double Uptime() {
    auto now = clock_t::now();
    auto elapsed = now - m_startTime;
    return std::chrono::duration<double>(elapsed).count();
  }

  static Time& Get() {
    static Time instance;
    return instance;
  }

private:
  Time() {
    m_startTime = std::chrono::high_resolution_clock::now();
  }

  std::chrono::high_resolution_clock::time_point m_startTime;
};
