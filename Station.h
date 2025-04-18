#pragma once
#include "MeasurmentStand.h"
#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class Commune {
protected:
	string communeName_;
	string districtName_;
	string provinceName_;
public:
	Commune(string communeName, string districtName, string provinceName);
};

class City : public Commune {
protected:
	unsigned short id_;
	string name_;
public:
	City(unsigned short id, string name, string communeName, string districtName, string provinceName);
};

class Location : public City {
protected:
	string gegrLat_;
	string gegrLon_;
	string addressStreet_;
public:
	Location(string gegrLat, string gegrLon, unsigned short id, string name, string communeName, string districtName, string provinceName, string addressStreet);
};

class Station : private Location {
private:
	unsigned short id_;
	string stationName_;
	vector<MeasurmentStand*> measurmentStands_;
public:
	Station(unsigned short id, string stationName, string gegrLat, string gegrLon, unsigned short CityId,
	string nameCity, string communeName, string districtName, string provinceName, string addressStreet);

	Station(const json& StationEntry);

	void loadStands();

	// Metody do pobierania danych z zewnątrz
	unsigned short getStationId() const;
	string getStationName() const;
	void assignCoordinates(string(&Coordinates)[2]) const;
	unsigned short getCityId() const;
	string getCityName() const;
	string getCommuneName() const;
	string getDistrictName() const;
	string getProvinceName() const;
	string getAddressStreet() const;

	void testDisplayData() const;

	//Metoda dodawania stanowisk pomiarowych do stacji
	void addMeasurmentStand(MeasurmentStand* measurmentStand);

	const vector<MeasurmentStand*>& getMeasurmentStands() const;

	~Station();
};