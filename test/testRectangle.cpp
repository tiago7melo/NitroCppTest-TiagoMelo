#include <gtest/gtest.h>
#include <limits>
#include "vertex.hpp"
#include "rectangle.hpp"
#include "rectangleIntersection.hpp"

namespace nitro {

//TODO: evaluate if we need a fixture
// class RectangleTestFixture : public ::testing::Test {
// protected:
//     void SetUp() override {
//     }

//     void TearDown() override {
//     }

//     int intMax = static_cast<uint64_t>(std::numeric_limits<int>::max());
//     int intMin = static_cast<uint64_t>(std::numeric_limits<int>::min());
// };

TEST(RectangleTest, DestructRectangles) {
    std::unique_ptr<Rectangle> rectangle = std::make_unique<Rectangle>(Rectangle{1, {100, 100}, 250, 80});
    rectangle.reset();
    ASSERT_FALSE(rectangle);
}

TEST(RectangleTest, IdCantBeZero) {
    std::string check = "";
    try {
        Rectangle rectangle{0, {100, 100}, 250, 80};
    } 
    catch (const std::exception& e) {
        check = e.what();
    }
    ASSERT_EQ(check, Rectangle::invalidIdErrorMsg);
}

TEST(RectangleTest, CreateFromTopLeftStoresInputCorrectly) {
    Rectangle rectangle{1, {100, 100}, 250, 80};
    ASSERT_EQ(rectangle.getVertices().topLeft.x, 100);
    ASSERT_EQ(rectangle.getVertices().topLeft.y, 100);
    ASSERT_EQ(rectangle.getWidth(), 250);
    ASSERT_EQ(rectangle.getHeight(), 80);
    ASSERT_EQ(rectangle.getId(), 1);
    Rectangle rectangle2{2, {140, 160}, 250, 100};
    ASSERT_EQ(rectangle2.getVertices().topLeft.x, 140);
    ASSERT_EQ(rectangle2.getVertices().topLeft.y, 160);
    ASSERT_EQ(rectangle2.getWidth(), 250);
    ASSERT_EQ(rectangle2.getHeight(), 100);
    ASSERT_EQ(rectangle2.getId(), 2);
    
}

TEST(RectangleTest, CreateFromTopLeftGeneratesCorrectVertices) {
    Rectangle rectangle{1, {100, 100}, 250, 80};
    ASSERT_EQ(rectangle.getVertices().bottomLeft.x, 100);
    ASSERT_EQ(rectangle.getVertices().bottomLeft.y, 180);
    ASSERT_EQ(rectangle.getVertices().bottomRight.x, 350);
    ASSERT_EQ(rectangle.getVertices().bottomRight.y, 180);
    ASSERT_EQ(rectangle.getVertices().topLeft.x, 100);
    ASSERT_EQ(rectangle.getVertices().topLeft.y, 100);
    ASSERT_EQ(rectangle.getVertices().topRight.x, 350);
    ASSERT_EQ(rectangle.getVertices().topRight.y, 100);
}

TEST(RectangleTest, CantChangeVerticesAfterCreationDirectly) {
    Rectangle rectangle{1, {100, 100}, 250, 80};
    Rectangle::Vertices vertices = rectangle.getVertices();
    vertices.bottomLeft.x = 2;
    ASSERT_EQ(rectangle.getVertices().bottomLeft.x, 100);
}

TEST(RectangleTest, CantChangeWidthHeightAfterCreationDirectly) {
    Rectangle rectangle{1, {100, 100}, 250, 80};
    uint32_t width = rectangle.getWidth();
    uint32_t height = rectangle.getHeight();
    width = 2;
    height = 3;
    ASSERT_EQ(rectangle.getWidth(), 250);
    ASSERT_EQ(rectangle.getHeight(), 80);
}

TEST(RectangleTest, UnderflowWidth) {
    std::string check = "";
    try {
        Rectangle rectangle{1, {100, 100}, 0, 80};
    } 
    catch (const std::exception& e) {
        check = e.what();
    }
    ASSERT_EQ(check, Rectangle::underflowErrorMsg);
}


TEST(RectangleTest, UnderflowHeight) {
    std::string check = "";
    try {
        Rectangle rectangle{1, {100, 100}, 250, 0};
    } 
    catch (const std::exception& e) {
        check = e.what();
    }
    ASSERT_EQ(check, Rectangle::underflowErrorMsg);
}

TEST(RectangleTest, WidthExceedsXBounds) {
    const int maxInt = std::numeric_limits<int>::max();
    std::string check = "";
    try {
        Rectangle rectangle{1, {maxInt - 40, 1}, 42, 80};
    } 
    catch (const std::exception& e) {
        check = e.what();
    }
    ASSERT_EQ(check, Rectangle::canvasXBoundExceededErrorMsg);
}

TEST(RectangleTest, HeightExceedsYBounds) {
    const int maxInt = std::numeric_limits<int>::max();
    std::string check = "";
    try {
        Rectangle rectangle{1, {1, maxInt - 40}, 80, 42};
    }  
    catch (const std::exception& e) {
        check = e.what();
    }
    ASSERT_EQ(check, Rectangle::canvasYBoundExceededErrorMsg);
}

TEST(RectangleTest, TestSimpleIntersection) 
{
    Rectangle rectangle{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {140, 160}, 250, 100};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());

