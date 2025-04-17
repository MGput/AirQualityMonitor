#pragma once

#include <string>
#include <vector>
using namespace std;

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
    void addValue(string date, double value);
    string getKey() const;
    const vector<Values*>& getValues() const;
    unsigned int getNumberOfValues() const;
    ~Data();
};