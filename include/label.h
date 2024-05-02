#pragma once

#include "SFML/Graphics.hpp"
#include "constants.h"

class Label{
public:
    inline static sf::Font font;
    Label(float x, float y);
    Label();
    
    void draw(sf::RenderWindow& window) const;
    
    void update_position(float x, float y, const sf::Vector2f vector2);
	
	bool is_empty() const;
    
    int get_value() const;
    
    void set_value(int i);

private:
    int size{0};
    sf::Text text;
    
};
