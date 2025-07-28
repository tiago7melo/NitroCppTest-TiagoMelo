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

TEST(RectangleTest, TestCreateEmptyRectangle) {
    Rectangle rectangle{};
    ASSERT_TRUE(rectangle.empty());
}

TEST(RectangleTest, DestructRectangles) {
    std::unique_ptr<Rectangle> rectangle = std::make_unique<Rectangle>();
    ASSERT_TRUE(rectangle->empty());
    rectangle.reset();
    ASSERT_FALSE(rectangle);
}

TEST(RectangleTest, RectangleNotEmptyAfterCopyingToIt) {
    Rectangle rectangle{};
    ASSERT_TRUE(rectangle.empty());
    Rectangle rectangle2{{1, 1}, 4, 2};
    rectangle = rectangle2;
    ASSERT_FALSE(rectangle.empty());
    ASSERT_TRUE(rectangle.getVertices().bottomLeft.x == 1);
}

TEST(RectangleTest, CreateFromTopLeftIsNotEmpty) {
    Rectangle rectangle{{1, 1}, 4, 2};
    ASSERT_FALSE(rectangle.empty());
}

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
    Rectangle rectangle{{1, 1}, 4, 3};
    ASSERT_EQ(rectangle.getVertices().topLeft.x, 1);
    ASSERT_EQ(rectangle.getVertices().topLeft.y, 1);
    ASSERT_EQ(rectangle.getWidth(), 4);
    ASSERT_EQ(rectangle.getHeight(), 3);
}

TEST(RectangleTest, CreateFromTopLeftGeneratesCorrectVertices) {
    Rectangle rectangle{{1, 1}, 4, 3};
    ASSERT_EQ(rectangle.getVertices().bottomLeft.x, 1);
    ASSERT_EQ(rectangle.getVertices().bottomLeft.y, -2);
    ASSERT_EQ(rectangle.getVertices().bottomRight.x, 5);
    ASSERT_EQ(rectangle.getVertices().bottomRight.y, -2);
    ASSERT_EQ(rectangle.getVertices().topLeft.x, 1);
    ASSERT_EQ(rectangle.getVertices().topLeft.y, 1);
    ASSERT_EQ(rectangle.getVertices().topRight.x, 5);
    ASSERT_EQ(rectangle.getVertices().topRight.y, 1);
}

// TEST(RectangleTest, ConstructorChecksVertexValidity) {
//     std::string check = "";
//     try {
//         Rectangle rectangle{{1, 1}, {4, 2}, {1, 3}, {4, 3}};
//         // TODO: check if after creating invalid rectangle,  rectangle not empty but also not valid
//     } 
//     catch (const std::exception& e) {
//         check = e.what();
//     }
//     ASSERT_TRUE(check == Rectangle::vertexDefErrorMsg);
// }

TEST(RectangleTest, CantChangeVerticesAfterCreationDirectly) {
    Rectangle rectangle{{1, 1}, 4, 2};
    Rectangle::Vertices vertices = rectangle.getVertices();
    vertices.bottomLeft.x = 2;
    ASSERT_EQ(rectangle.getVertices().bottomLeft.x, 1);
}

TEST(RectangleTest, CantChangeWidthHeightAfterCreationDirectly) {
    Rectangle rectangle{{1, 1}, 4, 2};
    uint32_t width = rectangle.getWidth();
    uint32_t height = rectangle.getHeight();
    width = 2;
    height = 3;
    ASSERT_EQ(rectangle.getWidth(), 4);
    ASSERT_EQ(rectangle.getHeight(), 2);
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
    const int maxInt = static_cast<uint32_t>(std::numeric_limits<int>::max());
    std::string check = "";
    try {
        Rectangle rectangle{{maxInt - 40, 1}, 42, 1};
    } 
    catch (const std::exception& e) {
        check = e.what();
    }
    ASSERT_TRUE(check == Rectangle::canvasXBoundExceededErrorMsg);
}

TEST(RectangleTestFixture, HeightExceedsYBounds) {
    const int minInt = static_cast<uint32_t>(std::numeric_limits<int>::min());
    std::string check = "";
    try {
        Rectangle rectangle{{1, minInt + 40}, 1, 42};
    } 
    catch (const std::exception& e) {
        check = e.what();
    }
    ASSERT_TRUE(check == Rectangle::canvasYBoundExceededErrorMsg);
}