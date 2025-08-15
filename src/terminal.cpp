#include "terminal.hpp"

#include <notcurses/notcurses.h>
#include <termios.h>
#include <unistd.h>

#include "events/KeyEvent.hpp"
#include "widget.hpp"

Terminal::Terminal() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == 0) {
        have_orig_termios = true;
    }

    nc = notcurses_init(NULL, stdout);
    stdplane = notcurses_stdplane(nc);
}

Terminal::~Terminal() { stop(); }

void Terminal::stop() {
    if (!running) return;
    running = false;

    if (nc) {
        int ret = notcurses_stop(nc);
        if (ret != 0) {
            std::fprintf(stderr, "notcurses_stop returned %d\n", ret);
        }
        nc = nullptr;
        stdplane = nullptr;
    }

    if (have_orig_termios) {
        if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios) != 0) {
            std::fprintf(stderr, "warning: tcsetattr restore failed\n");
        }

        std::fprintf(stderr, "Terminal::stop() restoring original termios\n");
        have_orig_termios = false;
    }

    std::fflush(stdout);
    std::fprintf(stderr, "Terminal::stop() done\n");
}

void Terminal::add(std::shared_ptr<Widget> widget) {
    if (!widget) return;
    widget->set_parent(this);
    widgets.push_back(widget);
}

void Terminal::clear() {
    if (!nc) return;
    ncplane_erase(stdplane);
}

void Terminal::render() {
    if (!running || !stdplane) return;

    clear();
    for (const auto& widget : widgets) {
        widget->render(stdplane);
    }
}

void Terminal::refresh() {
    if (!nc) return;
    notcurses_render(nc);
}

void Terminal::pollEvents() {
    if (!nc) return;

    struct ncinput ni;
    while (notcurses_get_nblock(nc, &ni) > 0) {
        if (ni.evtype == NCTYPE_PRESS) {
            if (ni.id == 'q') {
                stop();
                return;
            }

            eventQueue.push(std::make_unique<KeyEvent>(ni.id));
        }
    }
}

void Terminal::dispatchEvents() {
    while (!eventQueue.empty()) {
        auto& e = eventQueue.front();
        for (auto& w : widgets) {
            w->onEvent(*e);
        }
        eventQueue.pop();
    }
}