#include "window-events.hpp"

#include <Utils/event-system.h>

namespace event {

void WindowClose::Callback(GLFWwindow* window) {
  event::Send(new WindowClose(window));
}

void WindowResize::Callback(GLFWwindow* window, int width, int height) {
  event::Send(new WindowResize(window, width, height));
}

void FrameBufferResize::Callback(GLFWwindow* window, int width, int height) {
  event::Send(new FrameBufferResize(window, width, height));
}

void WindowContentResize::Callback(GLFWwindow* window, float x_scale, float y_scale) {
  event::Send(new WindowContentResize(window, x_scale, y_scale));
}

void WindowPosition::Callback(GLFWwindow* window, int x_pos, int y_pos) {
  event::Send(new WindowPosition(window, x_pos, y_pos));
}

void WindowMinimized::Callback(GLFWwindow* window, int minimized) {
  event::Send(new WindowMinimized(window, minimized));
}

void WindowMaximized::Callback(GLFWwindow* window, int maximized) {
  event::Send(new WindowMaximized(window, maximized));
}

void WindowFocused::Callback(GLFWwindow* window, int focused) {
  event::Send(new WindowFocused(window, focused));
}

void KeyboardKey::Callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  event::Send(new KeyboardKey(window, key, scancode, action, mods));
}

void KeyboardChar::Callback(GLFWwindow* window, unsigned key) {
  event::Send(new KeyboardChar(window, key));
}

void MousePosition::Callback(GLFWwindow* window, double x_pos, double y_pos) {
  event::Send(new MousePosition(window, x_pos, y_pos));
}

void MouseEntered::Callback(GLFWwindow* window, int entered) {
  event::Send(new MouseEntered(window, entered));
}

void MouseButton::Callback(GLFWwindow* window, int button, int action, int mods) {
  event::Send(new MouseButton(window, button, action, mods));
}

void MouseScroll::Callback(GLFWwindow* window, double x_offset, double y_offset) {
  event::Send(new MouseScroll(window, x_offset, y_offset));
}

}
