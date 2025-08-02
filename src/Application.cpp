#include "Application.hpp"

namespace nitro {

Application::Application(int argc, char **argv) : initialized(false), filePath(""), maxRectangles(DEFAULT_MAX_RECTS) {
	this->initialized = init(argc, argv);
}

// TODO: don't forget to try catch stuff
int Application::run() {
	if (!initialized) {
		return 1;
	}
	std::cout << "Hello World!\n";
	std::cout << "File: " << filePath << "\n";
	return 0;
}

bool Application::init(int argc, char **argv) {
	ErrorCode code = checkArgCount(argc);
	if (code != ErrorCode::Success) {
		reportError(code);
		printHelp();
		return false;
	}

	if (argc == 3) {
		code = parseMaxRects(argv[2]);
		if (code != ErrorCode::Success) {
			reportError(code);
			return false;
		}
	}

	std::string path = argv[1];

	code = parseFile(path);
	if (code != ErrorCode::Success) {
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
	if (path.size() < 5 || path.substr(path.size() - 5) != ".json") {
		return ErrorCode::InvalidFileExtension;
	}

	try {
		jsonHandler.loadFile(path);
		filePath = path;
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
		return ErrorCode::InvalidFile;
	}

	return ErrorCode::Success;
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
		case ErrorCode::InvalidFileExtension:
			std::cerr << "Error: File must have a .json extension.\n";
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