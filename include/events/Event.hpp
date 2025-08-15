#pragma once
#include <string>

enum class EventType { KeyPressed };

class Event {
   public:
    Event(EventType type) : type(type) {}
    virtual ~Event() = default;
    EventType getType() const { return type; }

   private:
    EventType type;
};