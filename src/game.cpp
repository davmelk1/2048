#include "game.h"

GameWindow::GameWindow() : window({constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT+constants::PADDING_TOP}, "2048") {
    Label::font.loadFromFile("/home/davit/Downloads/Times-New-Arial/timesnewarial.ttf");
    window.setFramerateLimit(60);
	reset();
}

void GameWindow::run() {
    
    while (window.isOpen()) {
        if (game_is_over()) {
			show_game_over_scene();
			reset();
			continue;
		}
        
        handle_events();
        
        draw_widgets();
        
        window.display();
    }
}

void GameWindow::populate_the_board() {
    float x{constants::PADDING}, y{constants::PADDING + constants::PADDING_TOP};
    for (auto& row : board) {
        for (auto& cell: row) {
			cell.set_value(0);
            cell.with_size(constants::CELL_WIDTH);
            cell.set_position(x, y);
            cell.with_color(constants::EMPTY_CELL_FILL_COLOR);
            x += constants::CELL_WIDTH + constants::PADDING;
        }
        x = constants::PADDING;
        y+=constants::CELL_WIDTH + constants::PADDING;
    }
}

void GameWindow::handle_events() {
    sf::Event ev{};
    while (window.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed || ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
            window.close();
        if (ev.type == sf::Event::KeyPressed) {
            switch (ev.key.code) {
                case (sf::Keyboard::Left):
                    move_left();
					break;
                case (sf::Keyboard::Right):
                    move_right();
					break;
                case (sf::Keyboard::Up):
                    move_up();
					break;
                case (sf::Keyboard::Down):
                    move_down();
					break;
                case (sf::Keyboard::R):
                    reset();
					break;
                default:
                    continue;
            }
        }
    }
}

void GameWindow::draw_widgets() {
    window.clear(constants::WINDOW_BACKGROUND_COLOR);
    
    for (const auto& row : board)
        for (const auto& cell: row)
            cell.draw(window);
}

void GameWindow::create_one_new_initial_square() {
    static std::mt19937 mt(std::chrono::system_clock::now().time_since_epoch().count());
    static std::uniform_int_distribution<int> dist(0, constants::NUMBER_OF_SQUARES - 1);
    static std::uniform_int_distribution<int> generator_0_to_100(0, 100);
    while (true) {
        auto i = dist(mt);
        auto j = dist(mt);
        if (board[i][j].is_empty()) {
            board[i][j].set_value(generator_0_to_100(mt) < constants::PROBABILITY_FOR_4 ? 4 : 2);
            break;
        }
    }
}

bool GameWindow::game_is_over() const {
    for (const auto& row : board)
        for (const auto& cell : row)
            if (cell.is_empty())
                return false;
	for (int i = 0; i < constants::NUMBER_OF_SQUARES; ++i) {
       for (int j = 1; j < constants::NUMBER_OF_SQUARES; ++j) {
           if (board[i][j].get_value() == board[i][j-1].get_value() || board[j][i].get_value() == board[j-1][i].get_value()) {
               return false;
           }
       }
    }
    return true;
}

void GameWindow::move_left() {
	bool is_there_a_move{false};
	move_non_zero_values_to_left(is_there_a_move);
	join_equal_value_squares_to_left(is_there_a_move);
	if (is_there_a_move) {
		move_non_zero_values_to_left(is_there_a_move);
		create_one_new_initial_square();
	}
}

void GameWindow::move_right() {
	bool is_there_a_move{false};
	move_non_zero_values_to_right(is_there_a_move);
	join_equal_value_squares_to_right(is_there_a_move);
	if (is_there_a_move) {
		move_non_zero_values_to_right(is_there_a_move);
		create_one_new_initial_square();
	}
}

void GameWindow::move_up() {
	bool is_there_a_move{false};
	move_non_zero_values_to_up(is_there_a_move);
	join_equal_value_squares_to_up(is_there_a_move);
	if (is_there_a_move) {
		move_non_zero_values_to_up(is_there_a_move);
		create_one_new_initial_square();
	}
}

void GameWindow::move_down() {
	bool is_there_a_move{false};
	move_non_zero_values_to_down(is_there_a_move);
	join_equal_value_squares_to_down(is_there_a_move);
	if (is_there_a_move) {
		move_non_zero_values_to_down(is_there_a_move);
		create_one_new_initial_square();
	}
}

void GameWindow::move_non_zero_values_to_left(bool& is_changed) {
	for (int i = 0; i < constants::NUMBER_OF_SQUARES; ++i) {
		int first_empty{-1};
		for (int j = 0; j < constants::NUMBER_OF_SQUARES; ++j) {
			if (board[i][j].is_empty()) {
				if (first_empty == -1)
					first_empty = j;
			} else if (first_empty != -1) {
				board[i][first_empty++].set_value(board[i][j].get_value());
				board[i][j].set_value(0);
				is_changed = true;
			}
		}
	}
}

