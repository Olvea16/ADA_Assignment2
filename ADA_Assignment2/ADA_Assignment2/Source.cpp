#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"
#include "Quickselect.h"
#include "PriorityQueueSelect.h"
#include "Json.h"
#include <math.h>
#include <random>

#include "ConsoleMatrix.h"
#include "JSONPlot.h"

// CPP program for implementation of QuickSelect 
using namespace std;

int randomInt(int maxVal = 100) {
	return rand() % maxVal;
}


std::vector<float> getAvg(std::vector<std::vector<float>> &vec) {
	std::vector<float> sum;
	for (size_t i = 0; i < vec.size(); i++) {
		sum.push_back(0.0);
		for (size_t j = 0; j < vec.at(i).size(); j++)
		{
			sum.at(i) += vec.at(i).at(j);
		}
		sum.at(i) /= vec.at(i).size();
	}
	return sum;
}

std::string fts(float f, int dec) {
	std::string floatstring = std::to_string(f);
	std::string res = "";
	unsigned int i;
	for (i = 0; i < floatstring.length(); i++) {
		if (floatstring[i] != '.') res += floatstring[i];
		else break;
	}
	for (unsigned int j = i + dec; i <= j and i < floatstring.length(); i++) {
		res += floatstring[i];
	}
	return res;
}

std::string getProcessbar(int n, int maxn, int len = 10) {
	char rn[8] = { '|', '/', '-', '\\', '|', '/', '-', '\\' };
	static int c = 0;

	std::string bar = "[";

	float pro = (n) / float(maxn) * 100;
	int barNumber = std::floor(pro / 100 * len);

	for (int i = 0; i < barNumber; i++) bar += '#';

	if (barNumber + 1 < len) bar += rn[c++ % 8];

	for (int i = barNumber + 1; i < len; i++) bar += ' ';
	bar += "]";

	bar += fts(std::roundf(pro * 100) / 100, 2) + "%";

	return bar;
}

struct testData
{
	std::vector<float> xdata;
	std::vector<float> ydata_qstats_nPointerIncrementations;
	std::vector<float> ydata_qstats_nSwaps;
	std::vector<float> ydata_pqstats_nArrayAccesses;
	std::vector<float> ydata_pqstats_nComparisons;
};

testData runComplextiTest(int startN, int endN, int increment, int nK = 100, std::string prefix = "") {
	testData data;

	std::vector<std::vector<float>> ydata_qstats_nPointerIncrementations;
	std::vector<std::vector<float>> ydata_qstats_nSwaps;
	std::vector<std::vector<float>> ydata_pqstats_nArrayAccesses;
	std::vector<std::vector<float>> ydata_pqstats_nComparisons;

	int k = 9;

	std::vector<int> ns;
	for (int N = startN; N < endN; N += increment)
	{
		ns.push_back(N);
	}

	for (int i = 0; i < ns.size(); i++)//
	{
		int N = ns.at(i);
		data.xdata.push_back(N);
		ydata_qstats_nPointerIncrementations.push_back(std::vector<float>());
		ydata_qstats_nSwaps.push_back(std::vector<float>());
		ydata_pqstats_nArrayAccesses.push_back(std::vector<float>());
		ydata_pqstats_nComparisons.push_back(std::vector<float>());

		//system("cls");
		std::cout << prefix << getProcessbar(N, ns.back(), 20) << '\r';

		std::vector<arrayType> vec(N);
		for (int g = 0; g < N; g++) vec[g] = (N - g);

		
		for (int j = 0; j < nK; j++)
		{

			k = 1 + randomInt(N - 2);

			random_shuffle(vec.begin(), vec.end());

			QSTimeComplexityStats qstats;
			PQSTimeComplexityStats pqstats;

			double nqsVal = Quickselect::select(vec, k - 1, qstats);

			double pqsVal = PriorityQueueSelect::select(vec, k, pqstats);


			ydata_qstats_nPointerIncrementations.back().push_back(qstats.nPointerIncrementations);
			ydata_qstats_nSwaps.back().push_back(qstats.nSwaps);
			ydata_pqstats_nArrayAccesses.back().push_back(pqstats.nArrayAccesses);
			ydata_pqstats_nComparisons.back().push_back(pqstats.nComparisons);
		}
	}

	data.ydata_qstats_nPointerIncrementations = getAvg(ydata_qstats_nPointerIncrementations);
	data.ydata_qstats_nSwaps = getAvg(ydata_qstats_nSwaps);
	data.ydata_pqstats_nArrayAccesses = getAvg(ydata_pqstats_nArrayAccesses);
	data.ydata_pqstats_nComparisons = getAvg(ydata_pqstats_nComparisons);

	return data;
}

