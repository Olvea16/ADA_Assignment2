#pragma once
#include <string>
#include "Json.h"
#include <vector>
class JSONPlot
{
protected:
	Json j;
	int count;
	std::string titel;
public:
	JSONPlot(std::string titel, std::string xlabel, std::string ylabel, std::string plotType = "plot");

	void addData(std::string legend, std::vector<float> xdata, std::vector<float> ydata);
	void write(std::string filename = " ");
	~JSONPlot();
};