void GameWindow::join_equal_value_squares_to_left(bool& is_changed) {
	for (int i = 0; i < constants::NUMBER_OF_SQUARES; ++i) {
		int left_addable_index{0};
		for (int j = 1; j < constants::NUMBER_OF_SQUARES; ++j) {
			if (board[i][j].get_value() != 0 && board[i][j].get_value() == board[i][left_addable_index].get_value()) {
				board[i][left_addable_index].set_value(board[i][j].get_value()*2);
				board[i][j].set_value(0);
				left_addable_index = j+++1;
				is_changed = true;
			} else {
				left_addable_index = j;
			}
		}
	}
}

void GameWindow::move_non_zero_values_to_right(bool& is_changed) {
	for (int i = 0; i < constants::NUMBER_OF_SQUARES; ++i) {
		int last_empty{-1};
		for (int j = constants::NUMBER_OF_SQUARES - 1; j >= 0; --j) {
			if (board[i][j].is_empty()) {
				if (last_empty == -1)
					last_empty = j;
			} else if (last_empty != -1) {
				board[i][last_empty--].set_value(board[i][j].get_value());
				board[i][j].set_value(0);
				is_changed = true;
			}
		}
	}
}

void GameWindow::join_equal_value_squares_to_right(bool& is_changed) {
	for (int i = 0; i < constants::NUMBER_OF_SQUARES; ++i) {
		int right_addable_index{constants::NUMBER_OF_SQUARES - 1};
		for (int j = constants::NUMBER_OF_SQUARES - 2; j >= 0; --j) {
			if (board[i][j].get_value() != 0 && board[i][j].get_value() == board[i][right_addable_index].get_value()) {
				board[i][right_addable_index].set_value(board[i][j].get_value() * 2);
				board[i][j].set_value(0);
				right_addable_index = j---1;
				is_changed = true;
			} else {
				right_addable_index = j;
			}
		}
	}
}

void GameWindow::move_non_zero_values_to_up(bool& is_changed) {
	for (int j = 0; j < constants::NUMBER_OF_SQUARES; ++j) {
		int first_empty{-1};
		for (int i = 0; i < constants::NUMBER_OF_SQUARES; ++i) {
			if (board[i][j].is_empty()) {
				if (first_empty == -1)
					first_empty = i;
			} else if (first_empty != -1) {
				board[first_empty++][j].set_value(board[i][j].get_value());
				board[i][j].set_value(0);
				is_changed = true;
			}
		}
	}
}

void GameWindow::join_equal_value_squares_to_up(bool& is_changed) {
	for (int j = 0; j < constants::NUMBER_OF_SQUARES; ++j) {
		int left_addable_index{0};
		for (int i = 1; i < constants::NUMBER_OF_SQUARES; ++i) {
			if (board[i][j].get_value() != 0 && board[i][j].get_value() == board[left_addable_index][j].get_value()) {
				board[left_addable_index][j].set_value(board[i][j].get_value() * 2);
				board[i][j].set_value(0);
				left_addable_index = i+++1;
				is_changed = true;
			} else {
				left_addable_index = i;
			}
		}
	}
}

void GameWindow::move_non_zero_values_to_down(bool& is_changed) {
	for (int j = 0; j < constants::NUMBER_OF_SQUARES; ++j) {
		int last_empty{-1};
		for (int i = constants::NUMBER_OF_SQUARES - 1; i >= 0; --i) {
			if (board[i][j].is_empty()) {
				if (last_empty == -1)
					last_empty = i;
			} else if (last_empty != -1) {
				board[last_empty--][j].set_value(board[i][j].get_value());
				board[i][j].set_value(0);
				is_changed = true;
			}
		}
	}
}

void GameWindow::join_equal_value_squares_to_down(bool& is_changed) {
	for (int j = 0; j < constants::NUMBER_OF_SQUARES; ++j) {
		int left_addable_index{constants::NUMBER_OF_SQUARES - 1};
		for (int i = constants::NUMBER_OF_SQUARES - 2; i >= 0; --i) {
			if (board[i][j].get_value() != 0 && board[i][j].get_value() == board[left_addable_index][j].get_value()) {
				board[left_addable_index][j].set_value(board[i][j].get_value() * 2);
				board[i][j].set_value(0);
				left_addable_index = i---1;
				is_changed = true;
			} else {
				left_addable_index = i;
			}
		}
	}
}

using namespace std::chrono_literals;

void GameWindow::show_game_over_scene() {
	window.clear(constants::WINDOW_BACKGROUND_COLOR);
	sf::Text game_over_text;
	game_over_text.setString("Game over.");
	game_over_text.setFillColor(sf::Color::Red);
	game_over_text.setFont(Label::font);
	game_over_text.setPosition(constants::WINDOW_WIDTH / 2 - game_over_text.getLocalBounds().width / 2,
							   constants::WINDOW_HEIGHT / 2 - game_over_text.getLocalBounds().height / 2);
	for (auto& row : board)
		for (auto& cell : row) {
			cell.set_game_over_color();
			cell.draw(window);
		}
	window.draw(game_over_text);
	window.display();
	sf::sleep(sf::seconds(3));
}

void GameWindow::reset() {
	populate_the_board();
	create_one_new_initial_square();
}
