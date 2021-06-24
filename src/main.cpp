#include "Controller.h"
#include <stdlib.h>
#include <time.h>

int main() try
{
	Controller controller{};

	controller.run();
}
catch (std::exception& e)
{
	std::cout << e.what() << '\n';
	return EXIT_FAILURE;
}