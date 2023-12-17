#include "str.h"
#include <limits>

int main()
{
	str string = -35.535334f;
	str name = " years old";
	string += name;
	std::cout << (string) << "\n";

	std::cout << string.length();
}