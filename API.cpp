#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class CurlServiceFundaments {
private:
    CURL* curl;

    void initializeCurl() {
        curl_global_init(CURL_GLOBAL_DEFAULT);                // Inicjalizacja curl
        curl = curl_easy_init();                              // Inicjalizacja uchwytu

        if (!curl) cerr << "Błąd inicjalizacji CURL" << endl;
    }

public:
    CurlServiceFundaments() {
        initializeCurl();
    }

    ~CurlServiceFundaments() {
        if (curl) curl_easy_cleanup(curl);                    // Sprawdzanie i czyszczenie uchwytu 
        curl_global_cleanup();                                // Czyszczenie curl
    }

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {    // Funkcja do odbierania danych
        ((string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

protected:
    json makeRequest(const string& url) {
        json responseFinal;
        if (curl) {
            string responseSingle;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());                       // Ustawienie adresu URL
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);           // Ustawienie funkcji i wskaźnika do odbierania danych
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseSingle);
            CURLcode reqResult = curl_easy_perform(curl);                           // Zapytanie

            if (reqResult != CURLE_OK) {
                cerr << "Błąd zapytania: " << curl_easy_strerror(reqResult) << endl;
            }
            else {
                long HTTPstatus = 0;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &HTTPstatus);
                if (HTTPstatus == 200) {                                            // Kod OK
                    try {
                        responseFinal = json::parse(responseSingle);
                    }
                    catch (const json::parse_error& e) {                            // Obsługa błędów JSON
                        cerr << "Błąd parsowania JSON: " << e.what() << endl;
                    }
                }
                else {                                                              // Obsługa błędów HTTP
                    cerr << "Błąd HTTP " << HTTPstatus << endl;
                }
            }
        }
        return responseFinal;
    }
};

class GIOS_APImanagement : public CurlServiceFundaments {
public:
    json getStationList() {                                                         // API zapytanie o listę stacji
        return makeRequest("https://api.gios.gov.pl/pjp-api/rest/station/findAll");
    }

    json getSensorList(int stationId) {                                             // API zapytanie o listę sensorów
        return makeRequest("https://api.gios.gov.pl/pjp-api/rest/station/sensors/" + to_string(stationId));
    }

    json getSensorData(int sensorId) {                                              // API zapytanie o dane z sensora
        return makeRequest("https://api.gios.gov.pl/pjp-api/rest/data/getData/" + to_string(sensorId));
    }

    json getAirQualityIndex(int stationId) {                                        // API zapytanie o indeks jakości powietrza
        return makeRequest("https://api.gios.gov.pl/pjp-api/rest/aqindex/getIndex/" + to_string(stationId));
    }
};