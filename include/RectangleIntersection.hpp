#ifndef NITRO_INTERSECTION_HPP
#define NITRO_INTERSECTION_HPP

#include "Canvas.hpp"
#include "Rectangle.hpp"
#include <optional>
#include <set>

namespace nitro {

/* RectangleIntersection specifically interoperates with information stored in Canvas.
   A RectangleIntersection is only created through Canvas functions.
   A RectangleIntersection stores IDs of intersecting rectangles and the shape of the intersection.
   To get the shape of the intersecting rectangles, the Canvas::getRectangleAtIndex() function is required. */
class Canvas::RectangleIntersection {
	public:
		/* Constructors, Destructors*/
		RectangleIntersection(const Rectangle &shape, const std::set<Rectangle::ID> &members);
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
		// TODO: rename to getMembers()?
		std::set<Rectangle::ID> getIntersectingRectangles() const;
		Rectangle::ID getRectIdAtIndex(size_t index) const;

		/* Functions */
		std::string toString() const;

	private:
		/* Internal Members */
		Rectangle shape;
		std::set<Rectangle::ID> intersectingRectangles; // TODO: rename to "members"
		                                                // (of the intersection) ?
};

} // namespace nitro
#endif // NITRO_INTERSECTION_HPP