#pragma once
#include <optional>

enum class VerticalAlignment {
    TOP,
    CENTER,
    BOTTOM,
};

enum class HorizontalAlignment {
    LEFT,
    CENTER,
    RIGHT,
};

struct Position {
    std::optional<int> x;
    std::optional<int> y;

    std::optional<VerticalAlignment> v;
    std::optional<HorizontalAlignment> h;

    int offset_x = 0;
    int offset_y = 0;

    [[nodiscard]] std::pair<int, int> compute(int termWidth, int termHeight, int widgetWidth, int widgetHeight) const {
        int rx = 0;
        int ry = 0;

        if (h.has_value()) {
            switch (h.value()) {
                case HorizontalAlignment::LEFT:
                    rx = 0;
                    break;
                case HorizontalAlignment::CENTER:
                    rx = (termWidth - widgetWidth / 2) / 2;
                    break;
                case HorizontalAlignment::RIGHT:
                    rx = termWidth - widgetWidth;
                    break;
            }
        } else if (x.has_value()) {
            rx = x.value();
        }

        if (v.has_value()) {
            switch (v.value()) {
                case VerticalAlignment::TOP:
                    ry = 0;
                    break;
                case VerticalAlignment::CENTER:
                    ry = (termHeight - widgetHeight / 2) / 2;
                    break;
                case VerticalAlignment::BOTTOM:
                    ry = termHeight - widgetHeight;
                    break;
            }
        } else if (y.has_value()) {
            ry = y.value();
        }

        return {rx + offset_x, ry + offset_y};
    }
};
