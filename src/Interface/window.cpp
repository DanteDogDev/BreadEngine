#include "window.hpp"

#include <GLFW/glfw3.h>
#include <Utils/log.hpp>

namespace interface {

Window::Window(unsigned width, unsigned height, const std::string& name) {
  TOAST_TRACE("Creating Window");

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
}
