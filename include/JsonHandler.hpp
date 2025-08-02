#ifndef NITRO_JSONHANDLER_H
#define NITRO_JSONHANDLER_H

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

namespace nitro {

using json = nlohmann::json;

class JsonHandler { // TODO: JsonHandler : FileHander? instantiate a different one depending on the extension in the
	public:
		/* Constructor, Destructor */
		JsonHandler();
		explicit JsonHandler(const std::string &path);

		/* Getters */
		std::string getFilePath() const;

		/* Functions */
		bool valid() const;
		bool loadFile(const std::string &filePath);
		std::optional<json> getArray(const std::string &key, const size_t maxSize = 10) const;

		template <typename T> static std::optional<T> unmarshal(json j);

	private:
		/* Member Variables*/
		json jsonFile;
		std::string filePath;
		bool fileValid{false};
};

} // namespace nitro

#endif // NITRO_JSONHANDLER_
