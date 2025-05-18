#include "renderer.hpp"

#include "Interface/window-events.hpp"
#include "Renderer/shader.hpp"
#include "Utils/file.hpp"

#include <Utils/log.hpp>

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

  // Makes a buffer and binds it to the VERTEX ARRAY BUFFER
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  // TRIANGLE
  glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

  // Describe how data is sent to the shader
  const int pos_index = 0;
  glEnableVertexAttribArray(pos_index);
  glVertexAttribPointer(pos_index, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

  glBindBuffer(GL_ARRAY_BUFFER,0);
  // TRIANGLE

  // SHADERS
  m_shaderProgram = glCreateProgram();

  const std::string vertex_code = utils::LoadTextFile("shaders/default.vert");
  const std::string fragment_code = utils::LoadTextFile("shaders/default.frag");

  RenderID vs = CompileShader(GL_VERTEX_SHADER, vertex_code);
  RenderID fs = CompileShader(GL_FRAGMENT_SHADER, fragment_code);

  glAttachShader(m_shaderProgram, vs);
  glAttachShader(m_shaderProgram, fs);
  glLinkProgram(m_shaderProgram);
  glValidateProgram(m_shaderProgram);

  glDeleteShader(vs);
  glDeleteShader(fs);

  glUseProgram(m_shaderProgram);
  // SHADERS
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

void OpenGL::Cleanup() {  // NOLINT
  glDeleteProgram(m_shaderProgram);
}
}
