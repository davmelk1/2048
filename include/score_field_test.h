#pragma once

#include <gtest/gtest.h>

#include "score_field.h"
#include "square.h"
class ScoreFieldTest : public ::testing::Test {
protected:
    ScoreField score_field;
};

TEST(ScoreFieldTesting, testObjectCreation) {
    ScoreField score_field;
}

TEST_F(ScoreFieldTest, testDefaultValue) {
    ASSERT_EQ(score_field.get_score(), 0);
}

TEST_F(ScoreFieldTest, testSettingValue) {
    score_field.set_value(12);
    ASSERT_EQ(score_field.get_score(), 12);
}

TEST_F(ScoreFieldTest, testCalculateTheValue) {
    std::array<std::array<Square, 4>, 4> board;
    board[0][2].set_value(2);
    score_field.calculate_value(board);
    EXPECT_EQ(score_field.get_score(), 2);
    board[1][2].set_value(2);
    score_field.calculate_value(board);
    EXPECT_EQ(score_field.get_score(), 4);
    board[0][2].set_value(0);
    board[1][2].set_value(4);
    score_field.calculate_value(board);
    EXPECT_EQ(score_field.get_score(), 4);
    board[0][2].set_value(16);
    score_field.calculate_value(board);
    EXPECT_EQ(score_field.get_score(), 20);
}