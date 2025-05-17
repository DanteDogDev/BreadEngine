#include "engine.hpp"

#include <Interface/window.hpp>
#include <Utils/log.hpp>
#include <EventSystem/eventSystem.hpp>

namespace toast {
  void Engine::Run(int argc, char** argv) {
    Init();
    while (!m_window->ShouldClose()) {
      event::EventSystem::PollEvents();
      m_window->HandleInput();

      Tick();
      Render();

      m_window->Tick();
    }
    Close();
  }
  void Engine::Init() {
    Log::Init();
    TOAST_INFO("Initializing Toast Engine...");

    m_window = std::make_unique<interface::Window>();
  }

  void Engine::Tick() {
  }
  void Engine::Render() {
  }
  void Engine::Close() {
    m_window.release();
  }
}
