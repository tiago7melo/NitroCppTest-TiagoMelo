#ifndef NITRO_JSONHANDLER_H
#define NITRO_JSONHANDLER_H

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

namespace nitro {

using json = nlohmann::json;

class JsonHandler {
	public:
		JsonHandler();
		explicit JsonHandler(const std::string &path);
		bool valid() const;
		bool loadFile(const std::string &filePath);

		std::optional<json> getValueJson(const std::string &key);
		std::optional<json> getArray(const std::string &key);
		std::optional<int> getValueInt(const std::string &key);

		// TODO: choose which approach
		static const std::invalid_argument fileEmptyException;
		static const std::string keyNotFoundErrorMsg;
		static const std::string fileLoadingErrorMsg;

	private:
		json jsonFile;
		bool fileLoaded{false};
};

} // namespace nitro

#endif // NITRO_JSONHANDLER_H
