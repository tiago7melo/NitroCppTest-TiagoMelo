#include <stdexcept>
#include <limits>
#include "rectangle.hpp"

namespace nitro {
    
//TODO: move generic error msgs to separate file?
const std::string Rectangle::vertexDefErrorMsg = "Vertex definition error";
const std::string Rectangle::underflowErrorMsg = "Underflow error";
const std::string Rectangle::overflowErrorMsg = "Overflow error";
const std::string Rectangle::canvasXBoundExceededErrorMsg = "Rectangle exceeds canvas X bounds";
const std::string Rectangle::canvasYBoundExceededErrorMsg = "Rectangle exceeds canvas Y bounds";
const std::string Rectangle::accessEmptyRectangleErrorMsg = "Trying to access elements of empty rectangle";
const std::string Rectangle::accessInvalidRectangleErrorMsg = "Trying to access elements of invalid rectangle";

Rectangle::Rectangle() : m_empty(true), m_valid(false) {
}

//TODO: only support this constructor if it improves the readability
// otherwise we need to maintain all the sanity checks for something that isn't being used
//TODO: can also consider just a constructor with two points: topLeft and bottomRight. more robust and shorter to
// Rectangle::Rectangle(Vertex2D bottomLeft, Vertex2D bottomRight, Vertex2D topLeft, Vertex2D topRight) {
//     if (!Rectangle::validateVertices(bottomLeft, bottomRight, topLeft, topRight)) {
//         throw std::invalid_argument(Rectangle::vertexDefErrorMsg);
//     }
//     vertices.bottomLeft = bottomLeft;
//     vertices.bottomRight = bottomRight;
//     vertices.topLeft = topLeft;
//     vertices.topRight = topRight;
//     m_empty = false;
//     m_valid = true;
// }

Rectangle::Rectangle(Vertex2D topLeft, uint32_t width, uint32_t height) {
    // overflow, underflow checks
    const int maxInt = static_cast<uint32_t>(std::numeric_limits<int>::max());
    if (width > maxInt || height > maxInt) {
        throw std::overflow_error(Rectangle::overflowErrorMsg);
    }

    if (width <= 0 || height <= 0) {
        throw std::overflow_error(Rectangle::underflowErrorMsg);
    }

    if(topLeft.x > maxInt - static_cast<int>(width)) {
        throw std::overflow_error(Rectangle::canvasXBoundExceededErrorMsg);
    }

    if(topLeft.y < maxInt + static_cast<int>(height)) {
        throw std::underflow_error(Rectangle::canvasYBoundExceededErrorMsg);
    }
    
    vertices.topLeft = topLeft;
    vertices.bottomLeft = {topLeft.x, topLeft.y - static_cast<int>(height)};
    vertices.topRight = {topLeft.x + static_cast<int>(width), topLeft.y};
    vertices.bottomRight = {vertices.topRight.x, vertices.bottomLeft.y};

    if (!Rectangle::validateVertices(vertices.bottomLeft, vertices.bottomRight, vertices.topLeft, vertices.topRight)) {
        throw std::invalid_argument(Rectangle::vertexDefErrorMsg);
    }

    m_empty = false;
    m_valid = true;
    this->width = width;
    this->height = height;
}   

const bool Rectangle::empty() {
    return m_empty;
}

const bool Rectangle::valid() {
    return m_valid;
}

const Rectangle::Vertices Rectangle::getVertices() {
    if(empty()) {
        throw std::runtime_error(Rectangle::accessEmptyRectangleErrorMsg);
    }
    //TODO: Should you be able to still get the information from an invalid rectangle?
    return vertices;
}

const uint32_t Rectangle::getWidth() {
    if(empty()) {
        throw std::runtime_error(Rectangle::accessEmptyRectangleErrorMsg);
    }
    //TODO: Should you be able to still get the information from an invalid rectangle?
    return width;
}

const uint32_t Rectangle::getHeight() {
    if(empty()) {
        throw std::runtime_error(Rectangle::accessEmptyRectangleErrorMsg);
    }
    //TODO: Should you be able to still get the information from an invalid rectangle?
    return height;
}

bool Rectangle::validateVertices(const Vertex2D &bottomLeft, const Vertex2D &bottomRight, 
                                 const Vertex2D &topLeft, const Vertex2D &topRight) {
    return  bottomLeft.y == bottomRight.y &&
            bottomLeft.x == topLeft.x &&
            bottomRight.x == topRight.x &&
            topLeft.y == topRight.y &&
            bottomLeft.x < topRight.x &&
            bottomLeft.y < topRight.y;
}

} //namespace nitro