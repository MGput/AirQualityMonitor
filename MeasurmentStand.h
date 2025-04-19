#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <locale.h>
#include <iostream>
#include "APIcontroller.h"
#include "MeasurementData.h"
#include "functions.cpp"

using namespace std;
using json = nlohmann::json;

class Parameters {
protected:
    string paramName_;
    string paramFormula_;
    string paramCode_;
    unsigned short idParam_;
    string qualityIndex_;
public:
    Parameters(string paramName, string paramFormula, string paramCode, unsigned short idParam);
};

class MeasurmentStand : private Parameters {
private:
    unsigned short id_;
    unsigned short stationId_;
    Data* standData_;

public:
    MeasurmentStand(unsigned short id, unsigned short stationId, string paramName, string paramFormula, string paramCode, unsigned short idParam);
    MeasurmentStand(const json& StandEntry);
	void loadData();
    MeasurmentStand(const MeasurmentStand* other);

    // Metody do pobierania danych z zewnątrz
    unsigned short getId() const;
	unsigned short getStationId() const;
    string getParamName() const;
    string getParamFormula() const;
    string getParamCode() const;
    unsigned short getIdParam() const;
	void displayStandInfo() const;
	Data* getStandData() const;
    string getQualityIndex() const;
    ~MeasurmentStand();
};