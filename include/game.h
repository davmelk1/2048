#pragma once

#include <random>
#include <chrono>
#include <iostream>

#include "constants.h"
#include "square.h"

class GameWindow{
public:
    GameWindow();
    void run();
private:
    sf::RenderWindow window;
    std::array<std::array<Square, constants::NUMBER_OF_SQUARES>, constants::NUMBER_OF_SQUARES> board;
    
    void populate_the_board();
    void handle_events();
    void draw_widgets();
    
    void create_one_new_initial_square();
    
    bool game_is_over() const;
    
    void move_left();
	
	void move_right();
	
	void move_up();
	
	void move_down();
	
	void move_non_zero_values_to_left(bool& is_changed);
	
	void join_equal_value_squares_to_left(bool& is_changed);
	
	void move_non_zero_values_to_right(bool& is_changed);
	
	void join_equal_value_squares_to_right(bool& is_changed);
	
	void move_non_zero_values_to_up(bool& is_changed);
	
	void join_equal_value_squares_to_up(bool& is_changed);
	
	void move_non_zero_values_to_down(bool& is_changed);
	
	void join_equal_value_squares_to_down(bool& is_changed);
};
