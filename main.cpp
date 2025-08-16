#include <iostream>

#include "Terminal.hpp"
#include "nixie.hpp"
#include "widgets/Text.hpp"

int main() {
    auto term = std::make_unique<Terminal>();

    auto txt = std::make_shared<Text>("Hello, Nixie!");
    txt->set_alignment(HorizontalAlignment::CENTER, VerticalAlignment::CENTER);
    term->add(txt);

    while (term->isRunning()) {
        term->pollEvents();
        term->dispatchEvents();
        term->render();
        term->refresh();
    }

    return 0;
}