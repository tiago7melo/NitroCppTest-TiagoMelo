#include "jsonHandler.hpp"

namespace nitro {

using json = nlohmann::json;

const std::invalid_argument JsonHandler::fileEmptyException("Loaded JSON file is empty");
const std::string JsonHandler::fileLoadingErrorMsg = "Could not load JSON file";
const std::string JsonHandler::keyNotFoundErrorMsg = "Key not found in JSON";

JsonHandler::JsonHandler() {
}

JsonHandler::JsonHandler(const std::string &path) {
	loadFile(path);
}

bool JsonHandler::valid() const {
	return ((fileLoaded) ? !jsonFile.empty() : false);
}

bool JsonHandler::loadFile(const std::string &filePath) {
	fileLoaded = false;
	std::ifstream file(filePath);

	if (!file.is_open()) {
		throw std::invalid_argument(JsonHandler::fileLoadingErrorMsg + ":  " + filePath);
	}

	if (file.peek() == std::ifstream::traits_type::eof()) {
		throw JsonHandler::fileEmptyException;
	}

	jsonFile = json::parse(file);
	fileLoaded = true;

	return fileLoaded;
}

// TODO: templates?
std::optional<json> JsonHandler::getArray(const std::string &key) {
	// TODO: this
	return std::nullopt;
}

std::optional<json> JsonHandler::getValueJson(const std::string &key) {
	std::optional<json> retVal{};
	if (not jsonFile.empty() and jsonFile.contains(key)) {
		retVal = jsonFile.at(key).template get<json>();
	}
	return retVal;
}

std::optional<int> JsonHandler::getValueInt(const std::string &key) {
	std::optional<int> retVal{};
	if (not jsonFile.empty() and jsonFile.contains(key)) {
		retVal = jsonFile.at(key).template get<int>();
	}
	return retVal;
}
} // namespace nitro
