#include <iostream>

#include "Terminal.hpp"
#include "nixie.hpp"
#include "widgets/Text.hpp"

int main() {
    auto term = std::make_unique<Terminal>();

    auto txt = std::make_shared<Text>("Hello, Nixie!");
    txt->set_position(5, 5);
    term->add(txt);

    while (term->isRunning()) {
        term->pollEvents();
        term->dispatchEvents();
        term->render();
        term->refresh();
    }

    std::system("reset");
    std::cout << "done." << std::endl;
    return 0;
}