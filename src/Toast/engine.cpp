#include "engine.hpp"

#include <Interface/window.h>
#include <Renderer/renderer.h>
#include <Utils/utils.h>
#include <tracy/Tracy.hpp>

namespace toast {

void Engine::Run(int argc, char** argv) {
  Init();
  TOAST_INFO("Running Engine...");
  while (!m_window->ShouldClose()) {
    ZoneScopedN("Frame");

    event::EventSystem::PollEvents();

    Tick();
    Render();

    m_window->Tick();
    FrameMark;
  }
  Close();
}

void Engine::Init() {
  Time::Init();
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
  TOAST_INFO("Engine Uptime: {}", Time::Get().Uptime());
}
}
