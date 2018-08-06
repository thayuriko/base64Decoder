#include "stdafx.h"
#include "CSVReader.h"

/**
* Reads csv file into table, exported as a vector of vector of doubles.
* @param inputFileName input file name (full path).
* @return data as vector of vector of doubles.
*/
std::vector<std::vector<std::string>> CSVReader::parse2DCsvFile() {
	std::vector<std::vector<std::string>> data;
	std::ifstream inputFile(fileName);
	int l = 0;

	while (inputFile) {
		l++;
		std::string s;

		if (!std::getline(inputFile, s))
			break;

		if (s[0] != '#') {
			std::istringstream ss(s);
			std::vector<std::string> record;

			while (ss) {
				std::string line;
				if (!getline(ss, line, ','))
					break;
				try {
					record.push_back(line);
				}
				catch (const std::invalid_argument e) {
					std::cout << "NaN found in file " << fileName << " line " << l
						<< std::endl;
					e.what();
				}
			}

			data.push_back(record);
		}
	}

	if (!inputFile.eof()) {
		std::cerr << "Could not read file " << fileName << "\n";
		throw std::invalid_argument("File not found.");
	}

	return data;
}
