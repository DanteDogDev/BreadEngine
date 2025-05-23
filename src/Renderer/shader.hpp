/**
 * @file shader.hpp
 * @author Dante Harper
 * @date 18/05/25
 */

#pragma once

#include "defines.hpp"

namespace renderer {

class ShaderProgram {
public:
  ShaderProgram(const std::string& vertex_path, const std::string& fragment_path);
  ~ShaderProgram();

  void BindShader() const;

private:
  RenderID m_shaderProgramId;

  static RenderID CompileShader(RenderID type, const std::string& source);
};

}
