#include <stdexcept>
#include <limits>
#include "rectangle.hpp"
#include <iostream> //TODO: rm iostream later

namespace nitro {
    
const std::string Rectangle::vertexDefErrorMsg = "Vertex definition error";
const std::string Rectangle::underflowErrorMsg = "Underflow error";
const std::string Rectangle::overflowErrorMsg = "Overflow error";
const std::string Rectangle::canvasXBoundExceededErrorMsg = "Rectangle exceeds canvas X bounds";
const std::string Rectangle::canvasYBoundExceededErrorMsg = "Rectangle exceeds canvas Y bounds";
const std::string Rectangle::invalidIdErrorMsg = "Rectangle IDs must be > 0";

Rectangle::Rectangle(Rectangle::ID id, Vertex topLeft, uint32_t width, uint32_t height) {
    // overflow, underflow checks
    if (width == 0 || height == 0) {
        throw std::overflow_error(Rectangle::underflowErrorMsg);
    }

    const int64_t maxInt = std::numeric_limits<int>::max();
    if (static_cast<int64_t>(topLeft.x) > maxInt - static_cast<int64_t>(width)) {
        throw std::overflow_error(Rectangle::canvasXBoundExceededErrorMsg);
    }

    if(static_cast<int64_t>(topLeft.y) > maxInt - static_cast<int64_t>(height)) {
        throw std::overflow_error(Rectangle::canvasYBoundExceededErrorMsg);
    }
    
    // vertex calculation and validation
    vertices.topLeft = topLeft;
    vertices.bottomLeft = {topLeft.x, topLeft.y + static_cast<int>(height)};
    vertices.topRight = {topLeft.x + static_cast<int>(width), topLeft.y};
    vertices.bottomRight = {vertices.topRight.x, vertices.bottomLeft.y};

    if (!Rectangle::validateVertices(vertices.bottomLeft, vertices.bottomRight, vertices.topLeft, vertices.topRight)) {
        throw std::invalid_argument(Rectangle::vertexDefErrorMsg);
    }

    this->width = width;
    this->height = height;

    if(id == 0) {
        throw std::invalid_argument(Rectangle::invalidIdErrorMsg);
    }
    this->id = id;
}

Rectangle::ID Rectangle::getId() const{
    return id;
}

void Rectangle::setId(Rectangle::ID id) {
    // Allow setting the ID freely for a Rectangle
    // Canvas responsible for ensuring that IDs are unique
    this->id = id;
}

Rectangle::Vertices Rectangle::getVertices() const{
    return vertices;
}

uint32_t Rectangle::getWidth() const {
    return width;
}

uint32_t Rectangle::getHeight() const {
    return height;
}

bool Rectangle::validateVertices(const Vertex &bottomLeft, const Vertex &bottomRight, 
                                 const Vertex &topLeft, const Vertex &topRight) {
    return  bottomLeft.y == bottomRight.y &&
            bottomLeft.x == topLeft.x &&
            bottomRight.x == topRight.x &&
            topLeft.y == topRight.y &&
            bottomLeft.x < topRight.x &&
            bottomLeft.y > topRight.y;
}

std::optional<Rectangle> Rectangle::intersection(const Rectangle &rectangle1, const Rectangle &rectangle2) {
    Rectangle::Vertices r1Vertices = rectangle1.getVertices();
    Rectangle::Vertices r2Vertices = rectangle2.getVertices();

    const int interLeftEdge = std::max(r1Vertices.topLeft.x, r2Vertices.topLeft.x);
    const int interRightEdge = std::min(r1Vertices.topRight.x, r2Vertices.topRight.x);
    const int interTopEdge = std::max(r1Vertices.topLeft.y, r2Vertices.topLeft.y);
    const int interBottomEdge = std::min(r1Vertices.bottomLeft.y, r2Vertices.bottomLeft.y);
    
    if ((interLeftEdge < interRightEdge) && ( interBottomEdge > interTopEdge)) {
        Vertex topLeftVertexX = {interLeftEdge, interTopEdge};
        uint32_t width = static_cast<uint32_t>(interRightEdge - interLeftEdge);
        uint32_t height = static_cast<uint32_t>(interBottomEdge - interTopEdge);
        // RectangleIntersections will be  identified by the IDs of the intersecting rectangles
        // the Rectangle shape that composes the RectangleIntersection doesn't need a unique ID
        return Rectangle{1, topLeftVertexX, width, height}; 
    }

    return std::nullopt;
}

} //namespace nitro