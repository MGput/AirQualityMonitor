#include "APIcontroller.h"
#include <iostream>

using namespace std;
using json = nlohmann::json;

int main() {
    // Przyk³adowe u¿ycie API GIOŒ
    GIOS_APImanagement api;

    json stations = api.getStationList();

    if (!stations.empty()) {
        cout << "Pobrano " << stations.size() << " stacji pomiarowych." << endl;

        // Wyœwietl kilka przyk³adowych stacji
        for (int i = 0; i < stations.size(); i++) {
            cout << "Stacja ID: " << stations[i]["id"] << endl;
            cout << "Nazwa: " << stations[i]["stationName"] << endl;
            cout << "Ulica: " << stations[i]["addressStreet"] << endl;
            cout << "-----------------------" << endl;
        }
    }
    else {
        cout << "Nie uda³o siê pobraæ listy stacji." << endl;
    }

    return 0;
}