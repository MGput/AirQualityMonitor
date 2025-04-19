#pragma once

#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "jsonController.cpp"

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
private:
	jsonController* jsonController_;
	bool internetConnection_;
public:
    GIOS_APImanagement();
    void setConnectionStatus();
    json getStationList();                       // API zapytanie o listę stacji
    json getSensorList(int stationId);           // API zapytanie o listę sensorów
    json getSensorData(int sensorId);            // API zapytanie o dane z sensora
    json getAirQualityIndex(int stationId);      // API zapytanie o indeks jakości powietrza
    ~GIOS_APImanagement();
};