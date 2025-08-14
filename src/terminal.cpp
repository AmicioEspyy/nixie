#include "terminal.hpp"

#include <notcurses/notcurses.h>

#include "widget.hpp"

Terminal::Terminal() {
    nc = notcurses_init(NULL, stdout);
    stdplane = notcurses_stdplane(nc);
}

Terminal::~Terminal() { notcurses_stop(nc); }

void Terminal::add(std::shared_ptr<Widget> widget) {
    if (!widget) return;
    widget->set_parent(this);
    widgets.push_back(widget);
}

void Terminal::clear() { ncplane_erase(stdplane); }

void Terminal::render() {
    clear();
    for (const auto& widget : widgets) {
        widget->render(stdplane);
    }
}

void Terminal::refresh() { notcurses_render(nc); }
