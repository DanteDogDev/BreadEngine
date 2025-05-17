/// @file   Event.hpp
/// @author Xein
/// @date   14/04/25
/// @brief  Base Event class

#pragma once
#include "listener.hpp"

namespace event {

using EventMap = std::multimap<unsigned char, Listener*>;

/// @brief  Core components of the event struct
struct IEvent {
  friend class EventSystem;
  virtual ~IEvent() = default;

protected:
  virtual void Notify() = 0;
};

/// @brief  Base class for all the Events
/// @tparam EventType Template for the CRTP (more info below)
template<typename EventType>
struct Event : IEvent {
  friend class EventSystem;

  /// @brief Holds all the listeners that are subscribed to the events
  static EventMap subscribers;

protected:
  void Notify() override;
};

template<typename EventType>
EventMap Event<EventType>::subscribers;

template<typename EventType>
void Event<EventType>::Notify() {
  bool handled = false;

  for (auto& subscriber : std::ranges::reverse_view(subscribers)) {
    auto* listener = subscriber.second;
    // This should never happen because listeners handle subscribing and unsubscribing 0x
    if (!listener) { throw std::runtime_error("Listener is null"); }
    handled = listener->template Dispatch<EventType>(dynamic_cast<EventType*>(this));

    if (handled) { return; }
  }
}

}
