#include "square.h"


Square Square::create_square_in_position(float x, float y) {
    return {x, y};
}

Square::Square(float x, float y) : Square() {
    square.setPosition(x, y);
    label.update_position(x, y, square.getSize());
}

Square& Square::with_size(float size) {
    square.setSize({size, size});
    return *this;
}

Square& Square::set_position(float x, float y) {
    square.setPosition(x, y);
    label.update_position(x, y, square.getSize());
    return *this;
}

Square& Square::with_color(const sf::Color& color) {
    square.setFillColor(color);
    return *this;
}

void Square::draw(sf::RenderWindow& window) const {
    window.draw(square);
    if (label.get_value())
        label.draw(window);
}

Square::Square() {

}

bool Square::is_empty() const {
    return label.is_empty();
}

void Square::set_init_value(InitialValue value) {
    label.set_init_value(value);
}

int Square::get_value() const {
    return label.get_value();
}

void Square::set_value(int i) {
    label.set_value(i);
}

void Square::set_game_over_color() {
	square.setFillColor(constants::COLOR_GAME_OVER);
}
