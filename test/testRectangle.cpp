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
    std::unique_ptr<Rectangle> rectangle = std::make_unique<Rectangle>(Rectangle{{100, 100}, 250, 80});
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

TEST(RectangleTest, CreateFromTopLeftStoresInputCorrectly) {
    Rectangle rectangle{{100, 100}, 250, 80};
    ASSERT_EQ(rectangle.getVertices().topLeft.x, 100);
    ASSERT_EQ(rectangle.getVertices().topLeft.y, 100);
    ASSERT_EQ(rectangle.getWidth(), 250);
    ASSERT_EQ(rectangle.getHeight(), 80);
    Rectangle rectangle2{{140, 160}, 250, 100};
    ASSERT_EQ(rectangle2.getVertices().topLeft.x, 140);
    ASSERT_EQ(rectangle2.getVertices().topLeft.y, 160);
    ASSERT_EQ(rectangle2.getWidth(), 250);
    ASSERT_EQ(rectangle2.getHeight(), 100);
    
}

TEST(RectangleTest, CreateFromTopLeftGeneratesCorrectVertices) {
    Rectangle rectangle{{100, 100}, 250, 80};
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
    Rectangle rectangle{{100, 100}, 250, 80};
    Rectangle::Vertices vertices = rectangle.getVertices();
    vertices.bottomLeft.x = 2;
    ASSERT_EQ(rectangle.getVertices().bottomLeft.x, 100);
}

TEST(RectangleTest, CantChangeWidthHeightAfterCreationDirectly) {
    Rectangle rectangle{{100, 100}, 250, 80};
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
        Rectangle rectangle{{1, 1}, 0, 1};
    } 
    catch (const std::exception& e) {
        check = e.what();
    }
    ASSERT_TRUE(check == Rectangle::underflowErrorMsg);
}


TEST(RectangleTest, UnderflowHeight) {
    std::string check = "";
    try {
        Rectangle rectangle{{1, 1}, 1, 0};
    } 
    catch (const std::exception& e) {
        check = e.what();
    }
    ASSERT_TRUE(check == Rectangle::underflowErrorMsg);
}

TEST(RectangleTest, WidthExceedsXBounds) {
    const int maxInt = std::numeric_limits<uint32_t>::max();
    std::string check = "";
    try {
        Rectangle rectangle{{maxInt - 40, 1}, 42, 1};
    } 
    catch (const std::exception& e) {
        check = e.what();
    }
    ASSERT_TRUE(check == Rectangle::canvasXBoundExceededErrorMsg);
}

TEST(RectangleTest, HeightExceedsYBounds) {
    const int maxInt = std::numeric_limits<uint32_t>::max();
    std::string check = "";
    try {
        Rectangle rectangle{{1, maxInt - 40}, 1, 42};
    }  
    catch (const std::exception& e) {
        check = e.what();
    }
    ASSERT_TRUE(check == Rectangle::canvasYBoundExceededErrorMsg);
}

TEST(RectangleTest, TestSimpleIntersection) 
{
    Rectangle rectangle{{100, 100}, 250, 80};
    Rectangle rectangle2{{140, 160}, 250, 100};

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
    Rectangle rectangle{{100, 100}, 250, 80};
    Rectangle rectangle2{{500, 500}, 250, 100};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_FALSE(interRet.has_value());
}

TEST(RectangleTest, TestSimpleIntersectionFullOverlap) 
{
    Rectangle rectangle{{100, 100}, 250, 80};
    Rectangle rectangle2{{100, 100}, 250, 80};
    
    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    ASSERT_TRUE(interRet.has_value());
    Rectangle intersection = interRet.value();
    ASSERT_EQ(intersection.getVertices().topLeft.x, 100);
    ASSERT_EQ(intersection.getVertices().topLeft.y, 100);
    ASSERT_EQ(intersection.getWidth(), 250);
    ASSERT_EQ(intersection.getHeight(), 80);

}
//TODO: more intersection tests, preferably with visual plot
//TODO: test negative coordinate stuff