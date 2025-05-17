/**
 * @file window.hpp
 * @author Dante Harper
 * @date 16/05/25
 */

#pragma once

struct GLFWwindow;
using GLFWglproc = void (*)();

namespace interface {

struct WindowProps {
  unsigned width;
  unsigned height;
  std::string name;
};

class TOAST_API Window {
public:
  Window(unsigned width = 800, unsigned height = 600, const std::string& name = "Toast Engine");
  ~Window();

  [[nodiscard]]
  bool ShouldClose() const;
  void Tick();

  void HandleInput() const;
  static GLFWglproc GetProcAddr(const char* procname);

private:
  WindowProps m_properties;
  GLFWwindow* m_glfwWindow;

  static constexpr int OPENGL_MAJOR = 4;
  static constexpr int OPENGL_MINOR = 6;

  static void ErrorCallback(int error, const char* description);
};

class WindowException : std::exception {
public:
  WindowException(int error, const char* description);
  int error;
  const char* description;
  std::string message;

  [[nodiscard]]
  const char* what() const noexcept override;
};
}
