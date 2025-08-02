#include "Application.hpp"
#include <optional>

namespace nitro {

Application::Application(int argc, char **argv) : initialized(false), filePath(""), maxRectangles(DEFAULT_MAX_RECTS) {
	this->initialized = init(argc, argv);
}

int Application::run() {
	if (!this->initialized) {
		return 1;
	}

	try {
		std::optional<std::vector<Rectangle>> rectangles = loadRectangles(this->maxRectangles);
		if (!rectangles.has_value()) {
			std::cerr << "Error: No rectangles were defined in the input.\n";
			return 1;
		}

		Canvas canvas{rectangles.value()};
		std::vector<Canvas::RectangleIntersection> intersections = canvas.intersectAll();

		printOutput(rectangles.value(), intersections);

	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}

	return 0;
}

bool Application::init(int argc, char **argv) {
	if (ErrorCode code = checkArgCount(argc); code != ErrorCode::Success) {
		reportError(code);
		printHelp();
		return false;
	}

	//TODO: checkArgCount should determine if this happens instead of doing another argcount check here
	if (argc == 3) {
		if (ErrorCode code = parseMaxRects(argv[2]); code != ErrorCode::Success) {
			reportError(code);
			return false;
		}
	}

	std::string path = argv[1];

	if (ErrorCode code = parseFile(path); code != ErrorCode::Success) {
		reportError(code);
		return false;
	}

	return true;
}

Application::ErrorCode Application::checkArgCount(int argc) const {
	if (argc < 2) {
		return ErrorCode::MissingPathArg;
	}

	if (argc > 3) {
		return ErrorCode::TooManyArguments;
	}

	return ErrorCode::Success;
}

Application::ErrorCode Application::parseMaxRects(const char *arg) {
	try {
		this->maxRectangles = static_cast<size_t>(std::stoull(arg));
	} catch (const std::exception &e) {
		return ErrorCode::InvalidSizeArg;
	}

	return ErrorCode::Success;
}

Application::ErrorCode Application::parseFile(const std::string &path) {
	try {
		jsonHandler.loadFile(path);
		filePath = path;
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
		return ErrorCode::InvalidFile;
	}

	return ErrorCode::Success;
}

std::optional<std::vector<Rectangle>> Application::loadRectangles(const size_t maxRectangles) const {
	std::optional<json> j = jsonHandler.getArray("rects", maxRectangles);
	if (!j.has_value()) {
		return std::nullopt;
	}

	std::optional<std::vector<Rectangle>> rects = JsonHandler::unmarshal<std::vector<Rectangle>>(j);
	return rects.has_value() ? rects : std::nullopt;
}

void Application::printOutput(const std::vector<Rectangle> &rectangles,
                              const std::vector<Canvas::RectangleIntersection> &intersections) const {
	std::cout << "Input:\n";
	if (rectangles.empty()) {
		std::cout << "   No rectangles have been defined.\n";
		return;
	}

	for (Rectangle rectangle : rectangles) {
		std::cout << "   " << rectangle.toString() << "\n";
	}

	std::cout << "\nIntersections:\n";
	if (intersections.empty()) {
		std::cout << "   No intersections were found.\n";
		return;
	}

	for (Canvas::RectangleIntersection intersection : intersections) {
		std::cout << "   " << intersection.toString() << "\n";
	}
}

void Application::printHelp() {
	std::cout << "Usage: ./rectangle_intersect <path/to/file.json> [max_rectangles]\n";
}

void Application::reportError(ErrorCode code) const {
	switch (code) {
		case ErrorCode::Success:
			break;
		case ErrorCode::MissingPathArg:
			std::cerr << "Error: Missing path to .json file.\n";
			break;
		case ErrorCode::TooManyArguments:
			std::cerr << "Error: Too many arguments. Usage: ./app <path.json> [optional_size]\n";
			break;
		case ErrorCode::InvalidFile:
			std::cerr << "Error: Failed to load the .json file.\n";
			break;
		case ErrorCode::InvalidSizeArg:
			std::cerr << "Error: Invalid size argument. Must be a non-negative integer.\n";
			break;
	}
}

} // namespace nitro