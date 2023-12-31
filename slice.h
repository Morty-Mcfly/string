#pragma once
#include <iostream>

class str_slice
{
public:

	str_slice(char* start, size_t length)
	{
		mStart = start;
		mLength = length;
	}

	inline const size_t len() const
	{
		return mLength;
	}
	inline const char* start() const
	{
		return mStart;
	}

	friend std::ostream& operator << (std::ostream& os, const str_slice& slice)
	{
		os.write(slice.start(), slice.len());
		return os;
	}

private:
	char* mStart;
	size_t mLength;

};

