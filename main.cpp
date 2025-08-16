#include <iostream>

#include "Terminal.hpp"
#include "nixie.hpp"
#include "widgets/Text.hpp"

int main() {
    auto term = std::make_unique<Terminal>();

    auto left = std::make_shared<Text>("left");
    left->set_alignment(HorizontalAlignment::LEFT, VerticalAlignment::BOTTOM);
    left->set_offset(0, -2);
    term->add(left);

    auto txt = std::make_shared<Text>("Hello, Nixie!");
    txt->set_alignment(HorizontalAlignment::CENTER, VerticalAlignment::BOTTOM);
    txt->set_offset(0, -2);
    term->add(txt);

    auto right = std::make_shared<Text>("right");
    right->set_alignment(HorizontalAlignment::RIGHT, VerticalAlignment::BOTTOM);
    right->set_offset(0, -2);
    term->add(right);

    while (term->isRunning()) {
        term->pollEvents();
        term->dispatchEvents();
        term->render();
        term->refresh();
    }

    return 0;
}