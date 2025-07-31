#include <stdexcept>
#include "rectangleIntersection.hpp"

namespace nitro {

const std::string Canvas::RectangleIntersection::outOfRangeErrorMsg = "Index out of range";

Canvas::RectangleIntersection::RectangleIntersection(const Rectangle &shape, const std::set<Rectangle::ID> &members)
    : shape{shape}, intersectingRectangles{members} {}
    
Rectangle Canvas::RectangleIntersection::getShape() const { 
    return shape; 
}

std::set<Rectangle::ID> Canvas::RectangleIntersection::getIntersectingRectangles() const { 
    return intersectingRectangles; 
}

Rectangle::ID Canvas::RectangleIntersection::getRectIdAtIndex(size_t index) const {
        if(index >= intersectingRectangles.size()) {
            throw::std::out_of_range(Canvas::RectangleIntersection::outOfRangeErrorMsg);
        }

        auto it = intersectingRectangles.begin();
        std::advance(it, index);
        return *it;
}

} // namespace nitro