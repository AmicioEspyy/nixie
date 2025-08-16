#include "Terminal.hpp"

#include <fcntl.h>
#include <notcurses/notcurses.h>
#include <termios.h>
#include <unistd.h>

#include "events/KeyEvent.hpp"
#include "widgets/Widget.hpp"

Terminal::Terminal() {
    // disable notcurses stats messages
    notcurses_options opts{};
    opts.flags |= NCOPTION_SUPPRESS_BANNERS;

    nc = notcurses_init(&opts, stdout);
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

    // disable kitty keyboard protocol
    std::fputs("\x1b[>0u", stdout);
    std::fflush(stdout);
}

void Terminal::add(const std::shared_ptr<Widget>& widget) {
    if (!widget) return;
    widget->set_parent(this);
    widgets.push_back(widget);
}

void Terminal::clear() const {
    if (!nc) return;
    ncplane_erase(stdplane);
}

void Terminal::render() const {
    if (!running || !stdplane) return;

    clear();
    for (const auto& widget : widgets) {
        widget->render(stdplane);
    }
}

void Terminal::refresh() const {
    if (!nc) return;
    notcurses_render(nc);
}

void Terminal::pollEvents() {
    if (!nc) return;

    ncinput ni;
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