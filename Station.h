#pragma once
#include "MeasurmentStand.h"
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
	double gegrLat_;
	double gegrLon_;
	string addressStreet_;
public:
	Location(double gegrLat, double gegrLon, unsigned short id, string name, string communeName, string districtName, string provinceName, string addressStreet);
};

class Station : private Location {
private:
	unsigned short id_;
	string stationName_;
	vector<MeasurmentStand*> measurmentStands_;
public:
	Station(unsigned short id, string stationName, double gegrLat, double gegrLon, unsigned short CityId,
	string nameCity, string communeName, string districtName, string provinceName, string addressStreet);

	Station(const json& StationEntry);

	// Metody do pobierania danych z zewn¹trz
	unsigned short getStationId() const;
	string getStationName() const;
	void assignCoordinates(double(&Coordinates)[2]) const;
	unsigned short getCityId() const;
	string getCityName() const;
	string getCommuneName() const;
	string getDistrictName() const;
	string getProvinceName() const;
	string getAddressStreet() const;

	//Metoda dodawania stanowisk pomiarowych do stacji
	void addMeasurmentStand(MeasurmentStand* measurmentStand);

	const vector<MeasurmentStand*>& getMeasurmentStands() const;

	~Station();
};