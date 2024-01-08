#pragma once
#include <iostream>

class str_slice
{
public:

	// Create a string slice.
	str_slice(char* start, size_t length)
	{
		mStart = start;
		mLength = length;
	}

	// Get the length of the string view
	inline const size_t len() const
	{
		return mLength;
	}

	// Get a pointer to the start of the string view.
	inline const char* start() const
	{
		return mStart;
	}

	// Get a copy of the string view. If you want to treat the string view as a char*, use this.
	inline const char* get() const
	{
		const char* buffer = (const char*)malloc(mLength);
		if (buffer)
		{
			memcpy(buffer, mStart, mLength);
		}
		return buffer;
	}

	// Printing a string view
	friend std::ostream& operator << (std::ostream& os, const str_slice& slice)
	{
		os.write(slice.start(), slice.len());
		return os;
	}

private:
	char* mStart;
	size_t mLength;

};

