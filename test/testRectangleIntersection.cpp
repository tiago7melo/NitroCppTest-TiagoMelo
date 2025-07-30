#include <gtest/gtest.h>
#include "rectangle.hpp"
#include "rectangleSet.hpp"
#include "rectangleIntersection.hpp"

namespace nitro {

TEST(RectangleIntersectionTest, TestRectangleIntersectionSetOrdering) {
    std::set<RectangleIntersection> intersections;

    Rectangle s1r1{1, {100, 100}, 250, 80};
    Rectangle s1r2{3, {140, 160}, 250, 100};
    Rectangle interRet1 = Rectangle::intersection(s1r1, s1r2).value();
    RectangleIntersection intersection1{interRet1, {s1r1.getId(), s1r2.getId()}};
    intersections.insert(intersection1);

    Rectangle s2r1{1, {100, 100}, 250, 80};
    Rectangle s2r2{4, {160, 140}, 350, 190};
    Rectangle intersection = Rectangle::intersection(s2r1, s2r2).value();
    RectangleIntersection intersection2{interRet1, {s2r1.getId(), s2r2.getId()}};
    intersections.insert(intersection2);

    ASSERT_EQ(intersection1.atIndex(0), 1);
    ASSERT_EQ(intersection1.atIndex(1), 3);

    ASSERT_EQ(intersection2.atIndex(0), 1);
    ASSERT_EQ(intersection2.atIndex(1), 4);

    ASSERT_TRUE(intersection1 < intersection2);
}

} // namespace nitro