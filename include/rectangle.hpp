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
        using ID = uint32_t;
        typedef struct {
            Vertex bottomLeft;
            Vertex bottomRight;
            Vertex topLeft;
            Vertex topRight;
        } Vertices;

        Rectangle(ID id, Vertex topLeft, uint32_t width, uint32_t height);
        ~Rectangle() = default;

        ID getId() const;
        void setId(ID id);
        Vertices getVertices() const; 
        uint32_t getWidth() const;
        uint32_t getHeight() const;

        static std::optional<Rectangle> intersection(const Rectangle &rectangle1, const Rectangle &rectangle2);
        
        static const std::string vertexDefErrorMsg;
        static const std::string underflowErrorMsg;
        static const std::string overflowErrorMsg;
        static const std::string canvasXBoundExceededErrorMsg;
        static const std::string canvasYBoundExceededErrorMsg;
        static const std::string invalidIdErrorMsg;

    private:
        static bool validateVertices(const Vertex &bottomLeft, const Vertex &bottomRight, 
                                     const Vertex &topLeft, const Vertex &topRight);

        ID id;
        Vertices vertices;
        uint32_t width;
        uint32_t height;
};

} // namespace nitro
#endif // NITRO_RECTANGLE_HPP