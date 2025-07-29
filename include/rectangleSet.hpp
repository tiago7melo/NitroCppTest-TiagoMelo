#ifndef NITRO_RECTANGLESET_HPP
#define NITRO_RECTANGLESET_HPP

#include <string>
#include <optional>
#include <vector>
#include <set>
#include "rectangle.hpp" 
#include "rectangleIntersection.hpp"

namespace nitro {

struct RectangleComparator {
    bool operator()(const Rectangle& rectangle1, const Rectangle& rectangle2) const {
        // implement strict weak ordering, requirement of std::set
        return rectangle1.getId() < rectangle2.getId();
    }
};
    
class RectangleSet {
    public:
        //TODO: is this constructor even worth it? why not just restrict to fromJSON?
        RectangleSet(const std::set<Rectangle, RectangleComparator> &rectangles);

        std::optional<std::vector<RectangleIntersection>> intersectAll();
        std::set<Rectangle, RectangleComparator> getRectangles() const;
        
        static std::optional<std::set<Rectangle>> fromJSON(std::string json, size_t maxRectangles); //TODO: change to json structure
        
    private:
        std::vector<std::vector<Rectangle::ID>> calculateAllSubsets(size_t maxRectangles);
        void subsetRecursion(Rectangle::ID start, Rectangle::ID max, size_t minSize,
                             std::vector<Rectangle::ID> &subset, 
                             std::vector<std::vector<Rectangle::ID>> &result);

        std::set<Rectangle, RectangleComparator> rectangles;
        int size;
};

} // namespace nitro
#endif // NITRO_RECTANGLESET_HPP