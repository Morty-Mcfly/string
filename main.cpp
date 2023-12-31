#include "str.h"
#include <limits>

int main()
{
	str code = "int i = 2; int j = 32;";
	code.replace("int", "float");

	std::cout << code;

	std::cout << string.length();
}