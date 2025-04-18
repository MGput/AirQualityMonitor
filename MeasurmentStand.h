#pragma once

#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class Parameters {
protected:
    string paramName_;
    string paramFormula_;
    string paramCode_;
    unsigned short idParam_;
public:
    Parameters(string paramName, string paramFormula, string paramCode, unsigned short idParam);
};

class MeasurmentStand : private Parameters {
private:
    unsigned short id_;
public:
    MeasurmentStand(unsigned short id, string paramName, string paramFormula, string paramCode, unsigned short idParam);
    MeasurmentStand(const json& StandEntry);
    // Metody do pobierania danych z zewn�trz
    unsigned short getId() const;
    string getParamName() const;
    string getParamFormula() const;
    string getParamCode() const;
    unsigned short getIdParam() const;
};