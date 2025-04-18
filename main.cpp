#include "APIcontroller.h"
#include "Station.h"
#include <iostream>

using namespace std;
using json = nlohmann::json;

int main() {
	Station* stat;

    GIOS_APImanagement api;
    json stationList = api.getStationList();
	for (size_t i = 0; i < stationList.size(); ++i) {
		stat = new Station(stationList[i]);
		stat->testDisplayData();
	}

    return 0;
}