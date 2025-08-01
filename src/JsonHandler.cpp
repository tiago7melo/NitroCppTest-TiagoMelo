#include "JsonHandler.hpp"
#include "Rectangle.hpp"
#include <filesystem>

namespace nitro {

using json = nlohmann::json;

JsonHandler::JsonHandler() {
}

JsonHandler::JsonHandler(const std::string &path) {
	loadFile(path);
}

bool JsonHandler::valid() const {
	return fileValid;
}

bool JsonHandler::loadFile(const std::string &filePath) {
	this->fileValid = false;

	if (std::filesystem::is_directory(filePath)) {
		throw std::invalid_argument("Path is a directory, not a file:  " + filePath);
	}

	std::ifstream file(filePath);

	if (!std::filesystem::exists(filePath)) {
		throw std::runtime_error("File does not exist:  " + filePath);
	}

	if (!file.is_open()) {
		throw std::runtime_error("Could not open file:  " + filePath);
	}

	if (file.peek() == std::ifstream::traits_type::eof()) {
		throw std::runtime_error("File is empty:  " + filePath);
	}

	try {
		jsonFile = json::parse(file);
		fileValid = true;
	} catch (const json::parse_error &e) {
		throw std::runtime_error("Could not parse JSON at  " + filePath + ": " + e.what());
	} catch (const std::exception &e) {
		throw std::runtime_error("Unexpected error parsing JSON at  " + filePath + ": " + e.what());
	}

	file.close();
	this->filePath = filePath;
	return this->fileValid;
}

std::string JsonHandler::getFilePath() const {
	return this->filePath;
}

std::optional<json> JsonHandler::getArray(const std::string &key) const {
	if (!this->valid()) {
		throw std::runtime_error("Trying to perform operation on invalid JSON File");
	}

	if (!jsonFile.contains(key)) {
		throw std::runtime_error("JSON File does not contain key: " + key);
	}

	if(!jsonFile.at(key).is_array()) {
		throw std::runtime_error("JSON Object at key [" + key + "] is not an array");
	}

	if (jsonFile.contains(key) and jsonFile.at(key).is_array()) {
		return jsonFile.at(key);
	}

	return std::nullopt;
}

template <typename T> 
std::optional<T> JsonHandler::unmarshal(json j) {
	// compiler won't even let it reach this throw
	throw std::invalid_argument("Unmarshal not implemented for type");
}

template <> 
std::optional<Rectangle> JsonHandler::unmarshal(json j) {
	if (j.contains("x") && j["x"].is_number_integer() && j.contains("y") && j["y"].is_number_integer() &&
	    j.contains("w") && j["w"].is_number_integer() && j.contains("h") && j["h"].is_number_integer()) {
		return Rectangle(Rectangle::ID_UNDEFINED, {j["x"].get<int>(), j["y"].get<int>()},
												   j["w"].get<int>(), j["h"].get<int>());
	} else {
		throw std::runtime_error("JSON Object does not define a rectangle");
	}

	return std::nullopt;
}

template <> 
std::optional<std::vector<Rectangle>> JsonHandler::unmarshal(json j) {
	if(!j.is_array()) {
		throw std::runtime_error("JSON Object is not an array");
	}
	
	//TODO: add max rectangles checks
	std::vector<Rectangle> rects;
	for (auto jsonObject : j ) {
		std::optional<Rectangle> r = unmarshal<Rectangle>(jsonObject);
		if (r.has_value()) {
			rects.push_back(r.value());
		}
	}

	return rects.empty() ? std::nullopt : std::make_optional(rects);
}

} // namespace nitro
