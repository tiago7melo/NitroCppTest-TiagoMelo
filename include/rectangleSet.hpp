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
        //TODO: function to Intersect with the Intersections
        std::optional<std::set<RectangleIntersection>> determineHigherOrderIntersections();

        std::set<Rectangle> rectangles;

        friend class RectangleSetTest;
        FRIEND_TEST(RectangleSetTest, TestPairwiseIntersections);
};

} // namespace nitro
#endif // NITRO_RECTANGLESET_HPP