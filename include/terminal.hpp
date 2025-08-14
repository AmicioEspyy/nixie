#pragma once
#include <memory>
#include <vector>

class Widget;

class Terminal {
   public:
    Terminal();
    ~Terminal();

    void clear();
    void refresh();
    void render();
    void add(std::shared_ptr<Widget> widget);

   private:
    struct notcurses* nc;
    struct ncplane* stdplane;
    std::vector<std::shared_ptr<Widget>> widgets;
};