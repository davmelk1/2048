#include "test.h"

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
	ASSERT_EQ(rect.x, 25+22);
	ASSERT_EQ(rect.y, 78 + 53);
}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