    Rectangle expectedShape{3, {140, 160}, 210, 20};
}

TEST(RectangleTest, TestSimpleIntersectionNoOverlap) 
{
    Rectangle rectangle{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {500, 500}, 250, 100};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_FALSE(interRet.has_value());
}

TEST(RectangleTest, TestSimpleIntersectionFullOverlap) 
{
    Rectangle rectangle{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {100, 100}, 250, 80};
    
    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());

    Rectangle expectedShape{3, {100, 100}, 250, 80};
    ASSERT_EQ(interRet.value(), expectedShape);
}

TEST(RectangleTest, TestIntersectionTopLeftNegativeRectangleBisectedByXYAxis) 
{
    Rectangle rectangle{1, {-100, -100}, 250, 80};
    Rectangle rectangle2{2, {-140, -160}, 250, 100};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());
    

    Rectangle expectedShape{3, {-100, -100}, 210, 40};
    ASSERT_EQ(interRet.value(), expectedShape);
}

TEST(RectangleTest, TestIntersectionTopLeftFullNegativeCoordinates) 
{
    Rectangle rectangle{1, {-430, -230 }, 250, 80};
    Rectangle rectangle2{2, {-390 , -170}, 250, 100};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());

    Rectangle expectedShape{3, {-390, -170}, 210, 20};
    ASSERT_EQ(interRet.value(), expectedShape);
}

TEST(RectangleTest, TestIntersectionOneInsideTheOther) 
{
    Rectangle rectangle{1, {-410, -320}, 250, 220};
    Rectangle rectangle2{2, {-410 , -260}, 250, 100};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());

    Rectangle expectedShape{3, {-410, -260}, 250, 100};
    ASSERT_EQ(interRet.value(), expectedShape);
}

TEST(RectangleTest, TestIntersectionOneAcrossTheOther) 
{
    Rectangle rectangle{1, {-410, -320}, 250, 220};
    Rectangle rectangle2{2, {-330 , -350}, 70, 270};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());

    Rectangle expectedShape{3, {-330, -320}, 70, 220};
    ASSERT_EQ(interRet.value(), expectedShape);
}

TEST(RectangleTest, TestIntersectionRectangleTopLeftAtOrigin) 
{
    Rectangle rectangle{1, {0, 0}, 250 , 220};
    Rectangle rectangle2{2, {-280 , -190}, 310 , 250};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());

    Rectangle intersection = interRet.value();
    Rectangle expectedShape{3, {0,0}, 30, 60};
    ASSERT_EQ(interRet.value(), expectedShape);
}

TEST(RectangleTest, TestIntersectionAdjacentRectanglesNoIntersection) 
{
    Rectangle rectangle{1, {0, 0}, 250 , 220};
    Rectangle rectangle2{2, {-310 , -70}, 310 , 330};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_FALSE(interRet.has_value());
}

TEST(RectangleTest, TestIntersectionAbstraction) 
{
    Rectangle rectangle{1, {0, 0}, 250 , 220};
    Rectangle rectangle2{2, {-280 , -190}, 310 , 250};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());
    RectangleIntersection inter = RectangleIntersection(interRet.value(), {1, 2});

    Rectangle intersectionShape = inter.getShape();
    ASSERT_EQ(intersectionShape.getVertices().topLeft.x, 0);
    ASSERT_EQ(intersectionShape.getVertices().topLeft.y, 0);
    ASSERT_EQ(intersectionShape.getWidth(), 30);
    ASSERT_EQ(intersectionShape.getHeight(), 60);

    std::set<Rectangle::ID> expectedMembers = {1, 2};
    ASSERT_EQ(inter.getIntersectingRectangles(), expectedMembers);
}

} // namespace nitro