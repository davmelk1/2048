#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

#include "constants.h"

class Label{
public:
    inline static sf::Font font;
    Label(float x, float y);
    Label();
    
    void draw(sf::RenderWindow& window) const;
    
    void update_position(float x, float y, const sf::Vector2f cell_size);
	
	bool is_empty() const;
    
    int get_value() const;
    
    void set_value(int i);
	
	sf::Vector2f get_position();
 
	sf::Vector2f get_text_size();

private:
    int size{0};
    sf::Text text;
	
};
