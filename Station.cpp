#include "Station.h"
#include "APIcontroller.h"

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

Location::Location(string gegrLat, string gegrLon, unsigned short id, string name, string communeName, string districtName, string provinceName, string addressStreet) :
	gegrLat_(gegrLat),
	gegrLon_(gegrLon),
	City(id, name, communeName, districtName, provinceName),
	addressStreet_(addressStreet)
{}

Station::Station(unsigned short id, string stationName, string gegrLat, string gegrLon, unsigned short CityId,
	string nameCity, string communeName, string districtName, string provinceName, string addressStreet) :
	id_(id),
	stationName_(stationName),
	Location(gegrLat, gegrLon, CityId, nameCity, communeName, districtName, provinceName, addressStreet)
{}

Station::Station(const json& StationEntry):
	id_(StationEntry["id"].get<unsigned short>()),
	stationName_(StationEntry["stationName"].get<string>()),
	Location(
		StationEntry["gegrLat"].get<string>(),
		StationEntry["gegrLon"].get<string>(),
		StationEntry["city"]["id"].get<unsigned short>(),
		StationEntry["city"]["name"].get<string>(),
		StationEntry["city"]["commune"]["communeName"].get<string>(),
		StationEntry["city"]["commune"]["districtName"].get<string>(),
		StationEntry["city"]["commune"]["provinceName"].get<string>(),
		StationEntry.contains("addressStreet") && !StationEntry["addressStreet"].is_null() 
			? StationEntry["addressStreet"].get<string>() 
			: "BRAK"
	)
{}

void Station::loadStands() {
	GIOS_APImanagement* API = new GIOS_APImanagement();
	for (auto& stand : API->getSensorList(id_)) {
		MeasurmentStand* measurmentStand = new MeasurmentStand(stand);
		addMeasurmentStand(measurmentStand);
	}
	delete API;
}

// Metody do pobierania danych z zewnątrz
unsigned short Station::getStationId() const { return id_; }
string Station::getStationName() const { return stationName_; }
void Station::assignCoordinates(string (&Coordinates)[2]) const {
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

/*
void Station::testDisplayData()
const {
	cout << "===============================================================" << endl;
	cout << "Id stacji:			" << id_ << endl;
	cout << "Stacja:				" << stationName_ << endl;
	cout << "Szerokość geograficzna:		" << gegrLat_ << endl;
	cout << "Długość geograficzna:		" << gegrLon_ << endl;
	cout << "Id miasta:			" << City::id_ << endl;
	cout << "Nazwa miasta:			" << City::name_ << endl;
	cout << "Nazwa gminy:			" << communeName_ << endl;
	cout << "Nazwa powiatu:			" << districtName_ << endl;
	cout << "Nazwa województwa:		" << provinceName_ << endl;
	if(addressStreet_ != "BRAK") cout << "Ulica:				" << addressStreet_ << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "Stanowiska pomiarowe na danej stacji (" << measurmentStands_.size() << "): " << endl;
	for (size_t i = 0; i < measurmentStands_.size(); ++i) {
		cout << "	" << i + 1 << ". " << measurmentStands_[i]->getParamName() << endl;
		cout << "		ID:			" << measurmentStands_[i]->getId() << endl;
		cout << "		Nazwa:			" << measurmentStands_[i]->getParamName() << endl;
		cout << "		Wzór:			" << measurmentStands_[i]->getParamFormula() << endl;
		cout << "		Kod:			" << measurmentStands_[i]->getParamCode() << endl;
		cout << "		IdParametru:		" << measurmentStands_[i]->getIdParam() << endl << endl;
		cout << "		Wpisy:" << endl;
		for (const auto& value : measurmentStands_[i]->getStandData()->getValues()) {
			cout << "			" << value->getValue() << " - " << value->getDate() << endl;
		}
	}
	cout << "===============================================================" << endl << endl;
}
*/

void Station::displayStationData() const {
	cout << "===============================================================" << endl;
	cout << "Id stacji:			" << id_ << endl;
	cout << "Stacja:				" << stationName_ << endl;
	cout << "Szerokość geograficzna:		" << gegrLat_ << endl;
	cout << "Długość geograficzna:		" << gegrLon_ << endl;
	cout << "Id miasta:			" << City::id_ << endl;
	cout << "Nazwa miasta:			" << City::name_ << endl;
	cout << "Nazwa gminy:			" << communeName_ << endl;
	cout << "Nazwa powiatu:			" << districtName_ << endl;
	cout << "Nazwa województwa:		" << provinceName_ << endl;
	if (addressStreet_ != "BRAK") cout << "Ulica:				" << addressStreet_ << endl;
	cout << "===============================================================" << endl;
}

bool Station::checkForInfo(string searchText) const {
	string searchTextLower = searchText;
	transform(searchTextLower.begin(), searchTextLower.end(), searchTextLower.begin(), ::tolower);

	auto containsText = [&searchTextLower](const string& field) {
		string fieldLower = field;
		transform(fieldLower.begin(), fieldLower.end(), fieldLower.begin(), ::tolower);
		return fieldLower.find(searchTextLower) != string::npos;
	};

	if (containsText(stationName_)) return true;
	if (containsText(gegrLat_)) return true;
	if (containsText(gegrLon_)) return true;
	if (containsText(City::name_)) return true;
	if (containsText(communeName_)) return true;
	if (containsText(districtName_)) return true;
	if (containsText(provinceName_)) return true;
	if (containsText(addressStreet_)) return true;
	return false;
}

MeasurmentStand* Station::filteredMeasureStand(const string& pollutionType) {
	MeasurmentStand* filteredStand;
	for (auto& stand : measurmentStands_) {
		cout << pollutionType << " = " << stand->getParamFormula() << " ?		";
		if (stand->getParamFormula() == pollutionType) {
			filteredStand = new MeasurmentStand(stand);
			cout << "TAK" << endl;
			return filteredStand;
		}
		else cout << "NIE" << endl;
	}
	return nullptr;
}

const vector<MeasurmentStand*>& Station::getMeasurmentStands() const { return measurmentStands_; }

Station::~Station() {
	for (auto& stand : measurmentStands_) {
		delete stand;
	}
	measurmentStands_.clear(); 
}
