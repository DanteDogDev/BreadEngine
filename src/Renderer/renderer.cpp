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
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
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
    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,    // bottom-left  // 0
    0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,    // bottom-right // 1
    0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,    // top-right    // 2
    -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f     // top-left     // 3
  };
  unsigned int indices[] = {
    0, 1, 2,    //
    0, 2, 3,    //
  };
  // NOLINTEND

  {    // Creating Buffers
    glCreateVertexArrays(1, &m_vao);
    glCreateBuffers(1, &m_vbo);
    glCreateBuffers(1, &m_ebo);
  }

  {    // Binding Data to the buffers
    glNamedBufferData(m_vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glNamedBufferData(m_ebo, sizeof(indices), indices, GL_STATIC_DRAW);
  }

  {    // Binding Buffers the the vao and describing their layout
    // binds the vbo data to the binding index
    glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(float) * 9);
    glVertexArrayElementBuffer(m_vao, m_ebo);
    // formats the a attribute according to the vbo
    glEnableVertexArrayAttrib(m_vao, 0);
    glEnableVertexArrayAttrib(m_vao, 1);
    glEnableVertexArrayAttrib(m_vao, 2);
    //
    glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(m_vao, 1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3);
    glVertexArrayAttribFormat(m_vao, 2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7);
    // Binds the data coming from the vbo and puts it onto the shader at the attrib_index
    glVertexArrayAttribBinding(m_vao, 0, 0);
    glVertexArrayAttribBinding(m_vao, 1, 0);
    glVertexArrayAttribBinding(m_vao, 2, 0);
  }

  m_shaderProgram = new ShaderProgram("shaders/default.vert", "shaders/default.frag");
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
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void OpenGL::EndFrame() { }

void OpenGL::Cleanup() {
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);
  delete m_shaderProgram;
}
}
