#include "Application.hpp"
#include <iostream>

int main(int argc, char **argv) {
	nitro::Application app(argc, argv);
	return app.run();
}