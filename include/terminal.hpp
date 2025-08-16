#pragma once

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
    void clear() const;
    void refresh() const;
    void render() const;
    void add(const std::shared_ptr<Widget>& widget);
    void pollEvents();
    void dispatchEvents();
    [[nodiscard]] bool isRunning() const { return running; }

   private:
    bool running = true;
    struct notcurses* nc;
    struct ncplane* stdplane;
    std::vector<std::shared_ptr<Widget>> widgets;
    std::queue<std::unique_ptr<Event>> eventQueue;
};