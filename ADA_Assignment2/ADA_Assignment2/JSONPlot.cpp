#include "JSONPlot.h"
JSONPlot::JSONPlot(std::string titel, std::string xlabel, std::string ylabel, std::string plotType)
{
	JSONPlot::titel = titel;
	count = 0;
	j.add("titel", titel);
	j.add("xlabel", xlabel);
	j.add("ylabel", ylabel);
	j.add("plotType", plotType);
}

void JSONPlot::write(std::string filename)
{
	if (filename == " ") filename = titel+".json";
	j.write(filename);
}

void JSONPlot::addData(std::string legend, std::vector<float> xdata, std::vector<float> ydata)
{
	j.add("legend_" + std::to_string(count), legend);
	j.add("xdata_" + std::to_string(count), xdata);
	j.add("ydata_" + std::to_string(count), ydata);
	count++;
}

JSONPlot::~JSONPlot()
{
}
