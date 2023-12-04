#include "str.h"
#include <string>
#include <memory> // for smart pointer
#include <math.h>
#include <stdexcept>
#include <format>

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

		// Point to the copy
		mString = (char*)newBuffer;
		mLength = buffer_size - 1;
	}
}

str::str(int number)
{
	ch
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
	char* newBuffer = (char*)malloc(sizeof(char) * buffer_size);


	if (newBuffer && mString && other.mString)
	{
		// copy bytes
		memcpy(newBuffer, mString, mLength);
		memcpy(newBuffer + (mLength * sizeof(char)), other.mString, other.mLength);
		//0x00000270ab95c660
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

char str::get(long long index) const
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
	if (index < 0) { index += mLength; }
	if (index < 0 || index > mLength)
	{
		throw std::out_of_range("Read access violation: Index out of range");
	}
	return mString[index];
}

void str::set(long long index, char newChar)
{
	if (index < 0) { index += mLength; }
	if (index < 0 || index >= mLength)
	{
		throw std::out_of_range("Read access violation: Index out of range");
	}
	mString[index] = newChar;
	// If the new character is a null byte, change the cached length of the string.
	if(!newChar)
	{
		mLength = (size_t)index;
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
	return str(mString);
}