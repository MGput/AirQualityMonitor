#include <string>
#include <vector>

using namespace std;

class Values {
protected:
	string date_;
	double value_;

public:
	Values(string date, double value) :
		date_(date),
		value_(value)
	{}

	string getDate() const { return date_; }
	double getValue() const { return value_; }
};

class Data {
private:
	string key_;
	vector<Values*> values_;

public:
	Data(string key) :
		key_(key)
	{}

	void addValue(string date, double value) {
		values_.push_back(new Values(date, value));
	}

	string getKey() const { return key_; }
	const vector<Values*>& getValues() const { return values_; }
	unsigned int getNumberOfValues() const { return values_.size(); }

	~Data() {
		for (Values* value : values_) {
			delete value;
		}
		values_.clear();
	}
};