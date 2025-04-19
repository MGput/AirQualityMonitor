#include <string>
#include <iostream>

using namespace std;

static string uncapitalizeString(const string& str) {
	string result = str;
	cout << "input: " << result << endl;
	if (!result.empty()) {
		for (size_t i = 0; i < result.length(); i++){
			result[i] = tolower(result[i]);
		}
	}
	cout << "output: " << result << endl;
	return result;
}