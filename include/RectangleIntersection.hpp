#ifndef NITRO_INTERSECTION_HPP
#define NITRO_INTERSECTION_HPP

#include "Canvas.hpp"
#include "Rectangle.hpp"
#include <optional>
#include <set>

#ifdef TEST
#include <gtest/gtest.h>
#endif

namespace nitro {
/* RectangleIntersection specifically interoperates with information stored in Canvas.
   A RectangleIntersection can only be created through Canvas intersection functions.
   A RectangleIntersection stores IDs of intersecting rectangles and the shape of the intersection.
   To get the shape of the intersecting rectangles, the Canvas::getRectangleAtIndex() function is required. */
class Canvas::RectangleIntersection {
	public:
		/* Constructors, Destructors */
		// Anyone can copy or move a RectangleIntersection
		RectangleIntersection(const RectangleIntersection &) = default;
		RectangleIntersection(RectangleIntersection &&) = default;
		RectangleIntersection &operator=(const RectangleIntersection &) = default;
		RectangleIntersection &operator=(RectangleIntersection &&) = default;
		~RectangleIntersection() = default;

		/* Operators */
		// implement strict weak ordering, requirement of std::set
		bool operator<(const RectangleIntersection &other) const {
			if (this->getIntersectingRectangles().size() != other.getIntersectingRectangles().size()) {
				return this->getIntersectingRectangles().size() < other.getIntersectingRectangles().size();
			}
			return this->getIntersectingRectangles() < other.getIntersectingRectangles();
		}

		/* Getters and Setters */
		Rectangle getShape() const;
		std::set<Rectangle::ID> getIntersectingRectangles() const;
		Rectangle::ID getRectIdAtIndex(size_t index) const;

		/* Functions */
		std::string toString() const;

	private:
		friend class Canvas;
		/* Private Constructor*/
		// Only Canvas can create a RectangleIntersection through its intersection functions
		RectangleIntersection(const Rectangle &shape, const std::set<Rectangle::ID> &members);

		/* Internal Members */
		Rectangle shape;
		std::set<Rectangle::ID> intersectingRectangles;

		/* For Testing */
#ifdef TEST
		friend class RectangleIntersectionTest;
		FRIEND_TEST(RectangleIntersectionTest, TestRectangleIntersectionSetOrdering);
		FRIEND_TEST(RectangleIntersectionTest, TestIntersectionAbstraction);
		FRIEND_TEST(RectangleIntersectionTest, GetIndexOutOfBounds);
#endif
};

} // namespace nitro
#endif // NITRO_INTERSECTION_HPP