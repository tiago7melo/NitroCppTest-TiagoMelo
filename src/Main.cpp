#include "Application.hpp"
#include <iostream>

int main(int argc, char **argv) {
	return nitro::Application{argc, argv}.run();
}