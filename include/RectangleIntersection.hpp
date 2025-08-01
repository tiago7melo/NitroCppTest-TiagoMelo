#ifndef NITRO_INTERSECTION_HPP
#define NITRO_INTERSECTION_HPP

#include "Canvas.hpp"
#include "Rectangle.hpp"
#include <optional>
#include <set>

namespace nitro {

/* Rectangle Intersection specifically interoperates with information stored in
   Canvas For identifying the IDs of intersecting rectangles, it is dependent on
   the Canvas abstraction*/
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

		/* Static Error Messages */
		static const std::string outOfRangeErrorMsg;

	private:
		/* Internal Members */
		Rectangle shape;
		std::set<Rectangle::ID> intersectingRectangles; // TODO: rename to "members"
		                                                // (of the intersection) ?
};

} // namespace nitro
#endif // NITRO_INTERSECTION_HPP