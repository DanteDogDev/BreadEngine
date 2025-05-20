#include "shader.hpp"

#include <Utils/log.h>

// clang-format off
#include <glad/gl.h>
#include <GL/gl.h>
// clang-format on

namespace renderer {
RenderID CompileShader(RenderID type, const std::string& source) {
  RenderID id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);
  // ERROR HANDLING HERE
  int compiled {};
  glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
  if (!compiled) {
    int log_length = 0;
    std::array<char, 1024> message;    // NOLINT
    glGetShaderInfoLog(id, 1024, &log_length, message.data());
    TOAST_ERROR("Shader Error: Failede to Compile {}\n{}", std::string(message.data()), source);
  }
  return id;
}

}
