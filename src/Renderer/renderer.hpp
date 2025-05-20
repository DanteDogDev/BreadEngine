/**
 * @file renderer.hpp
 * @author Dante Harper
 * @date 16/05/25
 */

#pragma once

#include <Utils/event-system.h>

struct GLFWwindow;
using GLADloadfunc = void (*(*)(const char* name))();

namespace event {
struct FrameBufferResize;
}

namespace renderer {
class TOAST_API OpenGL {
public:
  OpenGL(GLADloadfunc proc_addr);
  void Init();
  static bool Resize(event::FrameBufferResize* event);
  void BeginFrame();
  void RenderFrame(/*world context*/);
  void EndFrame();
  void Cleanup();

private:
  event::Listener m_listener;
  RenderID m_vbo{};
  RenderID m_vao{};
  RenderID m_shaderProgram{};
};
}
