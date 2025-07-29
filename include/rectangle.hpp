#ifndef NITRO_RECTANGLE_HPP
#define NITRO_RECTANGLE_HPP

#include <string>
#include <optional>
#include <vector>
#include <cstdint>
#include "vertex.hpp"

namespace nitro {
    
class Rectangle {
    public:
        typedef struct {
            Vertex2D bottomLeft;
            Vertex2D bottomRight;
            Vertex2D topLeft;
            Vertex2D topRight;
        } Vertices;

        Rectangle(Vertex2D topLeft, uint32_t width, uint32_t height);
        ~Rectangle() = default;

        Vertices getVertices() const; 
        uint32_t getWidth() const;
        uint32_t getHeight() const;

        static std::optional<Rectangle> intersection(const Rectangle &rectangle1, const Rectangle &rectangle2);
        //TODO: intersect all subsets of rectangles
        static std::optional<std::vector<Rectangle>> intersectRectangleSet(const std::vector<Rectangle> &rectangles);
        
        static const std::string vertexDefErrorMsg;
        static const std::string underflowErrorMsg;
        static const std::string overflowErrorMsg;
        static const std::string canvasXBoundExceededErrorMsg;
        static const std::string canvasYBoundExceededErrorMsg;

    private:
        static bool validateVertices(const Vertex2D &bottomLeft, const Vertex2D &bottomRight, 
                                     const Vertex2D &topLeft, const Vertex2D &topRight);

        Vertices vertices;
        uint32_t width;
        uint32_t height;
};

} // namespace nitro
#endif // NITRO_RECTANGLE_HPP