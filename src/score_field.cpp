#include "score_field.h"

int ScoreField::get_score() const {
    return score;
}

void ScoreField::set_value(int i) {
    score = i;
}

void ScoreField::calculate_value(const std::array<std::array<Square, 4>, 4>& board) {
    int sum = 0;
    for (const auto& row : board)
        for (const auto& cell : row)
            sum += cell.get_value();
    set_value(sum);
}

void ScoreField::draw(sf::RenderWindow& window) {
    window.draw(score_background);
    t.setString(std::to_string(score));
    t.setPosition(score_background.getPosition().x + score_background.getSize().x / 2 - t.getLocalBounds().width / 2,
                  score_background.getPosition().y + score_background.getSize().y / 2 - t.getLocalBounds().height);
    window.draw(t);
}

void ScoreField::add_value(int val) {
    score+=val;
}

ScoreField::ScoreField() {
    score_background.setFillColor({200, 200, 200});
    score_background.setPosition(constants::WINDOW_WIDTH * 0.8, constants::PADDING);
    score_background.setSize({constants::WINDOW_WIDTH * 0.15, constants::PADDING_TOP - constants::PADDING});
    t.setFont(Label::font);

}

void ScoreField::reset() {
    score = 0;
}
