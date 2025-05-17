#include "engine.hpp"

#include "Interface/window.hpp"
#include "Renderer/renderer.hpp"

#include <EventSystem/eventSystem.hpp>
#include <Utils/log.hpp>

namespace toast {

void Engine::Run(int argc, char** argv) {
  Init();
  while (!m_window->ShouldClose()) {
    event::EventSystem::PollEvents();

    Tick();
    Render();

    m_window->Tick();
  }
  Close();
}

void Engine::Init() {
  Log::Init(spdlog::level::info);
  TOAST_INFO("Initializing Toast Engine...");

  m_window = std::make_unique<interface::Window>();
  m_renderer = std::make_unique<renderer::OpenGL>(interface::Window::GetProcAddr);
}

void Engine::Tick() { }

void Engine::Render() {
  TOAST_ASSERT(m_renderer, "Renderer is null");
  m_renderer->BeginFrame();
  m_renderer->RenderFrame();
  m_renderer->EndFrame();
}

void Engine::Close() {
  m_window.reset();
}
}
