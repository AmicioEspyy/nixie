#pragma once

class Event;
class Terminal;

class Widget {
   public:
    virtual ~Widget() = default;
    virtual void set_parent(Terminal* terminal) { parent = terminal; }
    virtual void set_position(const int xc, const int yc) {
        this->x = xc;
        this->y = yc;
    }

    virtual void render(struct ncplane* plane) = 0;
    virtual void onEvent(const Event& e) {}

   protected:
    Terminal* parent = nullptr;
    int x = 0, y = 0;
};