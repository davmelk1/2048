#include "game.h"

GameWindow::GameWindow() : window({constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT}, "2048") {
    Label::font.loadFromFile("/home/davit/.local/share/fonts/timesnewarial.ttf");
    window.setFramerateLimit(60);
    populate_the_board();
    create_one_new_initial_square();
}

void GameWindow::run() {
    
    while (window.isOpen()) {
        if (game_is_over())
            break;
        
        handle_events();
        
        draw_widgets();
        
        window.display();
    }
}

void GameWindow::populate_the_board() {
    int x{constants::PADDING}, y{constants::PADDING};
    for (auto& row : board) {
        for (auto& square: row) {
            square.with_size(constants::CELL_WIDTH);
            square.set_position(x, y);
            square.with_color(constants::CELL_FILL_COLOR);
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
                case (sf::Keyboard::Right):
                    1;
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
    static std::uniform_int_distribution<int> dist(0, constants::NUMBER_OF_SQUARES);
    static std::bernoulli_distribution bernoulli;
    while (true) {
        auto i = dist(mt);
        auto j = dist(mt);
        if (board[i][j].is_empty()) {
            board[i][j].set_init_value(InitialValue(rand() % 100 < 30));
            break;
        }
    }
}

bool GameWindow::game_is_over() const {
    for (const auto& row : board)
        for (const auto& square : row)
            if (square.is_empty())
                return false;
    return true;
}

void GameWindow::move_left() {
    move_non_zero_values_to_left();
    join_equal_value_squares();
    move_non_zero_values_to_left();
    create_one_new_initial_square();
}

void GameWindow::move_non_zero_values_to_left() {
    for (int i = 0; i < constants::NUMBER_OF_SQUARES; ++i) {
        int first_empty{-1};
        for (int j = 0; j < constants::NUMBER_OF_SQUARES; ++j) {
            if (board[i][j].is_empty()) {
                if (first_empty == -1)
                    first_empty = j;
            } else if (first_empty != -1) {
                board[i][first_empty++].set_value(board[i][j].get_value());
                board[i][j].set_value(0);
            }
        }
    }
}

void GameWindow::join_equal_value_squares() {
    for (int i = 0; i < constants::NUMBER_OF_SQUARES; ++i) {
        int left_addable_index{0};
        for (int j = 1; j < constants::NUMBER_OF_SQUARES; ++j) {
            if (board[i][j].get_value() == board[i][left_addable_index].get_value()) {
                board[i][left_addable_index].set_value(board[i][j].get_value()*2);
                left_addable_index = j+++1;
            } else {
                left_addable_index = j;
            }
        }
    }
}

