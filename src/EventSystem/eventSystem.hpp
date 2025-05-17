/// @file   EventSystem.hpp
/// @author Xein
/// @date   16/04/25
/// @brief  Object responsible for handling the queue of events

#pragma once

namespace event {
struct IEvent;
class Listener;

class TOAST_API EventSystem {
public:
  friend class Listener;

  /// @brief See @c event::Send instead
  static void SendEvent(IEvent* event);

  static void PollEvents();

private:
  EventSystem() = default;
  ~EventSystem() = default;

  static std::queue<IEvent*> m_eventQueue;
};

void TOAST_API Send(IEvent* event);

}
