#include "widgets/Text.hpp"

#include "Terminal.hpp"

extern "C" {
#include <notcurses/notcurses.h>
}

int Text::getWidth() { return static_cast<int>(text.size()); }
int Text::getHeight() { return 1; }

void Text::render(ncplane* plane) {
    if (!plane) return;

    int width = parent->getWidth();
    int height = parent->getHeight();

    auto [new_x, new_y] = pos.compute(width, height, getWidth(), getHeight());
    ncplane_putstr_yx(plane, new_y, new_x, text.c_str());
}