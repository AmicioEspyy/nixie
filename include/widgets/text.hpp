#pragma once
#include <string>
#include <utility>

#include "Widget.hpp"

class Text : public Widget {
   public:
    explicit Text(std::string text) : text(std::move(text)) {}
    void set_text(const std::string& new_text) { text = new_text; }
    void render(struct ncplane* plane) override;
    int getWidth() override;
    int getHeight() override;

   private:
    std::string text;
};