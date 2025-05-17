/// @file   EventSystem.cpp
/// @author Xein

#include "eventSystem.hpp"

#include "event.hpp"

#include <Utils/log.hpp>

namespace event {

std::queue<IEvent*> EventSystem::m_eventQueue;

void EventSystem::SendEvent(IEvent* event) {
  if (!event) {
    TOAST_WARN("Event is not valid, aborting send");
    return;
  }

  TOAST_TRACE("Event {0} sent", typeid(*event).name());
  event::EventSystem::m_eventQueue.push(event);
}

void Send(IEvent* event) {
  EventSystem::SendEvent(event);
}

void EventSystem::PollEvents() {
  if (m_eventQueue.empty()) { return; }

  while (!m_eventQueue.empty()) {
    IEvent* event = m_eventQueue.front();
    m_eventQueue.pop();
    if (!event) { continue; }

    event->Notify();
    delete event;
  }
}

}
