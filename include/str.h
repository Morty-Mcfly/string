#pragma once

#include <memory>
#include <iostream>
#include "..\slice.h"

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
* Add templates
*/

#define DECIMAL_PRECISION 6



class str
{
	
	public:
		// Initialize the string to an empty string
		str();

		// Initialize the string to a constant C string
		str(const char* c_str);

		// String from signed integer
		str(int number);


		str(float number);
		

		// Destructor
		~str();

		// Peak into the C-string. Read-only reference
		const char* c_str() const;

		// Get a peak into the string's length. Read-only reference
		const size_t length() const;

		// Append the other string to the end of this one
		void append(str other);

		// Number of sub_string in this string
		size_t count(const str& sub_string);

		// Replace every occurence of old with new
		void replace(const str& old_sub, const str& new_sub);

		// Get a string view
		const str_slice substring(size_t start, size_t end) const
		{
			str_slice slice = { mString + start, end };
			return slice;
		}

		
		// Get the character at mString[index]
		char get(size_t index) const;

		// Set the character at index. Has some safety checks to update length if need be
		void set(size_t index, char newChar);
		

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
		str operator+(str const& other)
		{
			// NOTICE: This does not edit this string or the other string.

			// Get buffer size
			size_t buffer_size = mLength + other.mLength + 1;
			// Make buffer
			char* newBuffer = (char*)malloc(sizeof(char) * buffer_size);


			if (newBuffer && mString && other.mString)
			{
				// copy bytes
				memcpy(newBuffer, mString, mLength);
				memcpy(newBuffer + (mLength * sizeof(char)), other.mString, other.mLength);

				// set null byte
				newBuffer[buffer_size - 1] = 0;

				

				
			}
			// Create a new string. The constructor isn't performance heavy
			str out_string;

			// No need to construct a str from a char*. Just construct an empty one and overwrite its length and char* instead of having to run safety checks
			out_string.mString = newBuffer;
			out_string.mLength = other.mLength + mLength;

			// Return the cheaply constructed string.
			return out_string;
		}

		// Append two strings
		str operator+=(str const& other)
		{
			// NOTICE: This does not edit this string or the other string.

			// Get buffer size
			size_t buffer_size = mLength + other.mLength + 1;
			// Make buffer
			char* newBuffer = (char*)malloc(sizeof(char) * buffer_size);


			if (newBuffer && mString && other.mString)
			{
				// copy bytes
				memcpy(newBuffer, mString, mLength);
				memcpy(newBuffer + (mLength * sizeof(char)), other.mString, other.mLength);

				// set null byte
				newBuffer[buffer_size - 1] = 0;

				mString = newBuffer;
				mLength += other.mLength;


			}
			
			return *this;
		}
		
		str operator == (str const& other)
		{
			if (mLength == other.mLength)
			{
				for (size_t i = 0; i < mLength; i++)
				{
					if (*(mString + i) != *(other.mString + i))
					{
						return false;
					}
					else
					{
						break;
					}
				}
				return true;
			}
			else
			{
				return false;
			}
			std::cout << "no output?";
		}

		str operator > (str const& other)
		{
			if (mLength == other.mLength)
			{
				for (size_t i = 0; i < mLength; i++)
				{
					if (*(mString + i) <= *(other.mString + i))
					{
						return false;
					}
					else
					{
						break;
					}
				}
				return true;
			}
			else
			{
				return false;
			}
			std::cout << "no output?";
		}

		str operator < (str const& other)
		{
			if (mLength == other.mLength)
			{
				for (size_t i = 0; i < mLength; i++)
				{
					if (*(mString + i) >= *(other.mString + i))
					{
						return false;
					}
					else
					{
						break;
					}
				}
				return true;
			}
			else
			{
				return false;
			}
			std::cout << "no output?";
		}

		str operator * (int count)
		{
			char* buffer = (char*)malloc(mLength * count);
			for (size_t i = 0; i < count; i++)
			{
				memcpy(buffer + (mLength * i), mString, mLength);
			}
			str temp;

			free(temp.mString);
			temp.mString = buffer;
			return temp;
		}


		// Get the character at mString[index]
		char operator[](size_t index)// const
		{
			// Allow Python - like access via negative indices
			index %= mLength;
			return mString[index];
		}


		// For std::cout-ing a string
		friend std::ostream& operator <<(std::ostream& os, const str& string)
		{
			os << string.mString;
			return os;
		}

	private:

		// Pointer to the C string
		char* mString;

		// Length of the string
		size_t mLength;

		// Helper function to get the size of a buffer just large enough to fit number, eg -325 would return 4
		inline size_t getBuffSize(int number);

		size_t substr(const str& other);
};

int substr(const char* string, size_t length, const char* sub_string, size_t sub_length);

#endif // MYHEADER_H