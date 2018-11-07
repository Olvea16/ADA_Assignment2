#pragma once
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void makeJOSNPlotData(string titel, string xlabel, string ylabel, vector<float> xdata, vector<float> ydata, string plotType = "plot");

class Json
{
public:
	Json();
	~Json();

	void add(string name, string value);
	template<typename T>
	void add(string name, T value);
	template<typename T>
	void add(string name, vector<T> value);
	void add(string name, vector<string> value);

	void write(string filename);
	string to_string();

protected:
	
	struct jsonValue
	{
		string name;
		string value;

		jsonValue(string namein, string valuein) {
			name = namein;
			value = valuein;
		}
	};
	void addJsonValue(jsonValue val);
	vector<jsonValue> valuse;
};

