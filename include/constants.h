#pragma once

#include <SFML/Graphics.hpp>

namespace constants{
    constexpr int WINDOW_WIDTH{600};
    constexpr int WINDOW_HEIGHT{600};
    constexpr int PADDING{10};
    constexpr int PADDING_TOP{80};
    constexpr int CELL_WIDTH{(WINDOW_WIDTH-5*PADDING)/4};
    const sf::Color WINDOW_BACKGROUND_COLOR{180, 180, 180};
    const sf::Color EMPTY_CELL_FILL_COLOR{150, 150, 150};
    constexpr int NUMBER_OF_SQUARES{4};
	constexpr int PROBABILITY_FOR_4{20};
	inline std::map<int, sf::Color> colormap{
			{0, {150, 150, 150}},
			{2, {238, 228, 218}},
			{4, {237, 224, 200}},
			{8, {242, 177, 121}},
			{16, {245, 149, 99}},
			{32, {245, 149, 99}},
			{64, {246, 94, 59}},
			{128, {237, 207, 114}},
			{256, {237, 204, 97}},
			{512, {237, 200, 80}},
			{1024, {245, 149, 99}},
			{2048, {245, 149, 99}},
	};
	const sf::Color COLOR_OTHER = sf::Color::Black;
	const sf::Color COLOR_GAME_OVER = sf::Color(238, 228, 218);
}
