#include "MeasurmentStand.h"

using namespace std;

Parameters::Parameters(string paramName, string paramFormula, string paramCode, unsigned short idParam) :
	paramName_(paramName),
	paramFormula_(paramFormula),
	paramCode_(paramCode),
	idParam_(idParam)
{
}

MeasurmentStand::MeasurmentStand(unsigned short id, unsigned short stationId, string paramName, string paramFormula, string paramCode, unsigned short idParam) :
	id_(id),
	stationId_(stationId),
	Parameters(paramName, paramFormula, paramCode, idParam),
	standData_(nullptr)
{}

MeasurmentStand::MeasurmentStand(const json& StandEntry) :
	id_(StandEntry["id"].get<unsigned short>()),
	stationId_(StandEntry["stationId"].get<unsigned short>()),
	standData_(nullptr),
	Parameters(
		StandEntry["param"]["paramName"].get<string>(),
		StandEntry["param"]["paramFormula"].get<string>(),
		StandEntry["param"]["paramCode"].get<string>(),
		StandEntry["param"]["idParam"].get<unsigned short>()
	)
{}

void MeasurmentStand::loadData() {
	GIOS_APImanagement* API = new GIOS_APImanagement();
	standData_ = new Data(API->getSensorData(id_));
	cout << "załadowano dane" << endl;
	qualityIndex_ = API->getAirQualityIndex(stationId_)[uncapitalizeString(paramFormula_)+"IndexLevel"]["IndexLevelName"].get<string>();
	delete API;
}

MeasurmentStand::MeasurmentStand(const MeasurmentStand* other) :
	id_(other->getId()),
	stationId_(other->stationId_),
	Parameters(other->getParamName(), other->getParamFormula(), other->getParamCode(), other->getIdParam()),
    standData_(other->standData_ ? new Data(*other->standData_) : nullptr)
{}

unsigned short MeasurmentStand::getId() const { return id_; }

unsigned short MeasurmentStand::getStationId() const { return stationId_; }

string MeasurmentStand::getParamName() const { return paramName_; }

string MeasurmentStand::getParamFormula() const { return paramFormula_; }

string MeasurmentStand::getParamCode() const { return paramCode_; }

unsigned short MeasurmentStand::getIdParam() const { return idParam_; }

void MeasurmentStand::displayStandInfo() const {
	cout << "	-------------------------------------------------------" << endl;
	cout << "	Id stanowiska:			" << id_ << endl;
	cout << "	Nazwa parametru:		" << paramName_ << endl;
	cout << "	Wzór:				" << paramFormula_ << endl;
	cout << "	Kod:				" << paramCode_ << endl;
	cout << "	IdParametru:			" << idParam_ << endl;
	cout << "	-------------------------------------------------------" << endl;
}

Data* MeasurmentStand::getStandData() const {
	return standData_;
}

string MeasurmentStand::getQualityIndex() const { return qualityIndex_; }

MeasurmentStand::~MeasurmentStand() { delete standData_; }