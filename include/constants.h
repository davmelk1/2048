#pragma once

#include <SFML/Graphics.hpp>

namespace constants{
    constexpr int WINDOW_WIDTH{600};
    constexpr int WINDOW_HEIGHT{600};
    constexpr int PADDING{10};
    constexpr int CELL_WIDTH{(WINDOW_WIDTH-5*PADDING)/4};
    const sf::Color WINDOW_BACKGROUND_COLOR{180, 180, 180};
    const sf::Color CELL_FILL_COLOR{90, 90, 90};
    constexpr int NUMBER_OF_SQUARES{4};
}