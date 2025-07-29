#include <gtest/gtest.h>
#include "rectangleSet.hpp"

using namespace nitro;

TEST(RectangleSetTest, CreateFromSet) {
    Rectangle rectangle1{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {100, 100}, 260, 80};
    Rectangle rectangle3{3, {100, 100}, 270, 80};
    Rectangle rectangle4{4, {100, 100}, 280, 80};
    Rectangle rectangle5{1, {100, 100}, 250, 80};
    std::set<Rectangle, RectangleComparator> rectangles{rectangle1, rectangle2, rectangle3, rectangle4, rectangle5};
    RectangleSet rectangleSet{rectangles};
    ASSERT_EQ(rectangleSet.getRectangles().size(), 4);
}

//TODO: add subset calculation logic tests (friend tests?)
