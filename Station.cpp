#include "Station.h"

Commune::Commune(string communeName, string districtName, string provinceName) :
	communeName_(communeName),
	districtName_(districtName),
	provinceName_(provinceName)
{}

City::City(unsigned short id, string name, string communeName, string districtName, string provinceName) :
	id_(id),
	name_(name),
	Commune(communeName, districtName, provinceName)
{}

Location::Location(double gegrLat, double gegrLon, unsigned short id, string name, string communeName, string districtName, string provinceName, string addressStreet) :
	gegrLat_(gegrLat),
	gegrLon_(gegrLon),
	City(id, name, communeName, districtName, provinceName),
	addressStreet_(addressStreet)
{}

Station::Station(unsigned short id, string stationName, double gegrLat, double gegrLon, unsigned short CityId,
	string nameCity, string communeName, string districtName, string provinceName, string addressStreet) :
	id_(id),
	stationName_(stationName),
	Location(gegrLat, gegrLon, CityId, nameCity, communeName, districtName, provinceName, addressStreet)
{}

// Metody do pobierania danych z zewn¹trz
unsigned short Station::getStationId() const { return id_; }
string Station::getStationName() const { return stationName_; }
void Station::assignCoordinates(double (&Coordinates)[2]) const {
	Coordinates[0] = gegrLat_;
	Coordinates[1] = gegrLon_;
}
unsigned short Station::getCityId() const { return City::id_; }
string Station::getCityName() const { return City::name_; }
string Station::getCommuneName() const { return communeName_; }
string Station::getDistrictName() const { return districtName_; }
string Station::getProvinceName() const { return provinceName_; }
string Station::getAddressStreet() const { return addressStreet_; }

//Metoda dodawania stanowisk pomiarowych do stacji
void Station::addMeasurmentStand(MeasurmentStand* measurmentStand) {
	measurmentStands_.push_back(measurmentStand);
}

const vector<MeasurmentStand*>& Station::getMeasurmentStands() const { return measurmentStands_; }

Station::~Station() {
	for (auto& stand : measurmentStands_) {
		delete stand;
	}
	measurmentStands_.clear(); 
}