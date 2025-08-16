#pragma once
#include "Event.hpp"

class KeyEvent : public Event {
   public:
    explicit KeyEvent(int keyCode) : Event(EventType::KeyPressed), keyCode(keyCode) {}
    [[nodiscard]] int getKeyCode() const { return keyCode; }

   private:
    int keyCode;
};