void writeTestDataJSON(testData &data) {
	JSONPlot jp("Complexity", "N", "times");
	jp.addData("qstats_nPointerIncrementations", data.xdata, data.ydata_qstats_nPointerIncrementations);
	jp.addData("qstats_nSwaps", data.xdata, data.ydata_qstats_nSwaps);
	jp.addData("pqstats_nArrayAccesses", data.xdata, data.ydata_pqstats_nArrayAccesses);
	jp.addData("pqstats_nComparisons", data.xdata, data.ydata_pqstats_nComparisons);
	jp.write();
}

std::string vecToS(std::vector<int> &vec) {
	std::string res = "[ ";
	for (size_t i = 0; i < vec.size()-1; i++)
	{
		res += std::to_string(vec.at(i)) + ", ";
	}
	res += std::to_string(vec.back()) + " ]";
	return res;
}

int main() {
	srand(time(NULL));
	ConsoleMatrix cm(2);

	std::vector<int> vec;
	int maxn = 40;
	for (int i = 0; i < maxn; i++)
	{
		vec.push_back(i);
	}
	random_shuffle(vec.begin(), vec.end());
	vec.erase(vec.begin() + maxn / 2, vec.end());
	
	std::cout << "The array: " << vecToS(vec) << ". Has numbers from 0 to " << maxn-1 << std::endl;

	int k = rand()%vec.size();
	
	QSTimeComplexityStats qstats;
	PQSTimeComplexityStats pqstats;
	int nqsVal = Quickselect::select(vec, k, qstats);
	int pqsVal = PriorityQueueSelect::select(vec, k, pqstats);
	cm.addRow({ "k is:", std::to_string(k) });
	cm.addRow({"Quickselect found:", std::to_string(nqsVal)});
	cm.addRow({ "PriorityQueueSelect found:", std::to_string(pqsVal) });
	cm.print();


	
	testData data = runComplextiTest(10, 2000, 450, 100, "Running small complexity test ");
	std::cout << std::endl;
	std::cout << "Note that the values are averages of 100 repetitions with a random k-value." << std::endl;

	int dataPoints = 5;
	for (size_t i = 0; i < dataPoints; i++)
	{
		int index = i * (data.xdata.size() - 1) / (dataPoints - 1);
		ConsoleMatrix cm2(3);
		cm2.addRow({ "n is:", std::to_string(data.xdata.at(index)) , ""});
		cm2.addRow({"Quickselect :", "Pointer incrementations", "Swaps"});
		cm2.addRow({ "", std::to_string(data.ydata_qstats_nPointerIncrementations.at(index)), std::to_string(data.ydata_qstats_nSwaps.at(index))});
		cm2.addRow({ "PriorityQueueSelect :", "Array accesses", "Comparisons" });
		cm2.addRow({ "", std::to_string(data.ydata_pqstats_nArrayAccesses.at(index)), std::to_string(data.ydata_pqstats_nComparisons.at(index)) });
		cm2.print();
		std::cout << std::endl;
	}

	std::cout << "We strongly recommend looking at the complexity graph in the PDF" << std::endl << "for a better understanding of the complexity measurements." << std::endl;
	 
	std::system("pause");
	return 0;
}
