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

        /* Constructors, Destructors*/
        //TODO: is this constructor even worth it? why not just restrict to fromJSON?
        RectangleSet(const std::set<Rectangle> &rectangles);

        /* Getters and Setters */
        size_t getSize() const;
        std::set<Rectangle> getRectangles() const;
        Rectangle getRectangleAtIndex(size_t index) const;

        /* Operations */
        std::optional<std::set<RectangleIntersection>> intersectPairwise();
        const std::vector<RectangleIntersection> intersectAll();
        static std::optional<std::set<Rectangle>> fromJSON(std::string json, size_t maxRectangles); //TODO: change to json structure
        std::string toHumanReadableOutput() const;

        /* Static Error Messages */
        static const std::string outOfRangeErrorMsg;
    private:
        /* Internal Member Functions*/
        std::optional<std::set<RectangleIntersection>> determinePairwiseIntersections();
        std::optional<std::set<RectangleIntersection>> determineAllIntersections(const std::set<RectangleIntersection> &pairwiseIntersections);

        /* Member Variables */
        std::set<Rectangle> rectangles;

        /* For Testing */
        friend class RectangleSetTest;
        FRIEND_TEST(RectangleSetTest, PairwiseIntersectionsBaseCase);
        FRIEND_TEST(RectangleSetTest, PairwiseIntersectionsNoIntersections);
        FRIEND_TEST(RectangleSetTest, PairwiseIntersectionsOneIntersection);
        FRIEND_TEST(RectangleSetTest, PairwiseIntersectionsIntersectionTwoOverlappingRects);
        FRIEND_TEST(RectangleSetTest, PairwiseIntersectionsCocentricRectangles);
        FRIEND_TEST(RectangleSetTest, PairwiseIntersectionsIntersectionOneRectangle);
        FRIEND_TEST(RectangleSetTest, PairwiseIntersectionsIntersectionZeroRectangles);
};

} // namespace nitro
#endif // NITRO_RECTANGLESET_HPP