#pragma once

enum class EventType { KeyPressed };

class Event {
   public:
    explicit Event(EventType type) : type(type) {}
    virtual ~Event() = default;
    [[nodiscard]] EventType getType() const { return type; }

   private:
    EventType type;
};