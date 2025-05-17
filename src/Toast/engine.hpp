/**
 * @file engine.hpp
 * @author Dante Harper
 * @date 17/05/25
 *
 * @brief [TODO: Brief description of the file's purpose]
 */

#pragma once

#include "Interface/window.hpp"

namespace toast {
class TOAST_API Engine {
public:
  void Run(int argc, char** argv);

protected:
  void Init();
  void Tick();
  void Render();
  void Close();
  std::unique_ptr<interface::Window> m_window;
};
}
