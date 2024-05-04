#pragma once

#include <gtest/gtest.h>

#include "label.h"

class LabelTest : public ::testing::Test {
protected:
	Label label;
};


TEST(LabelClassTest, CreationOfLabel) {
    Label label;
}

TEST_F(LabelTest, emptyLabelValue) {
    ASSERT_EQ(label.get_value(), 0);
}

TEST_F(LabelTest, emptyLabelEmptiness) {
    ASSERT_TRUE(label.is_empty());
}

TEST_F(LabelTest, settingValue) {
    int n{75};
    label.set_value(n);
    ASSERT_EQ(label.get_value(), n);
}

TEST_F(LabelTest, settingPosition) {
    label.update_position(25, 78, {44, 106});
    auto rect = label.get_position();
    EXPECT_EQ(rect.x, 25+22);
    EXPECT_EQ(rect.y, 78 + 53);
}

TEST_F(LabelTest, checkTextWidthHeight) {
    Label::font.loadFromFile("/home/davit/.local/share/fonts/timesnewarial.ttf");
    sf::Text text{"2", Label::font};
    label.set_value(2);
    auto size = label.get_text_size();
    EXPECT_EQ(size.x, text.getLocalBounds().width);
    EXPECT_EQ(size.y, text.getLocalBounds().height);
    text.setString("32");
    label.set_value(32);
    size = label.get_text_size();
    EXPECT_EQ(size.x, text.getLocalBounds().width);
    EXPECT_EQ(size.y, text.getLocalBounds().height);
    text.setString("256");
    label.set_value(256);
    size = label.get_text_size();
    EXPECT_EQ(size.x, text.getLocalBounds().width);
    EXPECT_EQ(size.y, text.getLocalBounds().height);
    text.setString("1024");
    label.set_value(1024);
    size = label.get_text_size();
    EXPECT_EQ(size.x, text.getLocalBounds().width);
    EXPECT_EQ(size.y, text.getLocalBounds().height);
    text.setString("16384");
    label.set_value(16384);
    size = label.get_text_size();
    EXPECT_EQ(size.x, text.getLocalBounds().width);
    EXPECT_EQ(size.y, text.getLocalBounds().height);
}
