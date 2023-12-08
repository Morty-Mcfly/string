#include "str.h"
#include <limits>

int main()
{
	str string = -35.535334f;
	std::cout << string << "\n";
	std::cout << string.length();
}