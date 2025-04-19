#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

class Values {
protected:
    string date_;
    double value_;
public:
    Values(string date, double value);
    string getDate() const;
    double getValue() const;
};

class Data {
private:
    string key_;
    vector<Values*> values_;
public:
    Data(string key);
    Data(const json& DataEntry);
    Data(const Data& other);
    void addValue(string date, double value);
    string getKey() const;
    const vector<Values*>& getValues() const;
    ~Data();
};