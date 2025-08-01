#ifndef NITRO_RECTANGLE_HPP
#define NITRO_RECTANGLE_HPP

#include "Vertex.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace nitro {

class Rectangle {
	public:
		/* Defines */
		using ID = uint32_t;
		static const ID ID_UNDEFINED = -1;

		typedef struct {
				Vertex bottomLeft;
				Vertex bottomRight;
				Vertex topLeft;
				Vertex topRight;
		} Vertices;

		/* Constructors, Destructors */
		Rectangle(ID id, Vertex topLeft, uint32_t width, uint32_t height);
		~Rectangle() = default;

		/* Operators */
		// implement strict weak ordering, requirement of std::set
		bool operator<(const Rectangle &other) const {
			return this->getId() < other.getId();
		}

		// implement equality
		bool operator==(const Rectangle &other) const {
			return this->getVertices().topLeft.x == other.getVertices().topLeft.x &&
			       this->getVertices().topLeft.y == other.getVertices().topLeft.y &&
			       this->getWidth() == other.getWidth() && this->getHeight() == other.getHeight();
		}

		/* Getters and Setters */
		ID getId() const;
		void setId(ID id);
		Vertices getVertices() const;
		uint32_t getWidth() const;
		uint32_t getHeight() const;

		/* Functions */
		static std::optional<Rectangle> intersection(const Rectangle &rectangle1, const Rectangle &rectangle2);
		std::optional<Rectangle> intersect(const Rectangle &rectangle);

	private:
		/* Internal Functions */
		static bool validateVertices(const Vertex &bottomLeft, const Vertex &bottomRight, const Vertex &topLeft,
		                             const Vertex &topRight);

		/* Internal Members */
		ID id;
		Vertices vertices;
		uint32_t width;
		uint32_t height;
};

} // namespace nitro
#endif // NITRO_RECTANGLE_HPP