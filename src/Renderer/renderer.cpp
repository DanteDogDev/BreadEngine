#include "renderer.hpp"

#include "shader.hpp"

#include <Interface/window.h>
#include <Utils/file.h>
#include <Utils/log.h>

// clang-format off
#include <glad/gl.h>
#include <GL/gl.h>
// clang-format on

namespace renderer {
OpenGL::OpenGL(GLADloadfunc proc_addr) {
  TOAST_INFO("Initializing OpenGL Renderer...");

  int gl_version = gladLoadGL(proc_addr);
  TOAST_ASSERT(gl_version, "Failed to load OpenGL version");

  TOAST_INFO("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(gl_version), GLAD_VERSION_MINOR(gl_version));

  m_listener.Subscribe<event::FrameBufferResize>(OpenGL::Resize);
  Init();
}

void OpenGL::Init() {
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
  glClearColor(0.2f, 0.3f, 0.6f, 1.0f);

  // NOLINTBEGIN
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,    // bottom-left  // 0
    0.5f,  -0.5f, 0.0f,    // bottom-right // 1
    0.5f,  0.5f,  0.0f,    // top-right    // 2
    -0.5f, 0.5f,  0.0f,    // top-left     // 3
  };
  unsigned int indices[] = {
    0, 1, 2,    //
    2, 3, 0,    //
  };
  // NOLINTEND

  {    // Setting up buffers and binding the,
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  }

  {    // Binding Buffer Data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  }

  {    // Describing Vertex Layout
    const int pos_index = 0;
    glEnableVertexAttribArray(pos_index);
    glVertexAttribPointer(pos_index, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
  }

  { // Unbind Everything
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  // TRIANGLE

  // SHADERS

  m_shaderProgram = new ShaderProgram("shaders/default.vert", "shaders/default.frag");
  m_shaderProgram->BindShader();
}

bool OpenGL::Resize(event::FrameBufferResize* event) {
  glViewport(0, 0, event->width, event->height);
  return false;
}

void OpenGL::BeginFrame() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL::RenderFrame() {
  m_shaderProgram->BindShader();
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void OpenGL::EndFrame() { }

void OpenGL::Cleanup() {
  delete m_shaderProgram;
}
}
