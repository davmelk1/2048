#include "label.h"

Label::Label(float x, float y) : size(0), text('0', font) {
    update_position(x, y, sf::Vector2f());
}

void Label::draw(sf::RenderWindow& window) const {
    window.draw(text);
}

void Label::update_position(float x, float y, const sf::Vector2f cell_size) {
    auto [w, h] = cell_size;
    text.setPosition(x + w / 2 - text.getLocalBounds().width / 2, y + h / 2 - text.getLocalBounds().height);
}

Label::Label() : size(0), text('0', font) {
    update_position(0, 0, sf::Vector2f());
}

bool Label::is_empty() const {
    return !size;
}

int Label::get_value() const {
    return size;
}

void Label::set_value(int i) {
    size = i;
	const auto& color = constants::colormap[i];
	text.setFillColor((color.r*0.299 + color.g*0.587 + color.b*0.114) > 196 ? sf::Color::Black : sf::Color::White);
    text.setString(std::to_string(i));
    
}

sf::Vector2f Label::get_position() {
	return text.getPosition();
}

sf::Vector2f Label::get_text_size() {
    return {text.getLocalBounds().width, text.getLocalBounds().height};
}
