#include "MeasurmentStand.h"
#include <string>
#include <vector>

using namespace std;

class Commune {
protected:
	string communeName_;
	string districtName_;
	string provinceName_;
public:
	Commune(string communeName, string districtName, string provinceName) :
		communeName_(communeName),
		districtName_(districtName),
		provinceName_(provinceName)
	{}
};

class City : public Commune{
protected:
	unsigned short id_;
	string name_;
public:
	City(unsigned short id, string name, string communeName, string districtName, string provinceName) :
		id_(id),
		name_(name),
		Commune(communeName, districtName, provinceName)
	{}
};

class Location : public City{
protected:
	double gegrLat_;
	double gegrLon_;
	string addressStreet_;
public:
	Location(double gegrLat, double gegrLon, unsigned short id, string name, string communeName, string districtName, string provinceName, string addressStreet) :
		gegrLat_(gegrLat),
		gegrLon_(gegrLon),
		City(id, name, communeName, districtName, provinceName),
		addressStreet_(addressStreet)
	{}
};

class Station : private Location {
private:
	unsigned short id_;
	string stationName_;
	vector<MeasurmentStand*> measurmentStands_;
public:
	Station(unsigned short id, string stationName, double gegrLat, double gegrLon, unsigned short CityId,
		string nameCity, string communeName, string districtName, string provinceName, string addressStreet) :
		id_(id),
		stationName_(stationName),
		Location(gegrLat, gegrLon, CityId, nameCity, communeName, districtName, provinceName, addressStreet)
	{}

	// Metody do pobierania danych z zewn¹trz
	unsigned short getStationId() const { return id_; }
	string getStationName() const { return stationName_; }
	void assignCoordinates(double (&Coordinates)[2]) const {
		Coordinates[0] = gegrLat_;
		Coordinates[1] = gegrLon_;
	}
	unsigned short getCityId() const { return City::id_; }
	string getCityName() const { return City::name_; }
	string getCommuneName() const { return communeName_; }
	string getDistrictName() const { return districtName_; }
	string getProvinceName() const { return provinceName_; }
	string getAddressStreet() const { return addressStreet_; }

	//Metoda dodawania stanowisk pomiarowych do stacji
	void addMeasurmentStand(MeasurmentStand* measurmentStand) {
		measurmentStands_.push_back(measurmentStand);
	}

	const vector<MeasurmentStand*>& getMeasurmentStands() const { return measurmentStands_; }

	~Station() {
		for (auto& stand : measurmentStands_) {
			delete stand;
		}
		measurmentStands_.clear(); 
	}
};