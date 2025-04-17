#pragma once

#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class CurlServiceFundaments {
private:
    CURL* curl;
    void initializeCurl();

public:
    CurlServiceFundaments();
    ~CurlServiceFundaments();
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

protected:
    json makeRequest(const std::string& url);
};

class GIOS_APImanagement : public CurlServiceFundaments {
public:
    json getStationList();                       // API zapytanie o listê stacji
    json getSensorList(int stationId);           // API zapytanie o listê sensorów
    json getSensorData(int sensorId);            // API zapytanie o dane z sensora
    json getAirQualityIndex(int stationId);      // API zapytanie o indeks jakoœci powietrza
};