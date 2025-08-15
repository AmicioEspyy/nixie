#pragma once
#include <termios.h>

#include <memory>
#include <queue>
#include <vector>

class Event;

class Widget;

class Terminal {
   public:
    Terminal();
    ~Terminal();

    void stop();
    void clear();
    void refresh();
    void render();
    void add(std::shared_ptr<Widget> widget);
    void pollEvents();
    void dispatchEvents();
    bool isRunning() const { return running; }

   private:
    struct termios orig_termios{};
    bool have_orig_termios = false;
    bool running = true;
    struct notcurses* nc;
    struct ncplane* stdplane;
    std::vector<std::shared_ptr<Widget>> widgets;
    std::queue<std::unique_ptr<Event>> eventQueue;
};