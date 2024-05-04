#include "constants.h"
#include "square.h"

class ScoreField{
public:
    ScoreField();
	int get_score() const;
    
    void set_value(int i);
    
    void calculate_value(const std::array<std::array<Square, 4>, 4>& array1);
    
    void draw(sf::RenderWindow& window);
    
    void add_value(int val);
    
    void reset();

private:
    sf::RectangleShape score_background;
    sf::Text t;
	int score{0};
};
