/// @file   Listener.hpp
/// @author Xein
/// @date   14/04/25
/// @brief  Code that contains the listener of the Event System

#pragma once
#include <Utils/log.h>

namespace event {
struct IEvent;

class TOAST_API Listener {
public:
  friend class IEvent;
  template<typename TEvent>
  friend class Event;

  using EventMap = std::multimap<unsigned char, Listener*>;

  Listener() = default;
  ~Listener();

  Listener(const Listener&) = delete;
  Listener& operator=(const Listener&) = delete;

  /// @brief Subscribes a function to an specific event
  template<typename TEvent>
  void Subscribe(std::string name, std::function<bool(TEvent*)> callback, unsigned char priority = 1);

  /// @brief Subscribes a function to an event without specifying a name
  template<typename TEvent>
  void Subscribe(std::function<bool(TEvent*)> callback, unsigned char priority = 1) {
    Subscribe<TEvent>("Unnamed", callback, priority);
  }

  /// @brief Unsubscribes all callbacks from the event
  template<typename TEvent>
  void Unsubscribe();

  /// @brief Unsubscribes an specific callback from the event
  template<typename TEvent>
  void Unsubscribe(std::string name);

private:
  /// @brief This function calls all the functions on the @m_callbacks map asociated to one event
  template<typename TEvent>
  [[nodiscard]]
  bool Dispatch(TEvent* event);

  std::unordered_multimap<std::type_index, std::pair<std::string, std::any>> m_callbacks;
  std::unordered_map<std::type_index, EventMap*> m_events;    // This need to exist for the destructor 0x
};

template<typename TEvent>
void Listener::Subscribe(std::string name, std::function<bool(TEvent*)> callback, unsigned char priority) {
  static_assert(std::is_base_of_v<IEvent, TEvent>, "Event T is not inherited from IEvent");
  TOAST_INFO("Subscribing listener to event {0}", typeid(TEvent).name());

  // Add function to callback map
  std::pair callback_pair = { name, callback };
  m_callbacks.emplace(typeid(TEvent), callback_pair);

  // If the old priority is less than the new priority, we remove the old key to add it again with the new one 0x
  if (m_events.contains(typeid(TEvent))) {
    if (priority == 1) {
      return;    // We return if the priority is default to avoid checking more stuff 0x
    }

    for (auto it = TEvent::subscribers.begin(); it != TEvent::subscribers.end(); ++it) {
      if (it->second == this && it->first < priority) {
        TOAST_TRACE("Changing {0} priority from {1} to {2}", typeid(TEvent).name(), static_cast<int>(it->first), static_cast<int>(priority));
        TEvent::subscribers.erase(it);
      } else if (it->second == this && it->first >= priority) {
        return;
      }
    }
  }

  // Add EventMap to event map
  m_events.emplace(typeid(TEvent), &TEvent::subscribers);
  // Add listeners to event subscribers map
  TEvent::subscribers.emplace(priority, this);
}

template<typename TEvent>
void Listener::Unsubscribe() {
  static_assert(std::is_base_of_v<IEvent, TEvent>, "Event T is not inherited from IEvent");
  size_t count = m_callbacks.count(typeid(TEvent));
  if (!m_callbacks.contains(typeid(TEvent))) {
    TOAST_WARN("Trying to unsubscribe from an event but there is no callback assigned, aborting...");
    return;
  }

  // Remove functions from callback map
  TOAST_INFO("Removing {0} callbacks from event {1}", count, typeid(TEvent).name());
  m_callbacks.erase(typeid(TEvent));

  // Remove EventMap* from event map
  m_events.erase(typeid(TEvent));

  // Remove listener from event subscribers map
  for (auto it = TEvent::subscribers.begin(); it != TEvent::subscribers.end(); ++it) {
    if (it->second == this) {
      TEvent::subscribers.erase(it);
      break;
    }
  }
}

template<typename TEvent>
void Listener::Unsubscribe(std::string name) {
  static_assert(std::is_base_of_v<IEvent, TEvent>, "Event T is not inherited from IEvent");

  // CHECK if more functions exist
  size_t count = m_callbacks.count(typeid(TEvent));
  if (count == 0) {
    TOAST_WARN("Trying to unsubscribe from an event but there is no callback assigned, aborting...");
    return;
  }
  if (count == 1) {
    TOAST_TRACE("Only one instance found, calling Unsubscribe from All");
    Unsubscribe<TEvent>();
  }

  // Remove function from callback map
  TOAST_INFO("Unsubscribing callback from event {0}", typeid(TEvent).name());
  unsigned char deleted_functions = 0;
  auto range = m_callbacks.equal_range(typeid(TEvent));
  for (auto it = range.first; it != range.second;) {
    // We any_cast it to our pair of string and function and then check if the names match
    auto [callback_name, _] = it->second;
    if (callback_name == name) {
      it = m_callbacks.erase(it);
      deleted_functions++;
    } else {
      // Need to check this to remove ALL functions that are the same
      // not just the first one 0x
      ++it;
    }
  }

  // NOTE: Since a lot of you like to do typos while coding, i'll put a warning if no callbacks were unsubscribed 0x
  if (deleted_functions == 0) { TOAST_WARN("No callbacks were unsubscribed, check \"{0}\" for typos", name); }
}

template<typename TEvent>
inline bool Listener::Dispatch(TEvent* event) {
  // Find range with all callbacks
  auto [begin, end] = m_callbacks.equal_range(typeid(TEvent));
  bool handled = false;

  // Call each callback
  for (auto it = begin; it != end; ++it) {
    auto [name, callback] = it->second;
    handled = std::any_cast<std::function<bool(TEvent*)>>(callback)(event);
    if (handled) { return true; }
  }

  return false;
}

inline Listener::~Listener() {
  // Removes references for this listener on the events
  TOAST_INFO("Unsubscribing from {0} events", m_events.size());
  for (auto [_, event_map] : m_events) {
    for (auto it = event_map->begin(); it != event_map->end(); ++it) {
      if (it->second == this) {
        event_map->erase(it);
        break;
      }
    }
  }
}

}
