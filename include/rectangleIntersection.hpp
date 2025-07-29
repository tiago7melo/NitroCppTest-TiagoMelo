#ifndef NITRO_INTERSECTION_HPP
#define NITRO_INTERSECTION_HPP

#include <optional>
#include <set>
#include "rectangle.hpp"    

namespace nitro {
class RectangleIntersection {
  public:
    RectangleIntersection(Rectangle shape, std::set<Rectangle::ID> intersectingRectangles);

    Rectangle getShape() const;
    std::set<Rectangle::ID> getIntersectingRectangles() const;

  private:
    Rectangle shape;
    std::set<Rectangle::ID> intersectingRectangles;
};

} // namespace nitro

#endif // NITRO_INTERSECTION_HPP