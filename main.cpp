#include "str.h"
#include <limits>
#include <thread>

int main()
{
	str code = "int i = 2; int j = 32;";
	code.replace("int", "float");

	std::cout << code;

}