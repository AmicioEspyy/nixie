#include "nixie.hpp"
#include "terminal.hpp"
#include "widgets/text.hpp"

int main() {
    auto term = std::make_unique<Terminal>();

    auto txt = std::make_shared<Text>("Hello, Nixie!");
    txt->set_position(5, 5);
    term->add(txt);

    while (true) {
        term->render();
        term->refresh();
    }

    return 0;
}