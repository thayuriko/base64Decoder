#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <iterator>
#include <string>
#include <algorithm>

/*
* A class to create and write data in a csv file.
*/
class CSVWriter
{
	std::string fileNameW;
	std::string delimeterW;
	int linesCount;

public:
	CSVWriter(std::string filename, std::string delm = ",") :
		fileNameW(filename), delimeterW(delm), linesCount(0)
	{}
	/*
	* Member function to store a range as comma seperated value
	*/
	template<typename T>
	void addDatainRow(T first, T last) {
		std::fstream file;
		// Open the file in truncate mode if first line else in Append Mode
		file.open(fileNameW, std::ios::out | (linesCount ? std::ios::app : std::ios::trunc));

		// Iterate over the range and add each lement to file seperated by delimeter.
		for (; first != last; )
		{
			file << *first;
			if (++first != last)
				file << delimeterW;
		}
		file << "\n";
		linesCount++;

		// Close the file
		file.close();
	}
};
