#include <nlohmann/json.hpp>
#include <windows.h>
#include <direct.h>
#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;

class jsonController {
public:
	void saveStationList(json& stationList) {

		/*
		DWORD attributes = GetFileAttributesA("ProjectData");
		if (attributes == INVALID_FILE_ATTRIBUTES or !(attributes & FILE_ATTRIBUTE_DIRECTORY)) {
			cout << "TWORZENIE FOLDERU ProjectData..." << endl;
			_mkdir("ProjectData");
			cout << "FOLDER UTWORZONY" << endl;
		}
		ofstream outFile("ProjectData/stationList.json");
		cout << "ZAPISYWANIE DO PLIKU..." << endl;
		outFile << stationList.dump(0);
		outFile.close();
		cout << "ZAPISANO" << endl;
		*/
		cout << "TESTTESTTEST";
		DWORD attributes = GetFileAttributesA("ProjectData");
		if (attributes == INVALID_FILE_ATTRIBUTES) {
			cout << "TWORZENIE FOLDERU ProjectData..." << endl;
			_mkdir("ProjectData");
			cout << "FOLDER UTWORZONY" << endl;
		}
		else if (!(attributes & FILE_ATTRIBUTE_DIRECTORY)) {
			cout << "ŚCIEŻKA ProjectData ISTNIEJE, ALE NIE JEST FOLDEREM!" << endl;
		}
		else {
			cout << "FOLDER ProjectData JUŻ ISTNIEJE" << endl;
		}
	}

	json loadStationList() {
		ifstream inFile("ProjectData/stationList.json");
		json stationList;
		if (inFile.is_open()) {
			inFile >> stationList;
			inFile.close();
			if (stationList.empty()) {
				cerr << "BRAK DANYCH!" << endl;
				return json();
			}
			cout << "WCZYTANO DANE Z PLIKU!" << endl;
		}
		else {
			cerr << "" << endl;
		}
		return stationList;

	}

	void saveSensors(const json& sensors) {

	}

	void saveSensorData(const json& sensorData) {
		
	}

    void deleteAllData() {  

    }

	friend class GIOS_APImanagement;
	friend class curlServiceFundaments;
};