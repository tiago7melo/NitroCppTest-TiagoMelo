#include <gtest/gtest.h>
#include <limits>
#include "vertex.hpp"
#include "rectangle.hpp"

using namespace nitro;

//TODO: evaluate if we need a fixture
// class RectangleTestFixture : public ::testing::Test {
// protected:
//     void SetUp() override {
//     }

//     void TearDown() override {
//     }

//     int intMax = static_cast<uint32_t>(std::numeric_limits<int>::max());
//     int intMin = static_cast<uint32_t>(std::numeric_limits<int>::min());
// };

// TEST(RectangleTest, TestCreateEmptyRectangle) {
//     Rectangle rectangle{};
//     ASSERT_TRUE(rectangle.empty());
// }

TEST(RectangleTest, DestructRectangles) {
    std::unique_ptr<Rectangle> rectangle = std::make_unique<Rectangle>(Rectangle{1, {100, 100}, 250, 80});
    rectangle.reset();
    ASSERT_FALSE(rectangle);
}

// TEST(RectangleTest, RectangleNotEmptyAfterCopyingToIt) {
//     Rectangle rectangle{};
//     ASSERT_TRUE(rectangle.empty());
//     Rectangle rectangle2{{100, 100}, 250, 80};
//     rectangle = rectangle2;
//     ASSERT_FALSE(rectangle.empty());
//     ASSERT_EQ(rectangle.getVertices().bottomLeft.x, 100);
// }

// TEST(RectangleTest, CreateFromTopLeftIsNotEmpty) {
//     Rectangle rectangle{{100, 100}, 250, 80};
//     ASSERT_FALSE(rectangle.empty());
// }

// C++ shortcoming, NULL is 0 so this won't throw an except
// TEST(RectangleTest, CreateFromTopLeftPassNULLCoordinates) {
//     std::string check = "";
//     try {
//         Rectangle rectangle{{NULL, NULL}, 4, 2};
//     } 
//     catch (const std::exception& e) {
//         check = e.what();
//     }
//     std::cout << "Exception:" << check << std::endl;
//     ASSERT_TRUE(check == Rectangle::vertexDefErrorMsg);
// }

TEST(RectangleTest, IdCantBeZero) {
    std::string check = "";
    try {
        Rectangle rectangle{0, {100, 100}, 250, 80};
    } 
    catch (const std::exception& e) {
        check = e.what();
    }
    ASSERT_TRUE(check == Rectangle::invalidIdErrorMsg);
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
    ASSERT_TRUE(check == Rectangle::underflowErrorMsg);
}


TEST(RectangleTest, UnderflowHeight) {
    std::string check = "";
    try {
        Rectangle rectangle{1, {100, 100}, 250, 0};
    } 
    catch (const std::exception& e) {
        check = e.what();
    }
    ASSERT_TRUE(check == Rectangle::underflowErrorMsg);
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
    ASSERT_TRUE(check == Rectangle::canvasXBoundExceededErrorMsg);
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
    ASSERT_TRUE(check == Rectangle::canvasYBoundExceededErrorMsg);
}

TEST(RectangleTest, TestSimpleIntersection) 
{
    Rectangle rectangle{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {140, 160}, 250, 100};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());

    Rectangle intersection = interRet.value();
    ASSERT_EQ(intersection.getVertices().topLeft.x, 140);
    ASSERT_EQ(intersection.getVertices().topLeft.y, 160);
    ASSERT_EQ(intersection.getWidth(), 210);
    ASSERT_EQ(intersection.getHeight(), 20);
}

TEST(RectangleTest, TestSimpleIntersectionNoOverlap) 
{
    Rectangle rectangle{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {500, 500}, 250, 100};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_FALSE(interRet.has_value());
}

// TODO: Originally plotted with draw.io, need to add plots for clarity
TEST(RectangleTest, TestSimpleIntersectionFullOverlap) 
{
    Rectangle rectangle{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {100, 100}, 250, 80};
    
    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());
    Rectangle intersection = interRet.value();
    ASSERT_EQ(intersection.getVertices().topLeft.x, 100);
    ASSERT_EQ(intersection.getVertices().topLeft.y, 100);
    ASSERT_EQ(intersection.getWidth(), 250);
    ASSERT_EQ(intersection.getHeight(), 80);

}

TEST(RectangleTest, TestIntersectionTopLeftNegativeRectangleBisectedByXYAxis) 
{
    Rectangle rectangle{1, {-100, -100}, 250, 80};
    Rectangle rectangle2{2, {-140, -160}, 250, 100};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());

    Rectangle intersection = interRet.value();
    ASSERT_EQ(intersection.getVertices().topLeft.x, -100);
    ASSERT_EQ(intersection.getVertices().topLeft.y, -100);
    ASSERT_EQ(intersection.getWidth(), 210);
    ASSERT_EQ(intersection.getHeight(), 40);
}

TEST(RectangleTest, TestIntersectionTopLeftFullNegativeCoordinates) 
{
    Rectangle rectangle{1, {-430, -230 }, 250, 80};
    Rectangle rectangle2{2, {-390 , -170}, 250, 100};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());

    Rectangle intersection = interRet.value();
    ASSERT_EQ(intersection.getVertices().topLeft.x, -390);
    ASSERT_EQ(intersection.getVertices().topLeft.y, -170);
    ASSERT_EQ(intersection.getWidth(), 210);
    ASSERT_EQ(intersection.getHeight(), 20);
}

TEST(RectangleTest, TestIntersectionOneInsideTheOther) 
{
    Rectangle rectangle{1, {-410, -320}, 250, 220};
    Rectangle rectangle2{2, {-410 , -260}, 250, 100};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());

    Rectangle intersection = interRet.value();
    ASSERT_EQ(intersection.getVertices().topLeft.x, -410);
    ASSERT_EQ(intersection.getVertices().topLeft.y, -260);
    ASSERT_EQ(intersection.getWidth(), 250);
    ASSERT_EQ(intersection.getHeight(), 100);
}

TEST(RectangleTest, TestIntersectionOneAcrossTheOther) 
{
    Rectangle rectangle{1, {-410, -320}, 250, 220};
    Rectangle rectangle2{2, {-330 , -350}, 70, 270};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());

    Rectangle intersection = interRet.value();
    ASSERT_EQ(intersection.getVertices().topLeft.x, -330);
    ASSERT_EQ(intersection.getVertices().topLeft.y, -320);
    ASSERT_EQ(intersection.getWidth(), 70);
    ASSERT_EQ(intersection.getHeight(), 220);
}

TEST(RectangleTest, TestIntersectionRectangleTopLeftAtOrigin) 
{
    Rectangle rectangle{1, {0, 0}, 250 , 220};
    Rectangle rectangle2{2, {-280 , -190}, 310 , 250};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());

    Rectangle intersection = interRet.value();
    ASSERT_EQ(intersection.getVertices().topLeft.x, 0);
    ASSERT_EQ(intersection.getVertices().topLeft.y, 0);
    ASSERT_EQ(intersection.getWidth(), 30);
    ASSERT_EQ(intersection.getHeight(), 60);
}

TEST(RectangleTest, TestIntersectionAdjacentRectanglesNoIntersection) 
{
    Rectangle rectangle{1, {0, 0}, 250 , 220};
    Rectangle rectangle2{2, {-310 , -70}, 310 , 330};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_FALSE(interRet.has_value());
}