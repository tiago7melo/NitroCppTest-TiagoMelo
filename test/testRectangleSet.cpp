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
    std::set<Rectangle> rectangles{rectangle1, rectangle2, rectangle3, rectangle4};
    RectangleSet rectangleSet{rectangles};
    ASSERT_EQ(rectangleSet.getRectangles().size(), 4);
}

TEST(RectangleSetTest, CreateFromSetNoDuplicateIDs) {
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
    ASSERT_EQ(rectangleSet.getRectangleAtIndex(0).getId(), rectangle1.getId());
    ASSERT_EQ(rectangleSet.getRectangleAtIndex(1).getId(), rectangle2.getId());
    ASSERT_EQ(rectangleSet.getRectangleAtIndex(2).getId(), rectangle3.getId());
    ASSERT_EQ(rectangleSet.getRectangleAtIndex(3).getId(), rectangle4.getId());
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
        rectangleSet.getRectangleAtIndex(5);
    } 
    catch (const std::exception& e) {
        check = e.what();
    }

    ASSERT_EQ(check, RectangleSet::outOfRangeErrorMsg);
}

// Tests set of rectangles from the set in the exercise's specification
// test/test_plots/T5SampleFromSpecification.png
TEST(RectangleSetTest, TestPairwiseIntersections) {
    Rectangle r1{1, {100, 100}, 250, 80};
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
    std::set<Rectangle::ID> expectedMembers1{1, 3};

    ASSERT_EQ(intersectionOneMembers.size(), 2);
    ASSERT_EQ(intersectionOneMembers, expectedMembers1);
    ASSERT_EQ(intersectionOneShape.getVertices().topLeft.x, 140);
    ASSERT_EQ(intersectionOneShape.getVertices().topLeft.y, 160);
    ASSERT_EQ(intersectionOneShape.getWidth(), 210);
    ASSERT_EQ(intersectionOneShape.getHeight(), 20);

    std::set<Rectangle::ID> intersectionTwoMembers = intersections[1].getIntersectingRectangles();
    Rectangle intersectionTwoShape = intersections[1].getShape();
    std::set<Rectangle::ID> expectedMembers2{1, 4};

    ASSERT_EQ(intersectionTwoMembers.size(), 2);
    ASSERT_EQ(intersectionTwoMembers, expectedMembers2);
    ASSERT_EQ(intersectionTwoShape.getVertices().topLeft.x, 160);
    ASSERT_EQ(intersectionTwoShape.getVertices().topLeft.y, 140);
    ASSERT_EQ(intersectionTwoShape.getWidth(), 190);
    ASSERT_EQ(intersectionTwoShape.getHeight(), 40);

    std::set<Rectangle::ID> intersectionFiveMembers = intersections[4].getIntersectingRectangles();
    Rectangle intersectionFiveShape = intersections[4].getShape();
    std::set<Rectangle::ID> expectedMembers5{3, 4};

    ASSERT_EQ(intersectionFiveMembers.size(), 2);
    ASSERT_EQ(intersectionFiveMembers, expectedMembers5);
    ASSERT_EQ(intersectionFiveShape.getVertices().topLeft.x, 160);
    ASSERT_EQ(intersectionFiveShape.getVertices().topLeft.y, 160);
    ASSERT_EQ(intersectionFiveShape.getWidth(), 230);
    ASSERT_EQ(intersectionFiveShape.getHeight(), 100);
}

