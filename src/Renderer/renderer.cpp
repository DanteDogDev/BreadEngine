#include "renderer.hpp"

#include "Interface/window-events.hpp"
#include "Utils/file.hpp"

#include <Utils/log.hpp>

// clang-format off
#include <glad/gl.h>
#include <GL/gl.h>
// clang-format on

namespace renderer {
OpenGL::OpenGL(GLADloadfunc proc_addr) {
  TOAST_INFO("Initializing OpenGL Renderer");

  int gl_version = gladLoadGL(proc_addr);
  TOAST_ASSERT(gl_version, "Failed to load OpenGL version");

  TOAST_INFO("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(gl_version), GLAD_VERSION_MINOR(gl_version));

  m_listener.Subscribe<event::FrameBufferResize>(OpenGL::Resize);
  Init();
}

void OpenGL::Init() {
  glClearColor(0.2f, 0.3f, 0.6f, 1.0f);

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(
      [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param) {
        switch (severity) {
          case GL_DEBUG_SEVERITY_HIGH: TOAST_ERROR("OpenGL Error: {0}", message); break;
          case GL_DEBUG_SEVERITY_MEDIUM: TOAST_WARN("OpenGL Warning: {0}", message); break;
          case GL_DEBUG_SEVERITY_LOW: TOAST_INFO("OpenGL Info: {0}", message); break;
          default: TOAST_TRACE("OpenGL Trace: {0}", message); break;
        }
      },
      nullptr
  );

  // NOLINTBEGIN
  float vertices[] = {
    // NOLINT
    -0.5f, -0.5f, 0.0f,    //
    0.5f,  -0.5f, 0.0f,    //
    0.0f,  0.5f,  0.0f     //
  };
  // NOLINTEND

  glGenBuffers(1, &m_vertexBufferObj);
  glGenVertexArrays(1, &m_vertexArrayObj);

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObj);
  glBindVertexArray(m_vertexArrayObj);

  glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

  const std::string vertex_code = LoadTextFile("shaders/default.vert");
  const std::string fragment_code = LoadTextFile("shaders/default.frag");

  // RenderID program = glCreateProgram();
}

bool OpenGL::Resize(event::FrameBufferResize* event) {
  glViewport(0, 0, event->width, event->height);
  return false;
}

void OpenGL::BeginFrame() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL::RenderFrame() {
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void OpenGL::EndFrame() { }

void OpenGL::Cleanup() { }
}
