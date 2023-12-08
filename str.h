#pragma once

#include <memory>
#include <iostream>
#ifndef STRING_H
#define STRING_H

#define STRING_MAX_SIZE 64
extern const size_t MAX_STRING_SIZE;


/*
Fast string class.

* char* is containerized in instances of the class
* safety is enforced on initialization.
* If operating on char*'s, safety is enforced on that char*
* If operating on other strings, safety is not enforced, as the char* is (mostly) gauranteed to be safe.
* This makes it so if you do string operations with the same string, operations will be exceptionally fast
* NOTICE: I am a novice and had a neat idea, and wanted to create strings from scratch. As such, this class might not actually be safe.
* If you use this and find an exploit, please correct it, as well as document it. 
* 
* TODO: Add operations, including:
* String comparison
* String multiplication (might create a separate, inherited class to keep down on memory)
* Find & replace
* Strings from ints, booleans, floats
* Formatted char*
*/
#define DECIMAL_PRECISION 6

// longest uint32:  4294967295 (10)
// longest  int32: -2147483648 (11)

class str
{
	
	public:
		// Initialize the string to an empty string
		str();

		// Initialize the string to a constant C string
		str(const char* c_str);

		// String from signed integer
		str(int number);

		// String from unsigned integer
		//str(unsigned int number);

		str(float number);
		

		// Destructor
		~str();

		// Peak into the C-string. Read-only reference
		const char* c_str() const;

		// Get a peak into the string's length. Read-only reference
		const size_t length() const;

		// Append the other string to the end of this one
		void append(str& other);

		// Append a char* to the end of this string safely.
		//void append(const char* other);


		// Replace up to n occurences of new_string with old_string. -1 for all
		//void replace(const str& old_string, const str& new_string);
		
		// Get the character at mString[index]
		char get(long long index) const;

		// Set the character at index. Has some safety checks to update length if need be
		void set(long long index, char newChar);

		// Get the character at mString[index]
		char operator[](long long index) const;

		// For std::cout-ing a string
		friend std::ostream& operator <<(std::ostream& os, const str& string)
		{
			os << string.mString;
			return os;
		}

		// Find sub_string(str) in this string
		size_t find(const str& sub_string) const;

		// Find sub_string(const char*) in this string
		size_t find(const char* sub_string) const;

		// Find sub_string(str) in this string starting with the character at start
		size_t find(size_t start, const str& sub_string) const;

		// Find sub_string(const char*) in this string starting with the character at start
		size_t find(size_t start, const char* sub_string) const;

		// Create a copy of the string
		str copy();

		// Append two strings
		str operator+(str const& other);


	private:

		// Pointer to the C string
		char* mString;

		// Length of the string
		size_t mLength;

		inline size_t getBuffSize(int number);
};


#endif // MYHEADER_H