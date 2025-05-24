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
    const unsigned attrib_index = 0;
    const unsigned binding_index = 0;
    // binds the vbo data to the binding index
    glVertexArrayVertexBuffer(m_vao, binding_index, m_vbo, 0, sizeof(float) * 3);
    // formats the a attribute according to the vbo
    glEnableVertexArrayAttrib(m_vao, attrib_index);
    glVertexArrayAttribFormat(m_vao, attrib_index, 3, GL_FLOAT, GL_FALSE, 0);
    // Binds the data coming from the vbo and puts it onto the shader at the attrib_index
    glVertexArrayAttribBinding(m_vao, attrib_index, binding_index);
    glVertexArrayElementBuffer(m_vao, m_ebo);
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
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
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
