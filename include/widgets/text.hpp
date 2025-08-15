#pragma once
#include <string>

#include "Widget.hpp"

class Text : public Widget {
   public:
    explicit Text(const std::string& text) : text(std::move(text)) {}
    void set_text(const std::string& new_text) { text = std::move(new_text); }
    void render(struct ncplane* plane) override;

   private:
    std::string text;
};