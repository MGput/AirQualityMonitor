#include "APIcontroller.h"
#include "Station.h"
#include <iostream>
#include <locale.h>

using namespace std;
using json = nlohmann::json;

int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	setlocale(LC_ALL, ".UTF8");
	Station* stat;
	string input;
	vector<MeasurmentStand*> stands;
	MeasurmentStand* filteredStand;
	Data* data;

    GIOS_APImanagement api;
    json stationList = api.getStationList();
	cout << "Liczba stacji: " << stationList.size() << endl;

	for (size_t i = 0; i < stationList.size(); ++i) {
		stat = new Station(stationList[i]);
		stat->displayStationData();
		do {
			getline(cin, input);
		} while (input != "stands" and input != "q" and input != "" and input != "search" and input != "filter");
		if (input == "q") {
			return 0;
		}
		
		if (input == "filter") {
			string filter;
			do {
				getline(cin, filter);

				transform(filter.begin(), filter.end(), filter.begin(),					// Zmiana znaków na wielkie litery
					[](unsigned char c) { return toupper(c); });

				if (filter != "PM10" and filter != "SO2" and filter != "PM25" and filter != "O3" and filter != "NO2") {
					cout << "ZŁY TYP ZANIECZYSZCZENIA :(" << endl;
					continue;
				}
				else break;

			} while (true);
			for (size_t j = 0; j < stationList.size(); ++j) {
				stat = new Station(stationList[j]);
				stat->loadStands();
				filteredStand = stat->filteredMeasureStand(filter);
				if (!filteredStand) {
					stat->displayStationData();
					filteredStand->displayStandInfo();
						cout << endl;
				}
				delete stat;
				delete filteredStand;
			}
			return 0;
		}

		if (input == "search") {
			string searchQuery;
			vector<Station*> stationsFound;

			cout << "Wprowadź frazę do wyszukania: ";
			getline(cin, searchQuery);

			// Przeszukaj wszystkie stacje
			for (size_t i = 0; i < stationList.size(); ++i) {
				Station* tempStation = new Station(stationList[i]);
				if (tempStation->checkForInfo(searchQuery)) {
					stationsFound.push_back(tempStation);
				}
				else {
					delete tempStation; // Usuń stacje, które nie pasują do wyszukiwania
				}
			}

			cout << endl << searchQuery << endl;

			// Wyświetl znalezione stacje
			if (stationsFound.empty()) {
				cout << "Nie znaleziono stacji pasujących do zapytania." << endl;
			}
			else {
				cout << "Znaleziono " << stationsFound.size() << " pasujących stacji:" << endl;

				for (size_t i = 0; i < stationsFound.size(); ++i) {
					cout << "\nStacja #" << (i + 1) << ":" << endl;
					stationsFound[i]->displayStationData();
				}
			}

			// Zwolnij pamięć
			for (auto station : stationsFound) {
				delete station;
			}
			stationsFound.clear();

			delete stat;
			stat = nullptr;
			return 0;
		}

		if (input == "stands") {
			stat->loadStands();
			stands = stat->getMeasurmentStands();
			cout << "Liczba stanowisk: " << stands.size() << endl;
			for (size_t j = 0; j < stands.size(); ++j) {
				stands[j]->displayStandInfo();
				getline(cin, input);
				if (input == "entries") {
					data = stands[j]->getStandData();
					cout << endl;
					if (data->getValues().empty()) {
						cout << endl << "	BRAK :(" << endl;
						break;
					}
					cout << "			Data	    |  Wartość" << endl;
					cout << "		--------------------+------------" << endl;
					for (size_t k = 0; k < data->getValues().size(); ++k) {
						cout << "		" << data->getValues()[k]->getDate() << " |	" << data->getValues()[k]->getValue() << endl;
					}
					cout << endl;
					getline(cin, input);
				}
				if (j == stands.size() - 1) {
					cout << "	KONIEC STANOWISK NA TEJ STACJI :(" << endl << endl;
					getline(cin, input);
					break;
				}
				if (input == "q") break;
			}
		}

		delete stat;
	}

    return 0;
}