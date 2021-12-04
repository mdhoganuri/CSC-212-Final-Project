#include <iostream>
#include "Timer.h"

int main() {
	Timer test;
	
	test.start();

	for (int i = 0; i < 500; i++) {
		std::cout << i;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	
	test.stop();
	std::cout << test.getDuration() << std::endl;

	return 0;
}