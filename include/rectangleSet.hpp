#ifndef NITRO_RECTANGLESET_HPP
#define NITRO_RECTANGLESET_HPP

#include <string>
#include <optional>
#include <vector>
#include <set>
#include "rectangle.hpp" 
#include "rectangleIntersection.hpp"
#include <gtest/gtest.h>

namespace nitro {
    
class RectangleSet {
    public:

        //TODO: is this constructor even worth it? why not just restrict to fromJSON?
        RectangleSet(const std::set<Rectangle> &rectangles);

        std::optional<std::vector<RectangleIntersection>> intersectAll();
        size_t getSize() const;
        std::set<Rectangle> getRectangles() const;
        Rectangle atIndex(size_t index) const;
        
        static std::optional<std::set<Rectangle>> fromJSON(std::string json, size_t maxRectangles); //TODO: change to json structure
        std::string toHumanReadableOutput() const;

        static const std::string outOfRangeErrorMsg;
    private:
        std::optional<std::set<RectangleIntersection>> determinePairwiseIntersections();
        std::optional<std::set<RectangleIntersection>> determineHigherOrderIntersections(const std::set<RectangleIntersection> &pairwiseIntersections);

        std::set<Rectangle> rectangles;

        /* For Testing */
        friend class RectangleSetTest;
        FRIEND_TEST(RectangleSetTest, TestPairwiseIntersections);
        FRIEND_TEST(RectangleSetTest, TestPairwiseIntersectionsNoIntersections);
        FRIEND_TEST(RectangleSetTest, TestPairwiseIntersectionsOneIntersection);
        FRIEND_TEST(RectangleSetTest, TestPairwiseIntersectionTwoOverlappingRects);
        FRIEND_TEST(RectangleSetTest, TestPairwiseIntersectionsCocentricRectangles);
};

} // namespace nitro
#endif // NITRO_RECTANGLESET_HPP