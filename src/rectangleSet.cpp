#include <stdexcept>
#include "rectangleSet.hpp"
#include <iostream>

namespace nitro {

const std::string RectangleSet::outOfRangeErrorMsg = "Index out of range";

RectangleSet::RectangleSet(const std::set<Rectangle> &input) : rectangles{input} {}
std::set<Rectangle> RectangleSet::getRectangles() const {
    return rectangles;
}

size_t RectangleSet::getSize() const {
    return rectangles.size();
}

Rectangle RectangleSet::atIndex(size_t index) const {
    if(index >= rectangles.size()) {
        throw::std::out_of_range(RectangleSet::outOfRangeErrorMsg);
    }

    auto it = rectangles.begin();
    std::advance(it, index);
    return *it;
}

std::optional<std::set<RectangleIntersection>> RectangleSet::determinePairwiseIntersections() {
    std::set<RectangleIntersection> result; //TODO: do we need to use a set here?
    for(size_t i = 0; i < this->rectangles.size(); i++) {
        for(size_t j = i + 1; j < this->rectangles.size(); j++) {
            try {
                Rectangle rectangle1 = this->atIndex(i);
                Rectangle rectangle2 = this->atIndex(j);
                std::optional<Rectangle> intersection = Rectangle::intersection(rectangle1, rectangle2);
                if (intersection.has_value()) {
                    RectangleIntersection rectangleIntersection{intersection.value(), {rectangle1.getId(), rectangle2.getId()}};
                    result.insert(rectangleIntersection);
                }
            }
            catch (const std::exception& e){
                // TODO: deal with a bad rectangle creation in the intersection.
                // TODO: is this possible? maybe just better to make sure that the rectangles are valid
                // TODO: if we don't need to deal with it, just remove the try catch
                std::cout << e.what() << '\n';
            }
        }
    } 
    
    return result.empty() ? std::nullopt : std::make_optional(result);
}

std::optional<std::set<RectangleIntersection>> RectangleSet::determineHigherOrderIntersections() {
    return std::nullopt;
}

} // namespace nitros