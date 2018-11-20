#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"
#include "Quickselect.h"
#include "PriorityQueueSelect.h"
#include "Json.h"
#include <math.h>
#include <random>

#include "Stopwatch.h"
#include "ConsoleMatrix.h"
#include "JSONPlot.h"

// CPP program for implementation of QuickSelect 
using namespace std;

int randomInt(int maxVal = 100) {
	return rand() % maxVal;
}


std::vector<float> getAvg(std::vector <std::vector<float>> vec) {
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

int main() {
	std::vector<float> xdata;

	std::vector <std::vector<float>> ydata_qstats_nPointerIncrementations;
	std::vector <std::vector<float>> ydata_qstats_nSwaps;
	std::vector <std::vector<float>> ydata_pqstats_nArrayAccesses;
	std::vector <std::vector<float>> ydata_pqstats_nComparisons;
	int maxN = 10000;
	int k = 9;

	std::vector<int> ns;
	for (int N = 10; N < maxN; N += 100)
	{
		ns.push_back(N);
	}

	for (int i = 0; i < ns.size(); i++)//
	{
		int N = ns.at(i);
		xdata.push_back(N);
		ydata_qstats_nPointerIncrementations.push_back(std::vector<float>());
		ydata_qstats_nSwaps.push_back(std::vector<float>());
		ydata_pqstats_nArrayAccesses.push_back(std::vector<float>());
		ydata_pqstats_nComparisons.push_back(std::vector<float>());

		system("cls");
		std::cout << getProcessbar(N, maxN, 20) << std::endl;

		std::vector<arrayType> vec(N);
		for (int g = 0; g < N; g++) vec[g] = (N - g);
		
		int nK = 100;
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

	JSONPlot jp("Complexity","N","times");
	jp.addData("qstats_nPointerIncrementations", xdata, getAvg(ydata_qstats_nPointerIncrementations));
	jp.addData("qstats_nSwaps", xdata, getAvg(ydata_qstats_nSwaps));
	jp.addData("pqstats_nArrayAccesses", xdata, getAvg(ydata_pqstats_nArrayAccesses));
	jp.addData("pqstats_nComparisons", xdata, getAvg(ydata_pqstats_nComparisons));
	jp.write();

	std::system("pause");
	return 0;
}
