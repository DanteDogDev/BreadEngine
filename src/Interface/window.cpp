#include "window.hpp"

#include "window-events.hpp"

#include <GLFW/glfw3.h>
#include <Utils/log.hpp>

namespace interface {

Window::Window(unsigned width, unsigned height, const std::string& name) {
  TOAST_TRACE("Creating Window");
  glfwSetErrorCallback(ErrorCallback);

  m_properties.name = name;
  m_properties.width = width;
  m_properties.height = height;

  TOAST_ASSERT(glfwInit(), "Couldn't initialize GLFW");
  TOAST_INFO("Creating window {0} ({1}, {2})", m_properties.name, m_properties.width, m_properties.height);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  m_glfwWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);    // NOLINT
  glfwMakeContextCurrent(m_glfwWindow);

  glfwSetWindowCloseCallback(m_glfwWindow, event::WindowClose::Callback);
  glfwSetWindowSizeCallback(m_glfwWindow, event::WindowResize::Callback);
  glfwSetFramebufferSizeCallback(m_glfwWindow, event::FrameBufferResize::Callback);
  glfwSetWindowContentScaleCallback(m_glfwWindow, event::WindowContentResize::Callback);
  glfwSetWindowPosCallback(m_glfwWindow, event::WindowPosition::Callback);
  glfwSetWindowIconifyCallback(m_glfwWindow, event::WindowMinimized::Callback);
  glfwSetWindowMaximizeCallback(m_glfwWindow, event::WindowMaximized::Callback);
  glfwSetWindowFocusCallback(m_glfwWindow, event::WindowFocused::Callback);

  glfwSetKeyCallback(m_glfwWindow, event::KeyboardKey::Callback);
  glfwSetCharCallback(m_glfwWindow, event::KeyboardChar::Callback);

  glfwSetCursorPosCallback(m_glfwWindow, event::MousePosition::Callback);
  glfwSetCursorEnterCallback(m_glfwWindow, event::MouseEntered::Callback);
  glfwSetMouseButtonCallback(m_glfwWindow, event::MouseButton::Callback);
  glfwSetScrollCallback(m_glfwWindow, event::MouseScroll::Callback);
}

Window::~Window() {
  TOAST_INFO("Destroying window");
  glfwDestroyWindow(m_glfwWindow);
  glfwTerminate();
}

bool Window::ShouldClose() const {
  return glfwWindowShouldClose(m_glfwWindow);
}

void Window::Tick() {
  glfwSwapBuffers(m_glfwWindow);
  glfwPollEvents();
}

void Window::HandleInput() const {
  if (glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(m_glfwWindow, true); }
}

GLFWglproc Window::GetProcAddr(const char* procname) {
  return glfwGetProcAddress(procname);
}

#pragma region Callbacks

void Window::ErrorCallback(int error, const char* description) {
  TOAST_ERROR("GLFW ERROR {}: {}", error, description);
  throw WindowException(error, description);
}

#pragma endregion

#pragma region Exception

WindowException::WindowException(int error, const char* description) : error(error), description(description) {
  message = std::format("{}: {}", error, message);
}

const char* WindowException::what() const noexcept {
  return message.c_str();
}

#pragma endregion
}
