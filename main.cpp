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

    GIOS_APImanagement api;
    json stationList = api.getStationList();
	cout << "Liczba stacji: " << stationList.size() << endl;

	for (size_t i = 0; i < stationList.size(); ++i) {
		stat = new Station(stationList[i]);
		stat->testDisplayData();
		delete stat;
	}

    return 0;
}