#include "MeasurementData.h"

Values::Values(string date, double value) :
	date_(date),
	value_(value)
{}

string Values::getDate() const { return date_; }

double Values::getValue() const { return value_; }


Data::Data(string key) : key_(key){}

void Data::addValue(string date, double value) {
	values_.push_back(new Values(date, value));
}

string Data::getKey() const { return key_; }

const vector<Values*>& Data::getValues() const { return values_; }

unsigned int Data::getNumberOfValues() const { return values_.size(); }

Data::~Data() {
	for (Values* value : values_) {
		delete value;
	}
	values_.clear();
}