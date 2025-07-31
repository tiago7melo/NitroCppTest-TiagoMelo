#include <gtest/gtest.h>
#include "canvas.hpp"
#include "rectangleIntersection.hpp"

namespace nitro {

class CanvasTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST(CanvasTest, CreateFromSet) {
    Rectangle rectangle1{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {100, 100}, 260, 80};
    Rectangle rectangle3{3, {100, 100}, 270, 80};
    Rectangle rectangle4{4, {100, 100}, 280, 80};
    std::set<Rectangle> rectangles{rectangle1, rectangle2, rectangle3, rectangle4};
    Canvas canvas{rectangles};
    ASSERT_EQ(canvas.getRectangles().size(), 4);
}

TEST(CanvasTest, CreateFromSetNoDuplicateIDs) {
    Rectangle rectangle1{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {100, 100}, 260, 80};
    Rectangle rectangle3{3, {100, 100}, 270, 80};
    Rectangle rectangle4{4, {100, 100}, 280, 80};
    Rectangle rectangle5{1, {100, 100}, 250, 80};
    std::set<Rectangle> rectangles{rectangle1, rectangle2, rectangle3, rectangle4, rectangle5};
    Canvas canvas{rectangles};
    ASSERT_EQ(canvas.getRectangles().size(), 4);
}

TEST(CanvasTest, SizeSanityCheck) {
    Rectangle rectangle1{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {100, 100}, 260, 80};
    Rectangle rectangle3{3, {100, 100}, 270, 80};
    Rectangle rectangle4{4, {100, 100}, 280, 80};
    Rectangle rectangle5{1, {100, 100}, 250, 80};
    std::set<Rectangle> rectangles{rectangle1, rectangle2, rectangle3, rectangle4, rectangle5};
    Canvas canvas{rectangles};
    ASSERT_EQ(canvas.getRectangles().size(), rectangles.size());
}

TEST(CanvasTest, GetAtIndex) {
    Rectangle rectangle1{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {100, 100}, 260, 80};
    Rectangle rectangle3{3, {100, 100}, 270, 80};
    Rectangle rectangle4{4, {100, 100}, 280, 80};
    Rectangle rectangle5{1, {100, 100}, 250, 80};
    std::set<Rectangle> rectangles{rectangle1, rectangle2, rectangle3, rectangle4, rectangle5};
    Canvas canvas{rectangles};
    // set is orderded so that index == id - 1
    ASSERT_EQ(canvas.getRectangleAtIndex(0).getId(), rectangle1.getId());
    ASSERT_EQ(canvas.getRectangleAtIndex(1).getId(), rectangle2.getId());
    ASSERT_EQ(canvas.getRectangleAtIndex(2).getId(), rectangle3.getId());
    ASSERT_EQ(canvas.getRectangleAtIndex(3).getId(), rectangle4.getId());
}

TEST(CanvasTest, GetAtIndexOutOfBounds) {
    Rectangle rectangle1{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {100, 100}, 260, 80};
    Rectangle rectangle3{3, {100, 100}, 270, 80};
    Rectangle rectangle4{4, {100, 100}, 280, 80};
    Rectangle rectangle5{1, {100, 100}, 250, 80};
    std::set<Rectangle> rectangles{rectangle1, rectangle2, rectangle3, rectangle4, rectangle5};
    Canvas canvas{rectangles};

    std::string check = "";
    try {
        canvas.getRectangleAtIndex(5);
    } 
    catch (const std::exception& e) {
        check = e.what();
    }

    ASSERT_EQ(check, Canvas::outOfRangeErrorMsg);
}

// Tests set of rectangles from the set in the exercise's specification
// test/test_plots/T5SampleFromSpecification.png
TEST(CanvasTest, PairwiseIntersectionsBaseCase) {
    std::vector<Rectangle> rectanglesVec{{1, {100, 100}, 250, 80},
                                         {2, {120, 200}, 250, 150},
                                         {3, {140, 160}, 250, 100},
                                         {4, {160, 140}, 350, 190}};

    std::vector<std::set<Rectangle::ID>> interMembers = {{1, 3},
                                                         {1, 4}, 
                                                         {2, 3},
                                                         {2, 4},
                                                         {3, 4}};

    std::vector<Rectangle> interShapes = {{1, {140, 160}, 210, 20},
                                          {2, {160, 140}, 190, 40},
                                          {3, {140, 200}, 230, 60},
                                          {4, {160, 200}, 210, 130},
                                          {5, {160, 160}, 230, 100}};

    std::set<Rectangle> rectangles(rectanglesVec.begin(), rectanglesVec.end());
    Canvas canvas{rectangles};

    std::optional<std::set<Canvas::RectangleIntersection>> intersect = canvas.determinePairwiseIntersections();
    ASSERT_TRUE(intersect.has_value());

    std::vector<Canvas::RectangleIntersection> intersections(intersect.value().begin(), intersect.value().end());
    ASSERT_EQ(intersections.size(), 5);

    for (int i = 0; i < intersections.size(); i++) {
        ASSERT_EQ(intersections[i].getIntersectingRectangles(), interMembers[i]);
        ASSERT_EQ(intersections[i].getShape(), interShapes[i]);
    }
}

// test/test_plots/T1NoIntersections.png
TEST(CanvasTest, PairwiseIntersectionsNoIntersections) {
    std::set<Rectangle> rectangles{{{1, {-120, -120}, 120, 120},
                                    {2, {0, -120}, 120, 120},
                                    {3, {-120, 0}, 120, 120},
                                    {4, {0, 0}, 120, 120},
                                    {5, {-280, -280}, 120, 120},
                                    {6, {120, -280}, 120, 120},
                                    {7, {-280, 160}, 120, 120},
                                    {8, {120, 160}, 120, 120}}};

    Canvas canvas{rectangles};

    std::optional<std::set<Canvas::RectangleIntersection>> interRet = canvas.determinePairwiseIntersections();
    ASSERT_FALSE(interRet.has_value());
}
// test/test_plots/T2SingleSimpleIntersections.png
TEST(CanvasTest, PairwiseIntersectionsOneIntersection) {
    std::set<Rectangle> rectangles{{{1, {-100, -100}, 250, 80}, 
                                    {2, {-140, -160}, 250, 100}}};
    Canvas canvas{rectangles};

    std::optional<std::set<Canvas::RectangleIntersection>> interRet = canvas.determinePairwiseIntersections();
    ASSERT_TRUE(interRet.has_value());

    std::set<Canvas::RectangleIntersection> intersectionSet = interRet.value();
    std::vector<Canvas::RectangleIntersection> intersections(intersectionSet.begin(), intersectionSet.end());
    ASSERT_EQ(intersections.size(), 1);

    std::set<Rectangle::ID> expectedMembers{1, 2};
    Rectangle expectedShape = {1, {-100, -100}, 210, 40};
    std::set<Rectangle::ID> intersectionMembers = intersections[0].getIntersectingRectangles();

    ASSERT_EQ(intersectionMembers.size(), 2);
    ASSERT_EQ(intersectionMembers, expectedMembers);
    ASSERT_EQ(intersections[0].getShape(),expectedShape);
    
}
// test/test_plots/T3TwoOverlappingRectangles.png
TEST(CanvasTest, TestPairwiseIntersectionTwoOverlappingRects) {
    Rectangle r1{1, {-80, -80}, 160, 160};
    Rectangle r2{2, {-80, -80}, 160, 160};
    std::set<Rectangle> rectangles{r1, r2};
    Canvas canvas{rectangles};

    std::optional<std::set<Canvas::RectangleIntersection>> interRet = canvas.determinePairwiseIntersections();
    ASSERT_TRUE(interRet.has_value());

    std::set<Canvas::RectangleIntersection> intersectionSet = interRet.value();
    std::vector<Canvas::RectangleIntersection> intersections(intersectionSet.begin(), intersectionSet.end());
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
TEST(CanvasTest, PairwiseIntersectionsCocentricRectangles) {
    Rectangle r1{1, {-110, -100}, 240, 240};
    Rectangle r2{2, {-160, -140}, 340, 320};

    std::set<Rectangle> rectangles{r1, r2};
    Canvas canvas{rectangles};

    std::optional<std::set<Canvas::RectangleIntersection>> interRet = canvas.determinePairwiseIntersections();
    ASSERT_TRUE(interRet.has_value());

    std::set<Canvas::RectangleIntersection> intersectionSet = interRet.value();
    std::vector<Canvas::RectangleIntersection> intersections(intersectionSet.begin(), intersectionSet.end());
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

TEST(CanvasTest, TestPairwiseIntersectionOneRectangle) {
    Rectangle r1{1, {-110, -100}, 240, 240};

    std::set<Rectangle> rectangles{r1};
    Canvas canvas{rectangles};

    std::optional<std::set<Canvas::RectangleIntersection>> interRet = canvas.determinePairwiseIntersections();
    ASSERT_FALSE(interRet.has_value());
}

TEST(CanvasTest, TestPairwiseIntersectionZeroRectangles) {
    std::set<Rectangle> rectangles{};
    Canvas canvas{rectangles};

    std::optional<std::set<Canvas::RectangleIntersection>> interRet = canvas.determinePairwiseIntersections();
    ASSERT_FALSE(interRet.has_value());
}

TEST(CanvasTest, IntersectAllWithOneRectangle) {
    std::vector<Rectangle> rectanglesVec{{1, {100, 100}, 250, 80}};

    std::set<Rectangle> rectangles(rectanglesVec.begin(), rectanglesVec.end());
    Canvas canvas{rectangles};

    std::vector<Canvas::RectangleIntersection> intersections = canvas.intersectAll();
    ASSERT_EQ(intersections.size(), 0);
}

TEST(CanvasTest, IntersectAllWithZeroRectangles) {
    std::set<Rectangle> rectangles{};
    Canvas canvas{rectangles};

    std::vector<Canvas::RectangleIntersection> intersections = canvas.intersectAll();
    ASSERT_EQ(intersections.size(), 0);
}

// Tests set of rectangles from the set in the exercise's specification
// test/test_plots/T5SampleFromSpecification.png
TEST(CanvasTest, IntersectAllWithExampleFromSpecification) {
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
    Canvas canvas{rectangles};

    std::vector<Canvas::RectangleIntersection> intersections = canvas.intersectAll();
    ASSERT_EQ(intersections.size(), 7);

    for (int i = 0; i < intersections.size(); i++) {
        ASSERT_EQ(intersections[i].getIntersectingRectangles(), interMembers[i]);
        ASSERT_EQ(intersections[i].getShape(), interShapes[i]);
    }
}

// test/test_plots/T1NoIntersections.png
TEST(CanvasTest, TestIntersectAllNoIntersections) {
    std::set<Rectangle> rectangles{{{1, {-120, -120}, 120, 120},
                                    {2, {0, -120}, 120, 120},
                                    {3, {-120, 0}, 120, 120},
                                    {4, {0, 0}, 120, 120},
                                    {5, {-280, -280}, 120, 120},
                                    {6, {120, -280}, 120, 120},
                                    {7, {-280, 160}, 120, 120},
                                    {8, {120, 160}, 120, 120}}};

    Canvas canvas{rectangles};

    std::vector<Canvas::RectangleIntersection> interRet = canvas.intersectAll();
    ASSERT_EQ(interRet.size(), 0);
}

// test/test_plots/T6FourRectanglesAllIntersectEachOther.png
TEST(CanvasTest, IntersectAllRectanglesIntersectEachother) {
    std::vector<Rectangle> rectanglesVec{{1, {-160, -290}, 240, 240},
                                         {2, {-230, -360}, 385, 385},
                                         {3, {-325, -450}, 570, 570},
                                         {4, {-390, -520}, 700, 700}};

    std::vector<std::set<Rectangle::ID>> interMembers = {{1, 2},
                                                         {1, 3}, 
                                                         {1, 4},
                                                         {2, 3},
                                                         {2, 4},
                                                         {3, 4},
                                                         {1, 2, 3},
                                                         {1, 2, 4},
                                                         {1, 3, 4},
                                                         {2, 3, 4},
                                                         {1, 2, 3, 4}};
    //index = ID - 1
    std::vector<Rectangle> interShapes = {rectanglesVec[0],
                                          rectanglesVec[0],
                                          rectanglesVec[0],
                                          rectanglesVec[1],
                                          rectanglesVec[1],
                                          rectanglesVec[2],
                                          rectanglesVec[0],
                                          rectanglesVec[0],
                                          rectanglesVec[0],
                                          rectanglesVec[1],
                                          rectanglesVec[0]};

    std::set<Rectangle> rectangles(rectanglesVec.begin(), rectanglesVec.end());
    Canvas canvas{rectangles};

    std::vector<Canvas::RectangleIntersection> intersections = canvas.intersectAll();
    ASSERT_EQ(intersections.size(), 11);

    for (int i = 0; i < intersections.size(); i++) {
        ASSERT_EQ(intersections[i].getIntersectingRectangles(), interMembers[i]);
        ASSERT_EQ(intersections[i].getShape(), interShapes[i]);
    }
}

//TODO: only pairwise test

} // namespace nitro
