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

unsigned short MeasurmentStand::getId() const { return id_; }

string MeasurmentStand::getParamName() const { return paramName_; }

string MeasurmentStand::getParamFormula() const { return paramFormula_; }

string MeasurmentStand::getParamCode() const { return paramCode_; }

unsigned short MeasurmentStand::getIdParam() const { return idParam_; }