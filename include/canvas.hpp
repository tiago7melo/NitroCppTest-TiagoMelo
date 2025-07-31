#ifndef NITRO_CANVAS_HPP
#define NITRO_CANVAS_HPP

#include <string>
#include <optional>
#include <vector>
#include <set>
#include "rectangle.hpp" 
#include "rectangleIntersection.hpp"
#include <gtest/gtest.h>

namespace nitro {
    
class Canvas {
    public:
        /* Constructors, Destructors*/
        //TODO: is this constructor even worth it? why not just restrict to fromJSON?
        Canvas(const std::set<Rectangle> &rectangles);

        /* Getters and Setters */
        size_t getSize() const;
        std::set<Rectangle> getRectangles() const;
        Rectangle getRectangleAtIndex(size_t index) const;

        /* Operations */
        const std::vector<RectangleIntersection> intersectAll();
        static std::optional<std::set<Rectangle>> fromJSON(std::string json, size_t maxRectangles); //TODO: change to json structure
        std::string toString() const;

        /* Static Error Messages */
        static const std::string outOfRangeErrorMsg;
    private:
        /* Internal Member Functions*/
        std::optional<std::set<RectangleIntersection>> determinePairwiseIntersections();
        std::optional<std::set<RectangleIntersection>> determineAllIntersections(const std::set<RectangleIntersection> &pairwiseIntersections);

        /* Member Variables */
        std::set<Rectangle> rectangles;

        /* For Testing */
        friend class CanvasTest;
        FRIEND_TEST(CanvasTest, PairwiseIntersectionsBaseCase);
        FRIEND_TEST(CanvasTest, PairwiseIntersectionsNoIntersections);
        FRIEND_TEST(CanvasTest, PairwiseIntersectionsOneIntersection);
        FRIEND_TEST(CanvasTest, TestPairwiseIntersectionTwoOverlappingRects);
        FRIEND_TEST(CanvasTest, PairwiseIntersectionsCocentricRectangles);
        FRIEND_TEST(CanvasTest, TestPairwiseIntersectionOneRectangle);
        FRIEND_TEST(CanvasTest, TestPairwiseIntersectionZeroRectangles);
};

} // namespace nitro
#endif // NITRO_CANVAS_HPP