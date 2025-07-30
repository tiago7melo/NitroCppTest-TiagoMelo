#include <stdexcept>
#include "rectangleIntersection.hpp"

namespace nitro {

const std::string RectangleIntersection::outOfRangeErrorMsg = "Index out of range";

RectangleIntersection::RectangleIntersection(const Rectangle &shape, const std::set<Rectangle::ID> &members)
    : shape{shape}, intersectingRectangles{members} {}
    
Rectangle RectangleIntersection::getShape() const { 
    return shape; 
}

std::set<Rectangle::ID> RectangleIntersection::getIntersectingRectangles() const { 
    return intersectingRectangles; 
}

Rectangle::ID RectangleIntersection::atIndex(size_t index) const {
        if(index >= intersectingRectangles.size()) {
            throw::std::out_of_range(RectangleIntersection::outOfRangeErrorMsg);
        }

        auto it = intersectingRectangles.begin();
        std::advance(it, index);
        return *it;
}

} // namespace nitro