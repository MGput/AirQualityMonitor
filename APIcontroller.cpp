#include "APIcontroller.h"
#include <iostream>

using namespace std;
using json = nlohmann::json;

void CurlServiceFundaments::initializeCurl() {
    curl_global_init(CURL_GLOBAL_DEFAULT);                                          // Inicjalizacja curl
    curl = curl_easy_init();                                                        // Inicjalizacja uchwytu
    if (!curl) cerr << "Błąd inicjalizacji CURL" << endl;
}

CurlServiceFundaments::CurlServiceFundaments(){
    initializeCurl();
}

CurlServiceFundaments::~CurlServiceFundaments() {
    if (curl) curl_easy_cleanup(curl);                                              // Sprawdzanie i czyszczenie uchwytu 
    curl_global_cleanup();                                                          // Czyszczenie curl
}

size_t CurlServiceFundaments::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {    // Funkcja do odbierania danych
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

json CurlServiceFundaments::makeRequest(const string& url) {
    json responseFinal = json();
    if (curl) {
        string responseSingle;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());                           // Ustawienie adresu URL
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);               // Ustawienie funkcji i wskaźnika do odbierania danych
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseSingle);
        CURLcode reqResult = curl_easy_perform(curl);                               // Zapytanie
        if (reqResult != CURLE_OK) {
            cerr << "Błąd zapytania: " << curl_easy_strerror(reqResult) << endl;
        }
        else {
            long HTTPstatus = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &HTTPstatus);
            if (HTTPstatus == 200) {                                                // Kod OK
                try {
                    responseFinal = json::parse(responseSingle);
                }
                catch (const json::parse_error& e) {                                // Obsługa błędów JSON
                    cerr << "Błąd parsowania JSON: " << e.what() << endl;
                }
            }
            else {                                                                  // Obsługa błędów HTTP
                cerr << "Błąd HTTP " << HTTPstatus << endl;
            }
        }
    }
    return responseFinal;
}

GIOS_APImanagement::GIOS_APImanagement() :
    jsonController_(new jsonController()),
    internetConnection_(true)
{}

void GIOS_APImanagement::setConnectionStatus() {
    cout << "CHCESZ NETA? (t/n)" << endl;
    string input;
    do { cin >> input; } while (input != "t" and input != "n");
    if (input == "n") internetConnection_ = false;
}

json GIOS_APImanagement::getStationList() {
    setConnectionStatus();
    if (internetConnection_) {
        json response = makeRequest("https://api.gios.gov.pl/pjp-api/rest/station/findAll");
        jsonController_->saveStationList(response);
        return response;
    }
    cerr << "BRAK POŁĄCZENIA Z USŁUGĄ API!!!" << endl;
    cerr << "ODCZYTYWANIE DANYCH Z PLIKU..." << endl;
    return jsonController_->loadStationList();
}

json GIOS_APImanagement::getSensorList(int stationId) {
    if (internetConnection_) {
        json response = makeRequest("https://api.gios.gov.pl/pjp-api/rest/station/sensors/" + to_string(stationId));
        jsonController_->saveSensors(response);
        return response;
    }
    return json();
}

json GIOS_APImanagement::getSensorData(int sensorId) {
    if (internetConnection_) {
        json response = makeRequest("https://api.gios.gov.pl/pjp-api/rest/data/getData/" + to_string(sensorId));
        jsonController_->saveSensorData(response);
        return response;
    }
    return json();
}

json GIOS_APImanagement::getAirQualityIndex(int stationId) {
    return makeRequest("https://api.gios.gov.pl/pjp-api/rest/aqindex/getIndex/" + to_string(stationId));
}

GIOS_APImanagement::~GIOS_APImanagement() {
	delete jsonController_;
}