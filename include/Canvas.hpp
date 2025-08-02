#ifndef NITRO_CANVAS_HPP
#define NITRO_CANVAS_HPP

#include "Rectangle.hpp"
#include <optional>
#include <set>
#include <string>
#include <vector>

#ifdef TEST
#include <gtest/gtest.h>
#endif

namespace nitro {

class Canvas {
	public:
		/* Nested Classes */
		class RectangleIntersection;

		/* Constructors, Destructors*/
		Canvas(const std::vector<Rectangle> &input);

		/* Getters and Setters */
		size_t getRectangleCount() const;
		std::set<Rectangle> getRectangles() const;
		Rectangle getRectangleAtIndex(size_t index) const;

		/* Operations */
		const std::vector<RectangleIntersection> intersectAll();
		std::string toString() const;

	private:
		/* Internal Member Functions*/
		std::optional<std::set<RectangleIntersection>> determinePairwiseIntersections();
		std::optional<std::set<RectangleIntersection>>
		determineAllIntersections(const std::set<RectangleIntersection> &pairwiseIntersections);

		/* Member Variables */
		std::set<Rectangle> rectangles;

		/* For Testing */
#ifdef TEST
		friend class CanvasTest;
		FRIEND_TEST(CanvasTest, PairwiseIntersectionsBaseCase);
		FRIEND_TEST(CanvasTest, PairwiseIntersectionsNoIntersections);
		FRIEND_TEST(CanvasTest, PairwiseIntersectionsOneIntersection);
		FRIEND_TEST(CanvasTest, PairwiseIntersectionTwoOverlappingRects);
		FRIEND_TEST(CanvasTest, PairwiseIntersectionsCocentricRectangles);
		FRIEND_TEST(CanvasTest, PairwiseIntersectionOneRectangle);
		FRIEND_TEST(CanvasTest, PairwiseIntersectionZeroRectangles);
#endif
};

} // namespace nitro
#endif // NITRO_CANVAS_HPP