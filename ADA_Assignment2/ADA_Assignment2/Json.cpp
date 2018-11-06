#include "Json.h"



Json::Json()
{
}


Json::~Json()
{
}

void Json::add(string name, string value)
{
	jsonValue val(name, value);
	valuse.push_back(val);
}

void Json::write(string filename)
{
	ofstream jsonfile;
	jsonfile.open(filename);
	jsonfile << to_string();
	jsonfile.close();
}

string Json::to_string()
{
	string jsonString = "{";
	for(int i = 0; i < valuse.size()-1; i++)
	{
		jsonString += '"' + valuse.at(i).name + '"' + ": " + valuse.at(i).value+", \n";
	}
	jsonString += "}";
	return string();
}


