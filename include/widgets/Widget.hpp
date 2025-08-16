#pragma once
#include "ui/Position.hpp"

class Event;
class Terminal;

class Widget {
   public:
    virtual ~Widget() = default;
    virtual void set_parent(Terminal* terminal) { parent = terminal; }
    void set_position(int xc, int yc) {
        pos.x = xc;
        pos.y = yc;
    }
    void set_alignment(HorizontalAlignment h, VerticalAlignment v) {
        pos.h = h;
        pos.v = v;
    }

    virtual void render(struct ncplane* plane) = 0;
    virtual void onEvent(const Event& e) {}

   protected:
    Terminal* parent = nullptr;
    Position pos;
};