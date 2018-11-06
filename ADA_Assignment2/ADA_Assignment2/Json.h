#pragma once
#include <string>
#include <vector>
#include <fstream>

using namespace std;
class Json
{
public:
	Json();
	~Json();
	void add(string name, string value);
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

	vector<jsonValue> valuse;
};

