#include "str.h"
#include <string>
#include <memory> // for smart pointer
#include <math.h>
#include <stdexcept>

#define DECIMAL_PRECISION_MULTIPLIER 1000000

#define ascii_t char
#define unicode_t wchar_t
//#include <iostream>

// This could be an issue because it might become possible to overwrite temporarily, create an unsafe string and point to it, then reset to 256.
const size_t MAX_STRING_SIZE = 256;

// This string is guaranteed safe because I'm the one initializing it
str::str()
{
	mString = (char*)"";
	mLength = 0;
}

// Make a copy of the string given and point to that. Make it difficult to edit a string's content except in conjunction with other strings
str::str(const char* c_str)
{
	// Get the size of the buffer
	size_t buffer_size = strnlen(c_str, MAX_STRING_SIZE) + 1;

	// Create a new buffer
	char* newBuffer = (char*)malloc(buffer_size);
	
	if(newBuffer)
	{
		// Copy contents
		memcpy(newBuffer, c_str, buffer_size);

		// Null terminator. Might make this redundant by properly calculating buffer size and not writing \0 twice
		newBuffer[buffer_size - 1] = 0;

		
		
	}
		// Point to the copy
		mString = (char*)newBuffer;
		mLength = buffer_size - 1;
	}

str::str(int number)
{
	size_t buffSize = getBuffSize(number) + 1;
	char* buffer = (char*)malloc(buffSize);
	// set null byte
	if(buffer)
	{
		// Set null byte
		buffer[buffSize - 1] = '\0';

		// This is a little sketch ngl. It sets the first byte to '-' if the number is negative, which will never get overwritten by the digit raster later on, otherwise it will write to null and be overwritten later
		// Set negative sign or null byte (latter will be overwritten)
		buffer[0] = ('-' * (number < 0));
	
		// Pointer set to the last digit
		char* current_digit = buffer + buffSize - 2;


		number = abs(number);


		while (number > 0)
		{
			*current_digit = '0' + number % 10;
			number /= 10;
			current_digit--;
		}
		mLength = buffSize - 1;
	}
	else
	{
		mLength = 0;
	}

	// Points either to the newly created buffer or nullptr
	mString = buffer;
}

str::str(float number)
{
	bool sign = (number < 0);
	number = abs(number);
	int intPart = (int)number;
	int fracPart = (int)((number - intPart) * DECIMAL_PRECISION_MULTIPLIER); // 6 decimal places of accuracy
	// 0.000000 -> 0.0
	while (fracPart % 10 == 0 && fracPart != 0)
	{
		fracPart /= 10;
	}
	
	// Get the exact amount of bytes we need for memory efficiency
	size_t bufferSize = getBuffSize(intPart) + getBuffSize(fracPart) + 2 + sign; // size of int / frac parts + sign + '/0' + '.'

	// Find a buffer
	char* buffer = (char*)malloc(bufferSize);

	// continue if the buffer is nullptr
	if (buffer)
	{
		// Set null byte
		buffer[bufferSize - 1] = '\0';

		// Set negative sign or null byte (latter will be overwritten later)
		buffer[0] = ('-' * sign);

		// Pointer set to the last digit
		char* current_digit = buffer + bufferSize - 2;

		// Raster fractional part, back to front
		while (fracPart > 0)
		{
			*current_digit = '0' + fracPart % 10;
			fracPart /= 10;
			current_digit--;
		}

		// Add decimal point
		*current_digit = '.';
		current_digit--;

		// Raster integer part, back to front
		while (intPart > 0)
		{
			*current_digit = '0' + intPart % 10;
			intPart /= 10;
			current_digit--;
		}
		// Cache length
		mLength = bufferSize - 1;
	}
	mString = buffer;
}

str::~str() = default;

const size_t str::length() const
{
	 return mLength;
}

const char* str::c_str() const
{
	return mString;
}

void str::append(str& other)
{
	// Get buffer size
	size_t buffer_size = mLength + other.mLength + 1;
	// Make buffer
	char* newBuffer = (char*)realloc(sizeof(char) * buffer_size);


	if (newBuffer && mString && other.mString)
	{
		// copy bytes
		memcpy(newBuffer, mString, mLength);
		memcpy(newBuffer + (mLength * sizeof(char)), other.mString, other.mLength);
		// set null byte
		newBuffer[buffer_size - 1] = 0;

		// delete the old pointer
		delete[] mString;

		// Point to the new buffer
		mString = newBuffer;

		// Update the length of the string
		mLength += other.mLength;
	}
	else
	{
		// Set the pointer to nullptr.
		mString = nullptr;

		// Set the length to zero, appropriately
		mLength = 0;
	}

}

char str::get(size_t index) const
{
	// Allow Python - like access via negative indices
	if (index < 0) { index += mLength; }
	if (index < 0 || index > mLength)
	{
		throw std::out_of_range("Read access violation: Index out of range");
	}
	return mString[index];
}

char str::operator[](long long index) const
{
	// Allow Python - like access via negative indices
	index %= mLength;
	return mString[index];
}

void str::set(size_t index, char newChar)
{
	index %= mLength;
	mString[index] = newChar;

	// If the new character is a null byte...
	if(!newChar)
	{
		// free the extra space ( CHANGE THIS WHEN IMPLEMENTING CAPACITY
		mLength = index;
	}
}


size_t str::find(const str& sub_string) const {
	char* p = strstr(mString, sub_string.mString);

	return (p != nullptr) ? static_cast<size_t>(p - mString) : std::string::npos;
}

size_t str::find(const char* sub_string) const {
	char* p = strstr(mString, sub_string);

	return (p != nullptr) ? static_cast<size_t>(p - mString) : std::string::npos;
}

size_t str::find(size_t start, const str& sub_string) const {

	start %= mLength;

	char* p = strstr(mString + start, sub_string.mString);

	return (p != nullptr) ? static_cast<size_t>(p - mString) : std::string::npos;
}

size_t str::find(size_t start,  const char* sub_string) const {
	
	start %= mLength;

	char* p = strstr(mString + start, sub_string);

	return (p != nullptr) ? static_cast<size_t>(p - mString) : std::string::npos;
}

str str::copy()
{
	str newString;

	char* copy_buffer = (char*)malloc(sizeof(char) * mLength);
	if (copy_buffer)
	{
		memcpy(copy_buffer, mString, sizeof(char) * mLength);

		newString.mString = copy_buffer;
		newString.mLength = mLength;
	}

	return newString;
}

inline size_t str::getBuffSize(int number)
{
	bool sign = (number < 0);
	// Find the length of the buffer that is just large enough to hold number
	number = abs(number);
	return

		(number >= 1000000000) +
		(number >= 100000000) +
		(number >= 10000000) +
		(number >= 1000000) +
		(number >= 100000) +
		(number >= 10000) +
		(number >= 1000) +
		(number >= 100) +
		(number >= 10) +
		(number >= 0) +
		sign;

}