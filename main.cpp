#include "APIcontroller.h"
#include <iostream>

using namespace std;
using json = nlohmann::json;

int main() {
    // Przyk�adowe u�ycie API GIO�
    GIOS_APImanagement api;

    json stations = api.getStationList();

    if (!stations.empty()) {
        cout << "Pobrano " << stations.size() << " stacji pomiarowych." << endl;

        // Wy�wietl kilka przyk�adowych stacji
        for (int i = 0; i < stations.size(); i++) {
            cout << "Stacja ID: " << stations[i]["id"] << endl;
            cout << "Nazwa: " << stations[i]["stationName"] << endl;
            cout << "Ulica: " << stations[i]["addressStreet"] << endl;
            cout << "-----------------------" << endl;
        }
    }
    else {
        cout << "Nie uda�o si� pobra� listy stacji." << endl;
    }

    return 0;
}