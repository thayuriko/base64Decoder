// Base64Decoder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "CSVReader.h"
#include "CSVWriter.h"
#include "Base64.h"

using namespace std;

string& trim_left_inplace(string &s, const string &delimiters = " \f\n\r\t\v")
{
	return s.erase(0, s.find_first_not_of(delimiters));
}

stringstream asciiToHex(string asciiString) {
	stringstream hValStr;

	for (size_t i = 0; i < asciiString.length(); i++)
	{
		int hValInt = (char)asciiString[i];
		hValStr << "0x" << hex << hValInt << " ";
	}

	return hValStr;
}

int main() {
	string filename, tmp;
	vector<vector<uint8_t>> payloadHex;
	vector<vector<string>> outputCsv, newCsv;
	vector<uint8_t> payloadDecoded;
	string newCell;
	ofstream newCsvFile;
	int rssi, snr;

	int colId, rowId = 0, pktId = -1, columnMax = 0;

	cout << "Insira o nome do arquivo .csv: ";
	cin >> tmp;

	filename = trim_left_inplace(tmp, ".");

	CSVReader csvReader(filename + ".csv");
	CSVWriter csvWriter(filename + "Decoded.csv");

	outputCsv = csvReader.parse2DCsvFile();

	for (auto item : outputCsv) {
		colId = 0;

		for (auto data : item) {
			if (data == "PayloadRaw") pktId = colId;
			if (columnMax < colId) columnMax = colId + 1;

			if (colId++ != pktId) continue;

			payloadDecoded = Base64::decode(data);
			payloadHex.push_back(payloadDecoded);
		}

		if (rowId == 0) {
			newCell = "Payload Decoded,RSSI,SNR";
		}
		else {
			newCell = "";

			for (uint8_t i = 0; i < payloadDecoded.size(); i++) {
				newCell += to_string(payloadDecoded[i]) + " ";
			}

			snr = payloadDecoded[payloadDecoded.size() - 2] / 4;
			rssi = payloadDecoded[payloadDecoded.size() - 1] - 2 * 137;

			if (rssi > -120)
				newCell += "," + to_string(rssi);
			else
				newCell += "," + to_string(0);

			newCell += "," + to_string(snr);
		}

		newCsv.push_back(item);
		newCsv[rowId++].push_back(newCell);
	}

	for (auto item : newCsv) {
		csvWriter.addDatainRow(item.begin(), item.end());
	}	

	system("pause");

	return 0;
}