// test/test_plots/T1NoIntersections.png
TEST(RectangleSetTest, TestPairwiseIntersectionsNoIntersections) {
    Rectangle r1{1, {-120, -120}, 120, 120};
    Rectangle r2{2, {0, -120}, 120, 120};
    Rectangle r3{3, {-120, 0}, 120, 120};
    Rectangle r4{4, {0, 0}, 120, 120};
    Rectangle r5{5, {-280, -280}, 120, 120};
    Rectangle r6{6, {120, -280}, 120, 120};
    Rectangle r7{7, {-280, 160}, 120, 120};
    Rectangle r8{8, {120, 160}, 120, 120};

    std::set<Rectangle> rectangles{r1, r2, r3, r4};
    RectangleSet rectangleSet{rectangles};

    std::optional<std::set<RectangleIntersection>> interRet = rectangleSet.determinePairwiseIntersections();
    ASSERT_FALSE(interRet.has_value());
}
// test/test_plots/T2SingleSimpleIntersections.png
TEST(RectangleSetTest, TestPairwiseIntersectionsOneIntersection) {
    Rectangle r1{1, {-100, -100}, 250, 80};
    Rectangle r2{2, {-140, -160}, 250, 100};
    std::set<Rectangle> rectangles{r1, r2};
    RectangleSet rectangleSet{rectangles};

    std::optional<std::set<RectangleIntersection>> interRet = rectangleSet.determinePairwiseIntersections();
    ASSERT_TRUE(interRet.has_value());

    std::set<RectangleIntersection> intersectionSet = interRet.value();
    std::vector<RectangleIntersection> intersections(intersectionSet.begin(), intersectionSet.end());
    ASSERT_EQ(intersections.size(), 1);

    std::set<Rectangle::ID> intersectionMembers = intersections[0].getIntersectingRectangles();
    Rectangle intersectionOneShape = intersections[0].getShape();
    std::set<Rectangle::ID> expectedMembers{1, 2};

    ASSERT_EQ(intersectionMembers.size(), 2);
    ASSERT_EQ(intersectionMembers, expectedMembers);
    ASSERT_EQ(intersectionOneShape.getVertices().topLeft.x, -100);
    ASSERT_EQ(intersectionOneShape.getVertices().topLeft.y, -100);
    ASSERT_EQ(intersectionOneShape.getWidth(), 210);
    ASSERT_EQ(intersectionOneShape.getHeight(), 40);
    
}
// test/test_plots/T3TwoOverlappingRectangles.png
TEST(RectangleSetTest, TestPairwiseIntersectionTwoOverlappingRects) {
    Rectangle r1{1, {-80, -80}, 160, 160};
    Rectangle r2{2, {-80, -80}, 160, 160};
    std::set<Rectangle> rectangles{r1, r2};
    RectangleSet rectangleSet{rectangles};

    std::optional<std::set<RectangleIntersection>> interRet = rectangleSet.determinePairwiseIntersections();
    ASSERT_TRUE(interRet.has_value());

    std::set<RectangleIntersection> intersectionSet = interRet.value();
    std::vector<RectangleIntersection> intersections(intersectionSet.begin(), intersectionSet.end());
    ASSERT_EQ(intersections.size(), 1);

    std::set<Rectangle::ID> intersectionMembers = intersections[0].getIntersectingRectangles();
    Rectangle intersectionOneShape = intersections[0].getShape();
    std::set<Rectangle::ID> expectedMembers{1, 2};

    ASSERT_EQ(intersectionMembers.size(), 2);
    ASSERT_EQ(intersectionMembers, expectedMembers);
    ASSERT_EQ(intersectionOneShape.getVertices().topLeft.x, -80);
    ASSERT_EQ(intersectionOneShape.getVertices().topLeft.y, -80);
    ASSERT_EQ(intersectionOneShape.getWidth(), 160);
    ASSERT_EQ(intersectionOneShape.getHeight(), 160);
}
// test/test_plots/T4TwoConcentricRectangles.png
TEST(RectangleSetTest, TestPairwiseIntersectionsCocentricRectangles) {
    Rectangle r1{1, {-110, -100}, 240, 240};
    Rectangle r2{2, {-160, -140}, 340, 320};

    std::set<Rectangle> rectangles{r1, r2};
    RectangleSet rectangleSet{rectangles};

    std::optional<std::set<RectangleIntersection>> interRet = rectangleSet.determinePairwiseIntersections();
    ASSERT_TRUE(interRet.has_value());

    std::set<RectangleIntersection> intersectionSet = interRet.value();
    std::vector<RectangleIntersection> intersections(intersectionSet.begin(), intersectionSet.end());
    ASSERT_EQ(intersections.size(), 1);

    std::set<Rectangle::ID> intersectionMembers = intersections[0].getIntersectingRectangles();
    Rectangle intersectionOneShape = intersections[0].getShape();
    std::set<Rectangle::ID> expectedMembers{1, 2};

    ASSERT_EQ(intersectionMembers.size(), 2);
    ASSERT_EQ(intersectionMembers, expectedMembers);
    ASSERT_EQ(intersectionOneShape.getVertices().topLeft.x, -110);
    ASSERT_EQ(intersectionOneShape.getVertices().topLeft.y, -100);
    ASSERT_EQ(intersectionOneShape.getWidth(), 240);
    ASSERT_EQ(intersectionOneShape.getHeight(), 240);
}

TEST(RectangleSetTest, TestPairwiseIntersectionOneRectangle) {
    Rectangle r1{1, {-110, -100}, 240, 240};

    std::set<Rectangle> rectangles{r1};
    RectangleSet rectangleSet{rectangles};

    std::optional<std::set<RectangleIntersection>> interRet = rectangleSet.determinePairwiseIntersections();
    ASSERT_FALSE(interRet.has_value());
}

// Tests set of rectangles from the set in the exercise's specification
// test/test_plots/T5SampleFromSpecification.png
TEST(RectangleSetTest, IntersectAllWithExampleFromSpecification) {
    std::vector<Rectangle> rectanglesVec{{1, {100, 100}, 250, 80},
                                         {2, {120, 200}, 250, 150},
                                         {3, {140, 160}, 250, 100},
                                         {4, {160, 140}, 350, 190}};

    std::vector<std::set<Rectangle::ID>> interMembers = {{1, 3},
                                                         {1, 4}, 
                                                         {2, 3},
                                                         {2, 4},
                                                         {3, 4},
                                                         {1, 3, 4},
                                                         {2, 3, 4}};

    std::vector<Rectangle> interShapes = {{1, {140, 160}, 210, 20},
                                          {2, {160, 140}, 190, 40},
                                          {3, {140, 200}, 230, 60},
                                          {4, {160, 200}, 210, 130},
                                          {5, {160, 160}, 230, 100},
                                          {6, {160, 160}, 190, 20},
                                          {7, {160, 200}, 210, 60}};

    std::set<Rectangle> rectangles(rectanglesVec.begin(), rectanglesVec.end());
    RectangleSet rectangleSet{rectangles};

    std::vector<RectangleIntersection> intersections = rectangleSet.intersectAll();
    ASSERT_EQ(intersections.size(), 7);

    for (int i = 0; i < intersections.size(); i++) {
        ASSERT_EQ(intersections[i].getIntersectingRectangles(), interMembers[i]);
        ASSERT_EQ(intersections[i].getShape(), interShapes[i]);
    }
}

//TODO: adapt tests considering equality operator for rectangle
//TODO: add edge case validation to intersectAll

} // namespace nitro
