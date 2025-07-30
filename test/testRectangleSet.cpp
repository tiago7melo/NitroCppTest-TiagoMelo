#include <gtest/gtest.h>
#include "rectangleSet.hpp"

namespace nitro {

class RectangleSetTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST(RectangleSetTest, CreateFromSet) {
    Rectangle rectangle1{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {100, 100}, 260, 80};
    Rectangle rectangle3{3, {100, 100}, 270, 80};
    Rectangle rectangle4{4, {100, 100}, 280, 80};
    Rectangle rectangle5{1, {100, 100}, 250, 80};
    std::set<Rectangle> rectangles{rectangle1, rectangle2, rectangle3, rectangle4, rectangle5};
    RectangleSet rectangleSet{rectangles};
    ASSERT_EQ(rectangleSet.getRectangles().size(), 4);
}

TEST(RectangleSetTest, SizeSanityCheck) {
    Rectangle rectangle1{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {100, 100}, 260, 80};
    Rectangle rectangle3{3, {100, 100}, 270, 80};
    Rectangle rectangle4{4, {100, 100}, 280, 80};
    Rectangle rectangle5{1, {100, 100}, 250, 80};
    std::set<Rectangle> rectangles{rectangle1, rectangle2, rectangle3, rectangle4, rectangle5};
    RectangleSet rectangleSet{rectangles};
    ASSERT_EQ(rectangleSet.getRectangles().size(), rectangles.size());
}

TEST(RectangleSetTest, GetAtIndex) {
    Rectangle rectangle1{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {100, 100}, 260, 80};
    Rectangle rectangle3{3, {100, 100}, 270, 80};
    Rectangle rectangle4{4, {100, 100}, 280, 80};
    Rectangle rectangle5{1, {100, 100}, 250, 80};
    std::set<Rectangle> rectangles{rectangle1, rectangle2, rectangle3, rectangle4, rectangle5};
    RectangleSet rectangleSet{rectangles};
    // set is orderded so that index == id - 1
    ASSERT_EQ(rectangleSet.atIndex(0).getId(), rectangle1.getId());
    ASSERT_EQ(rectangleSet.atIndex(1).getId(), rectangle2.getId());
    ASSERT_EQ(rectangleSet.atIndex(2).getId(), rectangle3.getId());
    ASSERT_EQ(rectangleSet.atIndex(3).getId(), rectangle4.getId());
}

TEST(RectangleSetTest, GetAtIndexOutOfBounds) {
    Rectangle rectangle1{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {100, 100}, 260, 80};
    Rectangle rectangle3{3, {100, 100}, 270, 80};
    Rectangle rectangle4{4, {100, 100}, 280, 80};
    Rectangle rectangle5{1, {100, 100}, 250, 80};
    std::set<Rectangle> rectangles{rectangle1, rectangle2, rectangle3, rectangle4, rectangle5};
    RectangleSet rectangleSet{rectangles};

    std::string check = "";
    try {
        rectangleSet.atIndex(5);
    } 
    catch (const std::exception& e) {
        check = e.what();
    }

    ASSERT_EQ(check, RectangleSet::outOfRangeErrorMsg);
}

TEST(RectangleSetTest, TestPairwiseIntersections) {
    Rectangle r1{1, {100, 100}, 250, 80}; //TODO: put to fixture?
    Rectangle r2{2, {120, 200}, 250, 150};
    Rectangle r3{3, {140, 160}, 250, 100};
    Rectangle r4{4, {160, 140}, 350, 190};
    std::set<Rectangle> rectangles{r1, r2, r3, r4};
    RectangleSet rectangleSet{rectangles};

    std::optional<std::set<RectangleIntersection>> interRet = rectangleSet.determinePairwiseIntersections();
    ASSERT_TRUE(interRet.has_value());

    std::set<RectangleIntersection> intersectionSet = interRet.value();
    std::vector<RectangleIntersection> intersections(intersectionSet.begin(), intersectionSet.end());
    ASSERT_EQ(intersections.size(), 5);

    std::set<Rectangle::ID> intersectionOneMembers = intersections[0].getIntersectingRectangles();
    Rectangle intersectionOneShape = intersections[0].getShape();

    ASSERT_EQ(intersectionOneMembers.size(), 2);
    std::set<Rectangle::ID> expectedMembers1{1, 3};
    ASSERT_EQ(intersectionOneMembers, expectedMembers1);
    //TODO: assert shape

    std::set<Rectangle::ID> intersectionTwoMembers = intersections[1].getIntersectingRectangles();
    Rectangle intersectionTwoShape = intersections[1].getShape();

    ASSERT_EQ(intersectionTwoMembers.size(), 2);
    std::set<Rectangle::ID> expectedMembers2{1, 4};
    ASSERT_EQ(intersectionTwoMembers, expectedMembers2);
    //TODO: assert shape

    
}

} // namespace nitro
