#include "widgets/text.hpp"

extern "C" {
#include <notcurses/notcurses.h>
}

void Text::render(struct ncplane* plane) {
    if (!plane) return;
    ncplane_putstr_yx(plane, y, x, text.c_str());
}