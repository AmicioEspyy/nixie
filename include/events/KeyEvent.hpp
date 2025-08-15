#pragma once
#include "Event.hpp"

class KeyEvent : public Event {
   public:
    KeyEvent(int keyCode) : Event(EventType::KeyPressed), keyCode(keyCode) {}
    int getKeyCode() const { return keyCode; }

   private:
    int keyCode;
};