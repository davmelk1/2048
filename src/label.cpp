#include "label.h"

Label::Label(float x, float y) : size(0), text('0', font) {
    update_position(x, y, sf::Vector2f());
}

void Label::draw(sf::RenderWindow& window) const {
    window.draw(text);
}

void Label::update_position(float x, float y, const sf::Vector2f vector2) {
    auto [w, h] = vector2;
    text.setPosition(x + w / 2 - text.getLocalBounds().width / 2, y + h / 2 - text.getLocalBounds().width / 2);
}

Label::Label() : size(0), text('0', font) {
    update_position(0, 0, sf::Vector2f());
}

bool Label::is_empty() const {
    return !size;
}

void Label::set_init_value(InitialValue value) {
    size = value == InitialValue::TWO ? 2 : 4;;
    text.setString(std::to_string(size));
}

int Label::get_value() const {
    return size;
}

void Label::set_value(int i) {
    size = i;
    text.setString(std::to_string(i));
    
}
