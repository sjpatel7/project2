
#include <iostream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <ctime>
#include <algorithm>
using namespace std;

const int size = 3;
int config[size][size];
double fiveSteps[10000];
double fiftySteps[10000];
double fivehSteps[10000];

double kb = 1.38064852 * pow(10, -23);
// this function randomly samples spin configurations with a transition probability
//argument d is the dimension of the of configuration
double MHsample(double temp, int sample) {
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
	//this outer loop applies transitions to the configuration
	for (int trans = 0; trans < 500; trans++) {
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
		if ( trans==4 || trans==49 || trans==499) {
			//this builds a 9 bit binary number in configNum. the highest bit represents spin for top left spin.
			int configNum = 0;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (config[i][j] == -1) {
						;
					} else {
						configNum += (1 << (size * i + j));
					}
				}
			}
			if (trans == 4) {
				fiveSteps[sample] = configNum;
			} else if(trans == 49) {
				fiftySteps[sample] = configNum;
			} else if(trans == 499) {
				fivehSteps[sample] = configNum;
			}
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
	double temp = 1000 ;
	double magsquare_array[10000];
	double total = 0;
	for (int sample = 0; sample < 10000; sample++) {
		magsquare_array[sample] = MHsample(temp, sample);
		total += magsquare_array[sample];
	}

	ofstream myfile("C:/Users/Shawn/source/repos/Project0c++/Project0c++/probdist5.txt");
	for (int i = 0; i < 10000; i++) {
		myfile << fiveSteps[i] << endl;
	}
	ofstream MYfile("C:/Users/Shawn/source/repos/Project0c++/Project0c++/probdist50.txt");
	for (int i = 0; i < 10000; i++) {
		MYfile << fiftySteps[i] << endl;
	}
	ofstream Myfile("C:/Users/Shawn/source/repos/Project0c++/Project0c++/probdist500.txt");
	for (int i = 0; i < 10000; i++) {
		Myfile << fivehSteps[i] << endl;
	}
	ofstream File("C:/Users/Shawn/source/repos/Project0c++/Project0c++/stats1.txt");
	for (int i = 0; i < 100; i++) {
		File << magsquare_array[i] << endl;
	}
	double mag_ave = total / 10000;
	cout << mag_ave;
	return 0;
}

