#include "shader.hpp"

#include <Utils/file.h>
#include <Utils/log.h>

// clang-format off
#include <glad/gl.h>
#include <GL/gl.h>
// clang-format on

namespace renderer {
RenderID ShaderProgram::CompileShader(RenderID type, const std::string& source) {
  RenderID id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);
  return id;
}

ShaderProgram::ShaderProgram(const std::string& vertex_path, const std::string& fragment_path) {
  m_shaderProgramId = glCreateProgram();
  const std::string vertex_code = utils::LoadTextFile(vertex_path);
  const std::string fragment_code = utils::LoadTextFile(fragment_path);

  RenderID vs = CompileShader(GL_VERTEX_SHADER, vertex_code);
  RenderID fs = CompileShader(GL_FRAGMENT_SHADER, fragment_code);

  glAttachShader(m_shaderProgramId, vs);
  glAttachShader(m_shaderProgramId, fs);
  glLinkProgram(m_shaderProgramId);

#ifdef DEBUG
  glValidateProgram(m_shaderProgramId);
#endif

  glDeleteShader(vs);
  glDeleteShader(fs);
}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(m_shaderProgramId);
}

void ShaderProgram::BindShader() const {
  glUseProgram(m_shaderProgramId);
}

}
