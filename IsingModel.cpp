
#include <iostream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <ctime>
#include <algorithm>
using namespace std;

const int size = 20;
int config[size][size];

double kb = 1.38064852 * pow(10, -23);
// this function randomly samples spin configurations with a transition probability
//argument d is the dimension of the of configuration
double MHsample(double temp) {

	//this outer loop applies transitions to the configuration
	for (int trans = 0; trans < 10000; trans++) {
		int randrow = rand() % size;
		int randcol = rand() % size;
		double energy_Change = 0;
		if (randrow < size - 1) {
			energy_Change += -2 * (-(config[randrow][randcol] * config[randrow + 1][randcol]));
		} else {
			energy_Change += -2 * (-(config[randrow][randcol] * config[0][randcol])); }
		if (randrow > 0) {
			energy_Change += -2 * (-(config[randrow][randcol] * config[randrow - 1][randcol]));
		} else {
			energy_Change += -2 * (-(config[randrow][randcol] * config[size][randcol])); }
		if (randcol < size - 1) {
			energy_Change += -2 * (-(config[randrow][randcol] * config[randrow][randcol + 1]));
		} else {
			energy_Change += -2 * (-(config[randrow][randcol] * config[randrow][0])); }
		if (randcol > 0) {
			energy_Change += -2 * (-(config[randrow][randcol] * config[randrow][randcol - 1]));
		} else {
			energy_Change += -2 * (-(config[randrow][randcol] * config[randrow][size]));
		}

		double prob;
		if (energy_Change <= 0) {
			prob = 1.0;
		} else {
			prob = exp(-energy_Change / temp);
		}
		double randNum = (double)rand() / (double)RAND_MAX;   //randNum is a random number [0,1]
		if (randNum < prob) {
			config[randrow][randcol] = -config[randrow][randcol];
		}
	}
	double M = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			M += config[i][j];
		}
	}
	double m = M / (size * size);
	double m_squared = m*m;
	return m_squared;
}
int main()
{
	srand((unsigned)time(0));
	int spin[2] = { -1,1 };
	//come back to the dimensions of config when I figure out how to make variable size for array
	//this loop initializes the configuration with spins of -1 or 1
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			config[i][j] = spin[1];
			//config[i][j] = spin[rand() % 2];
		}
	}
	//change temp to whatever value for samples
	double temp = 2;
	double magsquare_array[100];
	double total = 0;
	for (int sample = 0; sample < 100; sample++) {
		magsquare_array[sample] = MHsample(temp);
		total += magsquare_array[sample];
	}
//	ofstream myfile("stats.txt");
//	for (int i = 0; i < 100; i++) {
//		myfile << magsquare_array[i] << endl;
//	}

	double mag_ave = total / 100;
	cout << mag_ave;
	return 0;
}
