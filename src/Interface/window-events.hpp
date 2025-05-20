/**
 * @file window-events.hpp
 * @author Dante Harper
 * @date 17/05/25
 *
 * @brief [TODO: Brief description of the file's purpose]
 */

#pragma once

#include <Utils/event-system.h>
struct GLFWwindow;

namespace event {

struct WindowClose : Event<WindowClose> {
  WindowClose(GLFWwindow* window) : window(window) { }

  GLFWwindow* window;

  static void Callback(GLFWwindow* window);
};

struct WindowResize : Event<WindowResize> {
  WindowResize(GLFWwindow* window, int width, int height) : window(window), width(width), height(height) { }

  GLFWwindow* window;
  int width;
  int height;

  static void Callback(GLFWwindow* window, int width, int height);
};

struct FrameBufferResize : Event<FrameBufferResize> {
  FrameBufferResize(GLFWwindow* window, int width, int height) : window(window), width(width), height(height) { }

  GLFWwindow* window;
  int width;
  int height;

  static void Callback(GLFWwindow* window, int width, int height);
};

struct WindowContentResize : Event<WindowContentResize> {
  WindowContentResize(GLFWwindow* window, float x_scale, float y_scale) : window(window), xScale(x_scale), yScale(y_scale) { }

  GLFWwindow* window {};
  float xScale;
  float yScale;

  static void Callback(GLFWwindow* window, float x_scale, float y_scale);
};

struct WindowPosition : Event<WindowPosition> {
  WindowPosition(GLFWwindow* window, int x_pos, int y_pos) : window(window), xPos(x_pos), yPos(y_pos) { }

  GLFWwindow* window {};
  int xPos;
  int yPos;

  static void Callback(GLFWwindow* window, int x_pos, int y_pos);
};

struct WindowMinimized : Event<WindowMinimized> {
  WindowMinimized(GLFWwindow* window, bool minimized) : window(window), minimized(minimized) { }

  GLFWwindow* window {};
  bool minimized;

  static void Callback(GLFWwindow* window, int minimized);
};

struct WindowMaximized : Event<WindowMaximized> {
  WindowMaximized(GLFWwindow* window, bool maximized) : window(window), maximized(maximized) { }

  GLFWwindow* window {};
  bool maximized;

  static void Callback(GLFWwindow* window, int maximized);
};

struct WindowFocused : Event<WindowFocused> {
  WindowFocused(GLFWwindow* window, bool focused) : window(window), focused(focused) { }

  GLFWwindow* window {};
  bool focused;

  static void Callback(GLFWwindow* window, int focused);
};

struct KeyboardKey : Event<KeyboardKey> {
  KeyboardKey(GLFWwindow* window, int key, int scancode, int action, int mods) : key(key), scancode(scancode), action(action), mods(mods) { }

  int key;
  int scancode;
  int action;
  int mods;

  static void Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

struct KeyboardChar : Event<KeyboardChar> {
  KeyboardChar(GLFWwindow* window, unsigned key) : key(key) { }

  unsigned key;

  static void Callback(GLFWwindow* window, unsigned key);
};

struct MousePosition : Event<WindowPosition> {
  MousePosition(GLFWwindow* window, double x_pos, double y_pos) : window(window), xPos(x_pos), yPos(y_pos) { }

  GLFWwindow* window {};
  double xPos;
  double yPos;

  static void Callback(GLFWwindow* window, double x_pos, double y_pos);
};

struct MouseEntered : Event<MouseEntered> {
  MouseEntered(GLFWwindow* window, bool entered) : window(window), entered(entered) { }

  GLFWwindow* window {};
  bool entered;

  static void Callback(GLFWwindow* window, int entered);
};

struct MouseButton : Event<MouseButton> {
  MouseButton(GLFWwindow* window, int button, int action, int mods) : window(window), button(button), action(action), mods(mods) { }

  GLFWwindow* window {};
  int button;
  int action;
  int mods;

  static void Callback(GLFWwindow* window, int button, int action, int mods);
};

struct MouseScroll : Event<MouseScroll> {
  MouseScroll(GLFWwindow* window, double x_offset, double y_offset) : window(window), xOffset(x_offset), yOffset(y_offset) { }

  GLFWwindow* window {};
  double xOffset;
  double yOffset;

  static void Callback(GLFWwindow* window, double x_offset, double y_offset);
};

}
