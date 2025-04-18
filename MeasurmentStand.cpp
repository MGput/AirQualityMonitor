#include "MeasurmentStand.h"

#include <string>
using namespace std;

Parameters::Parameters(string paramName, string paramFormula, string paramCode, unsigned short idParam) :
	paramName_(paramName),
	paramFormula_(paramFormula),
	paramCode_(paramCode),
	idParam_(idParam)
{
}

MeasurmentStand::MeasurmentStand(unsigned short id, string paramName, string paramFormula, string paramCode, unsigned short idParam) :
	id_(id),
	Parameters(paramName, paramFormula, paramCode, idParam)
{}

MeasurmentStand::MeasurmentStand(const json& StandEntry) :
	id_(StandEntry["id"].get<unsigned short>()),
	Parameters(
		StandEntry["param"]["paramName"].get<string>(),
		StandEntry["param"]["paramFormula"].get<string>(),
		StandEntry["param"]["paramCode"].get<string>(),
		StandEntry["param"]["idParam"].get<unsigned short>()
	)
{}

unsigned short MeasurmentStand::getId() const { return id_; }

string MeasurmentStand::getParamName() const { return paramName_; }

string MeasurmentStand::getParamFormula() const { return paramFormula_; }

string MeasurmentStand::getParamCode() const { return paramCode_; }

unsigned short MeasurmentStand::getIdParam() const { return idParam_; }