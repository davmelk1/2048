#pragma once

#include <SFML/Graphics.hpp>

#include "label.h"
#include "value_enum.h"
#include "constants.h"

class Square{
public:
    static Square create_square_in_position(float x, float y);
    Square& set_position(float x = 0, float y = 0);
    Square& with_size(float size);
    Square& with_color(const sf::Color& color);
    bool is_empty() const;
    void set_init_value(InitialValue value);
    void draw(sf::RenderWindow& window) const;
    Square();
    
    int get_value() const;
    
    void set_value(int i);
	
	void set_game_over_color();

private:
    Square(float x, float y);
    sf::RectangleShape square;
    Label label;
};
