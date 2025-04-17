#pragma once

#include <string>
using namespace std;

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
    // Metody do pobierania danych z zewn¹trz
    unsigned short getId() const;
    string getParamName() const;
    string getParamFormula() const;
    string getParamCode() const;
    unsigned short getIdParam() const;
};